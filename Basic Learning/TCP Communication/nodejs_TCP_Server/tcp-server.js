
var net = require('net');

var server = net.createServer(function(socket) {
    console.log('Turn ON LED')
    socket.write('\nTurn ON LED\r\n');
    socket.pipe(socket);
    socket.on('data',function(data)
  { //When client sent data this is called
    console.log(String(data));
  });
});

server.listen(8000, '192.168.0.110', function()
{
  console.log('Server is listening to the port 8000');
});
