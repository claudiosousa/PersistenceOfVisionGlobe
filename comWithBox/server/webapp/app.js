window.ws = new WebSocket('ws:/' + location.hostname + ':81');

ws.onopen = function () {
    $(document.body).removeClass('disconnected')
};


ws.onclose = function () {
    $(document.body).addClass('disconnected')
    alert('Connection closed')
}

ws.onmessage = function (message) {
    alert('Received: '+message.data);
};

var startMotor = function () {
    ws.send(JSON.stringify({ action: 1, body: ""}));
}

var stopMotor = function () {
    ws.send(JSON.stringify({ action: 0, body: "" }));
}