'use strict';

define(['angular'], function(angular)
{
	angular.module('routeResolverServices', ['config']).provider('routeResolver', function(config)
	{
		this.$get = function()
		{
			return this;
		};

		this.route = function()
		{
			var resolve = function(template, controller, dependencies, css)
			{
				var routeDef = {};
				routeDef.templateUrl = config.route.templates[template];
				routeDef.controller = controller;
				routeDef.reloadOnSearch = false;
				routeDef.resolve = {
					load : ['$q', '$rootScope',
					function($q, $rootScope)
					{
						angular.forEach(css || [], function(cssName)
						{
							var link = document.createElement("link");
							link.type = "text/css";
							link.rel = "stylesheet";
							link.href = config.route.css[cssName];
							document.getElementsByTagName("head")[0].appendChild(link);
						});

						return resolveDependencies($q, $rootScope, dependencies || [controller]);
					}]

				};

				return routeDef;
			}, resolveDependencies = function($q, $rootScope, dependencies)
			{
				var defer = $q.defer();
				require(dependencies, function()
				{
					defer.resolve();
					$rootScope.$apply();
				});

				return defer.promise;
			};

			return {
				resolve : resolve
			};
		}();
	});
});
