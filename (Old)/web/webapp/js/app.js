define(['angular', 'routeResolver', 'angularRoute', 'angularTranslate', 'angularAnimate', 'proxyService'], function (angular)
{'use strict';

var povApp = angular.module('povApp', ['ngRoute', 'routeResolverServices', 'ngAnimate', 'config', 'pascalprecht.translate', 'proxyServices']);

    povApp.config(['$httpProvider', '$translateProvider',
    function($httpProvider, $translateProvider)
    {
        // Load translation files
        $.getJSON('translations/translations-fr.json', function(data)
        {
            $translateProvider.translations('fr', data);
        });

        $.getJSON('translations/translations-en.json', function(data)
        {
            $translateProvider.translations('en', data);
        });

        $translateProvider.preferredLanguage(window.sessionStorage.lang || 'en');
    }]);

    povApp.filter('getByProperty', function()
    {
        return function(propertyName, propertyValue, collection)
        {
            var i = 0, len = collection.length;
            for (; i < len; i++) {
                if (collection[i][propertyName] == propertyValue) {
                    return collection[i];
                }
            }
            return null;
        };
    });

    povApp.filter('find', function()
    {
        return function(collection, predicate)
        {
            var i = 0, len = collection.length;
            for (; i < len; i++) {
                if (predicate(collection[i]) === true) {
                    return collection[i];
                }
            }
            return null;
        };
    });

    povApp.run(function($rootScope, config)
    {
        $rootScope.appInfos = config.appInfos;
    });

    return povApp;
});
