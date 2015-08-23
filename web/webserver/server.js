var fs = require('fs');
var path = require('path');
var Struct = require('./node_modules/struct/index.js').Struct;
var SerialPort = require('serialport').SerialPort;
var socketio = require('socket.io');
var net = require('net');
var http = require('http');
var underscore = require('underscore');

var logger = null;
var config = null;

var clients = {};

const SPEEDREQUEST = 2; 

function startServer(httpServer, cfg, loggr)
{
    logger = loggr;
    config = cfg;
    initSocketIO(httpServer);
}

function initSocketIO(httpServer)
{
    var io = socketio.listen(httpServer);

    io.sockets.on('connection', function(socket)
    {
        var client = {
            socket : socket,
            _watchId : 0,
            _watchStatus : false,
            nextDataRequest : 0,
            nextStatusRequest : 0,
            slowRequestTime : 0,
            watchId : function(value)
            {
                if ( typeof value == 'undefined') {
                    return Date.now() > this.nextDataRequest ? this._watchId : 0;
                }
                else {
                    this._watchId = value;
                    this.nextDataRequest = 0;
                }
            },
            watchStatus : function(value)
            {
                if ( typeof value == 'undefined') {
                    return this._watchStatus && Date.now() > this.nextStatusRequest;
                }
                else {
                    this._watchStatus = value;
                    this.nextStatusRequest = 0;
                }
            }
        };

        logger.info(socket.id + ' client connected');

        /*var serialPortModule = require("serialport");
        serialPortModule.list(function (err, ports) {
            ports.forEach(function (port) {
                logger.info(port);
            });
        });*/

        socket.on('disconnect', function ()
        {
            delete clients[socket.id];
            logger.info(socket.id + " client disconnected");
        });

        socket.on('request', function(params, callback)
        {
            if (!params || !params.request) {
                // Error
                params = params || {};
                params.error = 'invalid request parameters.';
                logger.error(socket.id + ' request error: ' + params.error);
                callback || callback(params);
                return;
            }

            logger.info(socket.id + ' request ' + params.request);
            try {
                switch(params.request)
                {
                    case 'setspeed':
                        //params.error = err;
                        //params.status = 'fail';

                        // Prepare struct request to arduino
                        var speedRequest = Struct()
                            .word8Sle('request')
                            .word8Sle('result')
                            .word16Ule('param')
                        speedRequest.allocate();
                        var proxy = speedRequest.fields;
                        proxy.request = SPEEDREQUEST;
                        proxy.result = 1;
                        proxy.param = params.speed;
                        var buffer = speedRequest.buffer();

                      
                        // Send to arduino
                        var port = new SerialPort('COM5', {
                            baudrate: 9600,
                            // defaults for Arduino serial communication
                            dataBits: 8, 
                            parity: 'none', 
                            stopBits: 1, 
                            flowControl: false 
                        }, false);

                        port.on('error', function (err) {
                            if (err) {
                                throw err;
                            }
                        });

                        port.open(function (err) {
                            if (err) {
                                throw err;
                            }
                            port.write('totoz', function (err, res) {
                                if (err) {
                                    throw err;
                                }
                                logger.info('data writed');
                                port.close(function (err) {
                                    if (err) {
                                        throw err;
                                    }
                                    logger.info('port closed');
                                    port.open(function (err) {
                                        if (err) {
                                            throw err;
                                        }

                                        logger.info('port opened');
                                        port.on('data', function (d) {
                                            logger.info('data received ' + d);
                                            /*port.close(function (err) {
                                                if (err) {
                                                    throw err;
                                                }
                                                logger.info('port closed');
                                            });*/
                                        });
                                    });
                                });
                            });
                        });

                        // Get result from arduino
                        var result = Struct()
                            .word8Sle('request')
                            .word8Sle('result')
                            .word16Ule('param')
                        result._setBuff(buffer);

                        params.status = 'ok';
                        params.data = result;
                        sendResponse(params);
                        return;

                    default:
                        throw "Not implemented request " + params.request;

                }
            }
            catch (e) {
                console.error("socket.io request: " + e.message || e);
                params.error = e.message;
                params.status = 'fail';
            }

            function sendResponse(result)
            {
                if (!result.method || result.method == 'post' || !callback) {
                    socket.emit('response', {
                        result : result
                    });
                }
                else {
                    callback(result);
                }
            }

            sendResponse(params);
        });

        clients[socket.id] = client;
    });
}

exports.start = startServer;
