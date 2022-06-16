/* FileReceiver.js */

// mqtt
var mqtt = require('mqtt');
var client = mqtt.connect('mqtt://localhost:1883');

// topic
var topic = 'myTopic';

// saved filename
var fileName = 'fileRecv.txt';

// file system
var fs = require('fs');

// receive
client.on('connect', function () {
        client.subscribe(topic);
        console.log(topic+" receive!");
});

client.on('message', function (topic, message) {
        fs.writeFileSync(fileName, message);
        client.end();
});