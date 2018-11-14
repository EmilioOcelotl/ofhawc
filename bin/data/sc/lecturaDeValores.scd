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

h = f.sort
//h[478] // chico
//h[0] // grande
//h[478].asFloat*100000000000 // chico 0.0011980022099968
//h[0].asFloat*100000000000 // grande -0.001229125466112

// proxy

Orb.start("192.168.1.111", 12000); // la dirección de la otra compu. Se necesita la librería PiranhaLab
Orb.start("127.0.0.1", 5612); // la dirección de la otra compu. Se necesita la librería PiranhaLab

p = ProxySpace.push(s.boot);
p.quant = 4;

// fuentes como un continuo

~crab = {Demand.kr(Impulse.kr(8), 0, Dseq(b.asFloat*100000000000, inf))};
~mrk421 = {Demand.kr(Impulse.kr(8), 0, Dseq(d.asFloat*100000000000, inf))};
~mrk501 = {Demand.kr(Impulse.kr(8), 0, Dseq(f.asFloat*100000000000, inf))};

// replys que jalan el demand

~crabSend = {SendReply.kr(Impulse.kr(30), '/crabSend', ~crab.kr)};
~mrk421Send = {SendReply.kr(Impulse.kr(30), '/mrk421Send', ~mrk421.kr)};
~mrk501Send = {SendReply.kr(Impulse.kr(30), '/mrk501Send', ~mrk501.kr)};

// oscdef

(

OSCdef(\crabSend, {|msg|
	var data = msg[3];
	//msg[3].postln;
	Orb.n.sendMsg("/crabSend", data);
}, '/crabSend');

OSCdef(\mrk421Send, {|msg|
	var data = msg[3];
	//msg[3].postln;
	Orb.n.sendMsg("/mrk421Send", data);
}, '/mrk421Send');

OSCdef(\mrk501Send, {|msg|
	var data = msg[3];
	//msg[3].postln;
	Orb.n.sendMsg("/mrk501Send", data);
}, '/mrk501Send');

)

OSCdef(\crabSend).free; /// para pararlo
OSCdef(\mrk421Send).free; /// para pararlo
OSCdef(\mrk501Send).free; /// para pararlo


// demands con valores del csv

~dema = {Demand.kr(Impulse.kr(4), 0, Dseq(b.asFloat*10000000000, inf))};
~deca = {Decay.kr(Demand.kr(Impulse.kr(4), 0, Dseq(b.asFloat*10000000000, inf)) * Impulse.kr(4), 0.3)};
~crab = {Pan2.ar(SinOsc.ar(LinLin.kr(~dema, 0, 1, 100, 1000), 0, ~deca)) * 10};
~dema2 = {Demand.kr(Impulse.kr(6), 0, Dseq(b.asFloat*10000000000, inf))};
~deca2 = {Decay.kr(Demand.kr(Impulse.kr(6), 0, Dseq(b.asFloat*10000000000, inf)) * Impulse.kr(6), 0.3)};
~crab2 = {Pan2.ar(SinOsc.ar(LinLin.kr(~dema2, 0, 1, 100, 5000), 0, ~deca2)) * 10};
~dema3 = {Demand.kr(Impulse.kr(2), 0, Dseq(b.asFloat*10000000000, inf))};
~deca3 = {Decay.kr(Demand.kr(Impulse.kr(2), 0, Dseq(b.asFloat*10000000000, inf)) * Impulse.kr(2), 0.3)};
~crab3 = {Pan2.ar(SinOsc.ar(LinLin.kr(~dema3, 0, 1, 100, 10000), 0, ~deca3)) * 10};

~sin2.play;
~sin3.play;
~sin.play;

