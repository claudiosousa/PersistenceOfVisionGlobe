var express = require('express');
var path = require('path');
var httpServ = require('http');
var WebSocketServer = require('ws').Server;
var arduinoProxy = require('./arduinoProxy.js');
var argv = require('argv').option({
    name: 'port',
    short: 'p',
    type: 'string',
    description: 'Port'
});;

var app = express();

app.use(express.static(path.join(__dirname, '../webapp')));

/*
app.post('/someUrl', bodyParser.json());
app.post('/someUrl', function (req, res, next) {
    res.send(req.body.input + "_response");
});
*/


arduinoProxy.connect(function () {
    websocketserver = httpServ.createServer(app).listen(argv.port, function () {
        console.log('Webapp listening on port %s', websocketserver.address().port);
    });

    var wss = new WebSocketServer({ server: websocketserver });
    wss.on('connection', function (ws) {

        ws.on('message', function (message) {
            console.log('received from socket: %s', message.length > 25 ? message.substr(0, 20) + "..." : message);
            var message = JSON.parse(message);
            arduinoProxy.send(message.action, message.body);
            //ws.send(message);
        });
        //ws.send('something');
    });
})
