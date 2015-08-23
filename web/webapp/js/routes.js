define(['app'], function(app)
{
    return app.config(['$routeProvider', 'routeResolverProvider', '$controllerProvider', '$compileProvider', '$filterProvider', '$provide', '$httpProvider', '$locationProvider', 'config',
    function($routeProvider, routeResolverProvider, $controllerProvider, $compileProvider, $filterProvider, $provide, $httpProvider, $locationProvider, config)
    {
        $locationProvider.html5Mode(true).hashPrefix('!');

        app.register = {
            controller : $controllerProvider.register,
            directive : $compileProvider.directive,
            filter : $filterProvider.register,
            factory : $provide.factory,
            service : $provide.service,
            provider : $provide.provider,
            constant : $provide.constant
        };

        // Define routes - controllers will be loaded dynamically
        var route = routeResolverProvider.route;

        // route.resolve(page, controller, [dependencies], [css])
        $routeProvider.when(config.page.home, route.resolve('homeTemplate', 'homeController', ['homeController'], ['uikitStyle']));

        $routeProvider.otherwise({
            redirectTo : config.page.home
        });
    }]);
});
