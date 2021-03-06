// Direcciones y puertos a los que envía mensajes OSC

m = NetAddr("127.0.0.1", 5612); // para OpenFrameworks
n = NetAddr("127.0.0.1", 12000); // para Processing

// Para correr el History.

(
q = ();
NetAddr.broadcastFlag = true;
q.addrs = (0..7).collect { |x|
		NetAddr("255.255.255.255", 57120 + x)
};
q.sendAll = { |q ... args|
		q.addrs.do { |addr|
				addr.sendMsg(*args)
		}; ""
}

);

(

History.start;
//History.makeWin;

OSCdef(\hist, { |msg|
	//msg.postln;
	History.enter(msg[2].asString, msg[1]);
}, \hist).fix;

// Este OSCdef envía lo que se declara a of y p

OSCdef(\ofyp, { |msg|
	n.sendMsg("/message", msg[2].asString, msg[1].asString);
	m.sendMsg("/message", msg[2].asString, msg[1].asString);
}, \hist);


History.localOff;

History.forwardFunc = { |code|
	//q.sendAll(\hist, \killall, code);
	q.sendAll(\hist, \emi, code);
};

)

// lectura de CSVs. Parece que hay que declararlos uno por uno, en bloque se pachequea

// fuentes juntas

// chico 0.0011980022099968
// grande 0.01241282988032

// crab

x = CSVFileReader.read(thisProcess.nowExecutingPath.dirname +/+"../csv/HAWC_fluxlc_Crab_.csv", true, true).postcs;

a = Array.fill(472, { arg i; x[i+1][0].split($ ) });
b = Array.fill(472, { arg i; a[i][0] });

//h = b.sort
//h[471] // chico
//h[0] // grande
//h[471].asFloat*100000000000 // chico 0.012142932893696
//h[0].asFloat*100000000000 // grande 0.01241282988032

// mrk421

y = CSVFileReader.read(thisProcess.nowExecutingPath.dirname +/+"../csv/HAWC_fluxlc_Mrk421_.csv", true, true).postcs;

c = Array.fill(471, { arg i; y[i+1][0].split($ ) });
d = Array.fill(471, { arg i; c[i][0] });

//h = d.sort
//h[470] // chico
//h[0] // grande
//h[470].asFloat*100000000000 // chico 0.01215144315904
//h[0].asFloat*100000000000 // grande -0.00128261856256


/// mrk501

z = CSVFileReader.read(thisProcess.nowExecutingPath.dirname +/+"../csv/HAWC_fluxlc_Mrk501_.csv", true, true).postcs;

e = Array.fill(479, { arg i; z[i+1][0].split($ ) });
f = Array.fill(479, { arg i; e[i][0] });

//h = f.sort
//h[478] // chico
//h[0] // grande
//h[478].asFloat*100000000000 // chico 0.0011980022099968
//h[0].asFloat*100000000000 // grande -0.001229125466112

// proxy JITLib just in time library

p = ProxySpace.push(s.boot);
p.quant = 4;
s.meter;

// fuentes como un continuo ar kr

//~crab = {Demand.kr(Impulse.kr(16), 0, Dseq(b.asFloat*100000000000, inf))};
//~mrk421 = {Demand.kr(Impulse.kr(16), 0, Dseq(d.asFloat*100000000000, inf))};
//~mrk501 = {Demand.kr(Impulse.kr(16), 0, Dseq(f.asFloat*100000000000, inf))};

~crab = {Lag.kr(Demand.kr(Impulse.kr(8), 0, Dseq(b.asFloat*100000000000, inf)), 0.5)};
~mrk421 = {Lag.kr(Demand.kr(Impulse.kr(8), 0, Dseq(d.asFloat*100000000000, inf)), 0.5)};
~mrk501 = {Lag.kr(Demand.kr(Impulse.kr(8), 0, Dseq(f.asFloat*100000000000, inf)), 0.5)};

// replys que jalan el demand

~crabSend = {SendReply.kr(Impulse.kr(30), '/crabSend', ~crab.kr)};
~mrk421Send = {SendReply.kr(Impulse.kr(30), '/mrk421Send', ~mrk421.kr)};
~mrk501Send = {SendReply.kr(Impulse.kr(30), '/mrk501Send', ~mrk501.kr)};

(

OSCdef(\crabSend, {|msg|
	var data = msg[3];
	//msg[3].postln;
	n.sendMsg("/crabSend", data);
	m.sendMsg("/crabSend", data);
}, '/crabSend');

OSCdef(\mrk421Send, {|msg|
	var data = msg[3];
	//msg[3].postln;
	n.sendMsg("/mrk421Send", data);
	m.sendMsg("/mrk421Send", data);
}, '/mrk421Send');

OSCdef(\mrk501Send, {|msg|
	var data = msg[3];
	//msg[3].postln;
	n.sendMsg("/mrk501Send", data);
	m.sendMsg("/mrk501Send", data);
}, '/mrk501Send');

)

OSCdef(\crabSend).free; /// para pararlo
OSCdef(\mrk421Send).free; /// para pararlo
OSCdef(\mrk501Send).free; /// para pararlo


// demands con valores del csv

~dema = {Demand.kr(Impulse.kr(4), 0, Dseq(b.asFloat*10000000000, inf))};
~deca = {Decay.kr(Demand.kr(Impulse.kr(4), 0, Dseq(b.asFloat*10000000000, inf)) * Impulse.kr(4), 0.3)};
~crab = {Pan4.ar(SinOsc.ar(LinLin.kr(~dema, 0, 1, 100, 1000), 0, ~deca)) * 10};

~dema2 = {Demand.kr(Impulse.kr(6), 0, Dseq(b.asFloat*10000000000, inf))};
~deca2 = {Decay.kr(Demand.kr(Impulse.kr(6), 0, Dseq(b.asFloat*10000000000, inf)) * Impulse.kr(6), 0.3)};
~crab2 = {Pan4.ar(SinOsc.ar(LinLin.kr(~dema2, 0, 1, 100, 5000), 0, ~deca2)) * 10};

~dema3 = {Demand.kr(Impulse.kr(2), 0, Dseq(b.asFloat*10000000000, inf))};
~deca3 = {Decay.kr(Demand.kr(Impulse.kr(2), 0, Dseq(b.asFloat*10000000000, inf)) * Impulse.kr(2), 0.3)};
~crab3 = {Pan4.ar(SinOsc.ar(LinLin.kr(~dema3, 0, 1, 100, 10000), 0, ~deca3)) * 10};

~crab.play;
~crab2.play;
~crab3.play;