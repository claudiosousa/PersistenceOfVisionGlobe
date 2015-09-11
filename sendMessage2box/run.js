var serialport = require("serialport");
var SerialPort = serialport.SerialPort;
var portName = process.argv[2];
console.log('portName: '+portName);

if (!portName){
// list serial ports:
serialport.list(function (err, ports) {
  ports.forEach(function(port) {
    console.log(port.comName);
  });
});
return;
}


var myPort = new SerialPort(portName, {
   baudRate: 57600,
   
      dataBits: 8, 
	     parity: 'none', 
	     stopBits: 1, 
	     flowControl: false 
		 
 });
 
myPort.on('open', showPortOpen);
myPort.on('close', showPortClose);
myPort.on('error', showError);
	myPort.on('data', saveLatestData);

function showPortOpen() {
   console.log('port open. Data rate: ' + myPort.options.baudRate);
   myPort.write("AAAAAAAA\r\n", function(err, results) {
    console.log("err: " + err);
    console.log("results: " + JSON.stringify(results));
  });  
}
 
function saveLatestData(data) {
   console.log(data.toString());
}
 
function showPortClose() {
   console.log('port closed.');
}
 
function showError(error) {
   console.log('Serial port error: ' + error);
}
