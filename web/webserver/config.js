var path = require('path');
var baseDir = __dirname;
var config = {
    listenPort : 777,
    baseDir : baseDir,
    viewsDir : path.join(baseDir, '../webapp'),
    appDir : path.join(baseDir, '../webapp'),
    serverAddress : '192.168.1.80',
    serverPort : 7070,
    serialPort : 'com0',
    ampDatasSendIntervall : 1,
    ampTimeOut : 30000
};

module.exports = config; 