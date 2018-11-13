// crab

x = CSVFileReader.read(thisProcess.nowExecutingPath.dirname +/+"../csv/HAWC_fluxlc_Crab_.csv", true, true).postcs;

a = Array.fill(472, { arg i; x[i+1][0].split($ ) });
b = Array.fill(472, { arg i; a[i][0] });

// mrk421

y = CSVFileReader.read(thisProcess.nowExecutingPath.dirname +/+"../csv/HAWC_fluxlc_Mrk421_.csv", true, true).postcs;

c = Array.fill(471, { arg i; y[i+1][0].split($ ) });
d = Array.fill(471, { arg i; c[i][0] });

/// mrk501

z = CSVFileReader.read(thisProcess.nowExecutingPath.dirname +/+"../csv/HAWC_fluxlc_Mrk501_.csv", true, true).postcs;

e = Array.fill(479, { arg i; z[i+1][0].split($ ) });
f = Array.fill(479, { arg i; e[i][0] });

// proxy

Orb.start("127.0.0.1", 5612); // la dirección de la otra compu. Se necesita la librería PiranhaLab
p = ProxySpace.push(s.boot);
p.quant = 4;

// fuentes como un continuo

~crab = {Demand.kr(Impulse.kr(4), 0, Dseq(b.asInt, inf))};


~crab = {Demand.kr(Impulse.kr(4), 0, Dseq(b.asFloat*10000000, inf))};
~mkr421 = {Demand.kr(Impulse.kr(4), 0, Dseq(d.asFloat*10000000000, inf))};
~mkr501 = {Demand.kr(Impulse.kr(4), 0, Dseq(f.asFloat*10000000000, inf))};

// replys que jalan el demand

~crabSend = {SendReply.kr(Impulse.kr(15), '/crabSend', ~crab.kr)};
~mkr421Send = {SendReply.kr(Impulse.kr(15), '/mkr421Send', ~mkr421.kr)};
~mkr501Send = {SendReply.kr(Impulse.kr(15), '/mkr501Send', ~mkr501.kr)};

// oscdef

(

OSCdef(\crabSend, {|msg|
	var data = msg[3];
	msg[3].postln;
	Orb.n.sendMsg("/crabSend", data);
}, '/crabSend');

OSCdef(\mkr421Send, {|msg|
	var data = msg[3];
	//msg[3].postln;
	Orb.n.sendMsg("//mkr421Send", data);
}, '/mkr421Send');

OSCdef(\mkr501Send, {|msg|
	var data = msg[3];
	//msg[3].postln;
	Orb.n.sendMsg("/mkr501Send", data);
}, '/mkr501Send');

)

OSCdef(\crabSend).free; /// para pararlo
OSCdef(\mkr421Send).free; /// para pararlo
OSCdef(\mkr501Send).free; /// para pararlo


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

