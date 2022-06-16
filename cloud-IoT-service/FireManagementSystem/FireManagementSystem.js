/* FireManagementSystem.js */

// mqtt
var mqtt = require('mqtt');
var client = mqtt.connect('mqtt://localhost:1883');

// topic
var recvTopic = 'fire/alarm';
var sendTopic = 'fire/sprinkler';


// receive
client.on('connect', function () {
    client.subscribe(recvTopic);
    console.log(recvTopic+" receive!");
});

client.on('message', function (recvTopic, message) {
    console.log("message arrive: " + message);

    // send
    // client.subscribe(sendTopic);
    client.publish(sendTopic, message);
    console.log("message send: " + message)
});