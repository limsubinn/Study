/* FireDetector.js */

// mqtt
var mqtt = require('mqtt');
var client = mqtt.connect('mqtt://localhost:1883');

// topic
var topic = 'fire/alarm';

// alarm message
var alarmMessage = "fire!!!!!!!!!!!!!!"

// send
client.on('connect', function() {
	client.subscribe(topic);
    setInterval(function() {
        client.publish(topic, alarmMessage);
        console.log("publish");
    }, 3000);
});

client.on('message', function() {
	console.log(topic+" send!");
});