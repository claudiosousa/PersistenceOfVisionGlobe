var express = require('express');
var user = require('./routes/user');
var http = require('http');
var path = require('path');
var config = require('./config');
var ejs = require('ejs');
var server = require("./server");
var log4js = require('log4js');

var logtofile = false;
var loglevel = log4js.levels.INFO;
var app = express();

// Read command line arguments
process.argv.forEach(function (val, index, array) {
    switch (val) {
        case '-logdbg':
            loglevel = log4js.levels.DEBUG;
            break;

        case '-logtofile':
            logtofile = true;
            break;
    }
});

var appenders = [{
    type: 'console',
}];

if (logtofile) {
    appenders.push({
        type: 'file',
        filename: config.baseDir + '\\server.log',
    });
}

log4js.configure({
    appenders: appenders
});

var logger = log4js.getLogger();
logger.setLevel(loglevel);

// all environments
app.set('port', config.listenPort || 8000);
app.set('views', config.viewsDir);
app.engine('html', ejs.renderFile);
app.use(express.favicon());
app.use(log4js.connectLogger(logger, {
    level: loglevel
}));
app.set('view engine', 'html');
app.use('/', express.static(config.appDir));
app.get('/users', user.list);
app.use(function (req, res, next) {
    res.render('index');
});

// development only
if ('development' == app.get('env')) {
    app.use(express.errorHandler());
}

var httpServer = http.createServer(app).listen(app.get('port'), function(){
    console.log('Express server listening on port ' + app.get('port'));
});

server.start(httpServer, config, logger)

