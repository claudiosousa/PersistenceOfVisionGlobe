netsh wlan set hostednetwork mode=allow ssid=nexus6_ key=povpovpov
netsh wlan start hostednetwork
node server/server.js --port=80 --retry