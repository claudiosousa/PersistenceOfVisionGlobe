var serialPort = require("serialport");

var sp;

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
            console.log("received: " + data);
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
    serialPort.list(function (err, ports) {
        var arduinoPorts = ports.filter(function (p) {
            return p.manufacturer.indexOf('Arduino') >= 0
        })
        if (arduinoPorts.length == 0)
            throw "No arduino port was found";
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

module.exports.send = function (action, body) {
    var bytes = [];
    bytes.push(action);
    bytes.push(body.length);
    for (var i = 0; i < body.length; ++i) {
        bytes.push(body.charCodeAt(i));
    }
    sp.write(bytes);
}