const mqtt = require('mqtt');
var settings = {
  port: 1883,
  host: '192.168.0.110',
  username: 'sshuvo93',
  password: 'light'
};
var client  = mqtt.connect(settings);
client.on('connection',function()
{
  client.subscribe('sshuvo93/Light');
  console.log('subscribed :sshuvo93/Light ');
  client.publish('sshuvo93/Light','1');
})
