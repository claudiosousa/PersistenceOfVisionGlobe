// Read config
$.getJSON('config.json', function(json)
{
    var config = json;

    config.route = {
        baseUrl : config.baseUrl, /* Must be absolute url and begin with '/' */
        paths : {
            jqueryUI: 'bower_components/jqueryui/ui/jquery-ui',
            jqueryUIWidget: 'bower_components/jqueryui/ui/jquery.ui.widget',
            jqueryUICore: 'bower_components/jqueryui/ui/jquery.ui.core',
            jqueryUIPosition: 'bower_components/jqueryui/ui/jquery.ui.position',
            jqueryUIMenu: 'bower_components/jqueryui/ui/jquery.ui.menu',
            jqueryUIAutocomplete: 'bower_components/jqueryui/ui/jquery.ui.autocomplete',
            jqueryUIDatePickerI18n: 'bower_components/jqueryui/ui/i18n/jquery-ui-i18n',
            angular: 'bower_components/angular/angular',
            angularDateParser: 'bower_components/angular-dateparser/dateparser',
            angularRoute: 'bower_components/angular-route/angular-route',
            angularResource: 'bower_components/angular-resource/angular-resource',
            angularAnimate: 'bower_components/angular-animate/angular-animate',
            angularTranslate: 'bower_components/angular-translate/angular-translate',
            uikit: 'bower_components/uikit/dist/js/uikit',
            numeral: 'bower_components/numeral/numeral',
            app : 'js/app',
            routes : 'js/routes',
            routeResolver : 'js/providers/route-resolver',
            socketProvider : 'js/providers/socket-provider',
            homeController : 'js/controllers/home-controller',
            logsController : 'js/controllers/logs-controller',
            proxyService : 'js/services/proxy-service',
            dataService : 'js/services/data-service',
            uikitService: 'js/services/uikit-service'
        },
        css : {
            uikitStyle: 'bower_components/uikit/dist/css/uikit.css',
        },
        templates : {
            homeTemplate : '{baseUrl}templates/home.html'
        },
        shim : {
            'angular' : {
                'exports' : 'angular'
            },
            'jqueryUIPosition' : ['jqueryUI'],
            'jqueryUIMenu' : ['jqueryUI'],
            'jqueryUIAutocomplete' : ['jqueryUI'],
            'jqueryUIWidget' : ['jqueryUI'],
            'jqueryUIDatePickerI18n' : ['jqueryUI'],
            'promiseTracker' : ['angular'],
            'angularAnimate' : ['angular'],
            'angularBusy' : ['angular', 'angularAnimate'],
            'angularRoute' : ['angular'],
            'angularResource' : ['angular'],
            'angularTranslate': ['angular'],
            'angularDateParser': ['angular'],
        },
        priority : ['angular']
    };

    // Format config
    function formatConfig(section)
    {
        var regex = new RegExp('^\{.*}', 'i');                
        for (var name in section) {
            if ( typeof section[name] == "object") {
                formatConfig(section[name]);
            }
            else if ( typeof section[name] == "string") {
                var match = regex.exec(section[name]);
                if (match) {
                    var len  = match[0].length;
                    var keyw = match[0].substring(1, len - 1);
                    if (config[keyw]) {
                        section[name] = config[keyw] + section[name].substring(len);
                    }
                }
            }
        }
    };
    formatConfig(json);

    // http://code.angularjs.org/1.2.1/docs/guide/bootstrap#overview_deferred-bootstrap
    window.name = 'NG_DEFER_BOOTSTRAP!';

    require(config.route, ['angular', 'app', 'routes'], function(angular, app)
    {
        var $html = angular.element(document.getElementsByTagName('html')[0]);

        angular.module('config', []).constant('config', config);

        angular.element().ready(function()
        {
            angular.resumeBootstrap([app['name']]);
        });
    });
});
