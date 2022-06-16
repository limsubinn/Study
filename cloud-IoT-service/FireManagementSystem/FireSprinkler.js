/* FireSprinkler.js */

// mqtt
var mqtt = require('mqtt');
var client = mqtt.connect('mqtt://localhost:1883');

// topic
var topic = 'fire/sprinkler';


// receive
client.on('connect', function () {
    client.subscribe(topic);
    console.log(topic+" receive!");
});

client.on('message', function (topic, message) {
    console.log(message.toString())
    client.end();
});