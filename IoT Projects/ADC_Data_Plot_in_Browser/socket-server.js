const express = require('express');
const app = express();
const http = require('http').Server(app);
const io = require('socket.io')(http);
const path = require('path');
const fs = require('fs');
app.get('/',function(req,res)
{
  //res.sendFile(__dirname+'/index.html');
  res.sendFile(__dirname+'/public/index.html');
});
app.use('/public',express.static(path.join(__dirname,'public')));
//app.use('/docs',express.static(path.join(__dirname,'node_modules/chart.js/dist/docs')));
//http.listen(8000,'192.168.0.110');
//http.listen(80,function()
http.listen(80,'192.168.0.110',function()
{
  var host = http.address().address;
  var port = http.address().port;
  console.log('Server listening at http://%s:%s', host, port);
});
var incomingData = [];
var i=0;
var userName = []; //Device userName will be saved in this object
var users = {}; //User Socket Id for corresponding userName will be saved in this object
io.on('connection', function (socket)
 {
   console.log("New client Connected ");
   socket.on('browser-login', function (incoming)
   {
      users[incoming.id] = socket.id;
      console.log('Browser Connected,ID: : '+users[incoming.id]);
    });

      socket.on('D', function (data)
      {
        //var start = new Date();
        console.log(data+"-"+i);
        //incomingData.push(data);
       socketId = users.browser1;
       if(socketId)//check if device is connected
        {
          io.sockets.connected[socketId].emit('D',data); //Send data to a specific socketId
          i++;
        }
        else
        {
          console.log('Device disconnected');
        }
        i++;
        //var end = new Date()-start;
        //console.log('Time: '+ end);
     });

  //
  //socket.broadcast.emit('Valo aso ni ESP8266!!');
  //socket.emit('event','Hello ESP, HOW Are you?');
  //socket.emit('event','Valo Aso naki ESP8266!!');
  // for(var i=0;i<1000;i++)
  // {
  //   socket.emit('event','Hello  ESP8266--'+i);
  // }
  socket.on('disconnect',function()
  {
    console.log('A User disconnected: ');
  });
});
// setInterval(function()
// {
//   console.log(incomingData);
// },3000);
