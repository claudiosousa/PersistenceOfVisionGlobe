define(['app'], function(app)
{'use strict';

    app.register.service('dataService', ['proxyService',
    function(proxyService)
    {
        return {
            setSpeed : function(speed)
            {
                return proxyService({
                    method : 'get',
                    request: 'setspeed',
                    speed: speed
                });
            },
         };
    }]);
});