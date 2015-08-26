var serialPort = require("serialport");

var sp;
var waitingPackets = [];
var isWaitingForPacketReceivedReponse = false;
var initiateCommunication = function (port, cb) {

    sp = new serialPort.SerialPort(port, {
        baudrate: 115200,
        parser: serialPort.parsers.readline("\n")
    });

    sp.on('error', function (error) {
        console.log('Error received: ' + error);
    })

    sp.on('close', function (error) {
        console.log('Connection closed');
    })

    sp.on("open", function () {
        console.log('Open connection');

        sp.on('data', function (data) {
            console.log("received from arduino: " + data);
            /*for (var i = 0; i < data.length; ++i)
                console.log(data.charCodeAt(i));
                */
            if (data.indexOf("DPR") == 0)
                checkIfCanSendNextPacket(true);
           
            //sendMessage(sp);
        });


        /*
        sp.write("ls\n", function (err, results) {
            console.log('err ' + err);
            console.log('results ' + results);
        });
        */
        cb();
    });

}



module.exports.connect = function (cb) {
	var searchForArduino = function(){
		serialPort.list(function (err, ports) {
			var arduinoPorts = ports.filter(function (p) {
				return p.manufacturer.indexOf('Arduino') >= 0
			})
			if (arduinoPorts.length == 0){
				console.log( "No arduino port was found");
				setTimeout(searchForArduino, 1000);
			}
			if (arduinoPorts.length > 1)
				console.log("More than one arduino port was found. Picking first...");

			console.log("Connecting to arduino on port '" + arduinoPorts[0].comName + "'")
			initiateCommunication(arduinoPorts[0].comName, cb);
			/*
			  ports.forEach(function(port) {
				console.log(port.comName);
				console.log(port.pnpId);
				console.log(port.manufacturer);
			  });
			  */
		});
	}
	searchForArduino();
}

var checkIfCanSendNextPacket = function (packetReceived) {
    if (packetReceived)
        isWaitingForPacketReceivedReponse = false;
    if (isWaitingForPacketReceivedReponse)
        return;
    if (waitingPackets.length == 0)
        return;
    isWaitingForPacketReceivedReponse = true;
    var nextPacket =  waitingPackets.splice(0, 1)[0];
    console.log("Sending pckg of size: " + nextPacket.length);
    sp.write(nextPacket);
}

module.exports.send = function (action, data) {
    var header = [];
    header.push(action);
    var dataLength = data.length;
    header.push(dataLength >> 8);
    header.push(dataLength % 256);
    console.log("Action byte1: " + Math.trunc(dataLength / 256));
    console.log("Action byte2: " + dataLength % 256);
    waitingPackets.push(header);
    while (data.length > 0)
        waitingPackets.push(data.splice(0, Math.min(32, data.length)));

    checkIfCanSendNextPacket();
}