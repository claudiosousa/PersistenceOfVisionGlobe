netsh wlan set hostednetwork mode=allow ssid=nexus6 key=povpovpov
netsh wlan start hostednetwork
node server/server.js --port=80 --retry