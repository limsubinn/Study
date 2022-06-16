/* FileSender.js */

// mqtt
var mqtt = require('mqtt');
var client = mqtt.connect('mqtt://localhost:1883');

// topic
var topic = 'myTopic';

// file read
var fs = require('fs');
var fileName = 'file.txt';
var fileData = fs.readFileSync(fileName, 'utf-8');

// send
client.on('connect', function() {
        client.subscribe(topic);
        client.publish(topic, fileData);
});

client.on('message', function() {
        console.log(topic+" send!");
        client.end();
});