// aquí extraemos la información

x = CSVFileReader.read(thisProcess.nowExecutingPath.dirname +/+"../csv/HAWC_fluxlc_Crab.csv", true, true).postcs;

a = Array.fill(472, { arg i; x[i][0].split($ ) });
b = Array.fill(472, { arg i; a[i][2] });

// proxystyle
Orb.start("127.0.0.1", 5612); // la dirección de la otra compu
p = ProxySpace.push(s.boot)
p.quant = 4;

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

// osc to OF

~crabSend = {SendReply.kr(Impulse.kr(15), '/crabSend', ~dema2.kr)};

(

OSCdef(\crabSend, {|msg|
	var data = msg[3];
	//msg[3].postln;
	Orb.n.sendMsg("/crabSend01", data);
}, '/crabSend');

)



