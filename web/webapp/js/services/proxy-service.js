define(['angular', 'socketProvider'], function(angular)
{
    angular.module('proxyServices', ['socketProviders']).service('proxyService', ['$http', '$q', '$cacheFactory', 'socket', '$rootScope',
    function($http, $q, $cacheFactory, socket, $rootScope)
    {
        // This is the extent of $cacheFactory's configuration
        var metaCache = $cacheFactory('metaCache', {
            // This cache can hold 1000 items
            capacity : 1000
        });

        socket.on('response', function(receivedData)
        {
            var result = receivedData.result;
            if (result.status == 'ok') {
                if (result.cachekey) {
                    // Update cache
                    if (result.mode == 'update') {
                        var datas = metaCache.get(result.cachekey);
                        datas.push(result.data);
                        metaCache.put(result.cachekey, datas);
                        result.data = datas;
                    }
                    else {
                        metaCache.put(result.cachekey, result.data);
                    }
                }
                $rootScope.$emit('response', result);
            }
            else {
                $rootScope.$emit('error', result);
            }
        });

        return function(params)
        {
            var deferred = $q.defer();

            params.data = params.data || {};

            var cachekey = params.cachekey;
            var data = cachekey && metaCache.get(cachekey);
            if (data) {
                if (params.method == 'post') {
                    params.data = data;
                    $rootScope.$emit('response', params);
                }
                deferred.resolve(data);
            }
            else {
                if (!params.method || params.method == 'post') {
                    socket.emit('request', params);
                }
                else {
                    socket.emit('request', params, function(result)
                    {
                        if (result.status == 'ok') {
                            if (cachekey) {
                                metaCache.put(cachekey, result.data);
                            }

                            deferred.resolve(result.data, result.status, result.headers, params);
                        }
                        else {
                            deferred.reject(result, result.status, result.headers, params);
                        }
                    });
                }
            }

            return deferred.promise;
        };
    }]);
});
