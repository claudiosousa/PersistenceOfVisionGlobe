define(['app', 'uikitService', 'dataService'], function (app) {
    'use strict';
    app.register.controller('homeController', ['$rootScope', '$scope', 'dataService',
    function ($rootScope, $scope, dataService) {
        $scope.requestResult = '';
        $scope.getPanelButtonClass = function (selector) {
            var relatedElement = $(selector);
            return relatedElement.hasClass('uk-active') ? 'open' : '';
        };

        $scope.onrequest = function (request) {
            switch (request) {
                case 'speed':
                    var speed = parseInt($scope.speed);
                    dataService.setSpeed(speed).then(function (result) {
                        debugger;
                        $scope.requestResult = JSON.stringify(result);
                    });
            }
        };
    }]);
});
