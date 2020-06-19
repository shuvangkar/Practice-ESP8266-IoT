var socket = io();
socket.emit('browser-login', {id: 'browser1'});


// document.body.addEventListener("myEventName", doSomething, false);
//
// function doSomething(e) {
//     alert("Event is called: " + e.detail);
// }
//
// var myEvent = new CustomEvent("myEventName",
// {
//   'detail' : Math.round(Math.random()*1000)
// });
// document.body.dispatchEvent(myEvent);

var data = [];
var index = 0;
var bufferFull = new CustomEvent("full", {detail : "hello world"}); //Creating the event
socket.on('D', function (incomingData)
{
  data.push(incomingData);
  index++;

  //console.log(incomingData);
  if(index>=25)
  {
    document.body.dispatchEvent(bufferFull);
    console.log(data);
    index = 0;
  }
});

document.body.addEventListener('full',updateGraph,false);
var arrayLength = 30
var newArray = []
for(var i = 0; i < arrayLength; i++)
{
  var y = Math.round(Math.random()*10) + 1
  newArray[i] = y
}

Plotly.plot('graph', [{
  y: newArray,
  mode: 'lines',
  line: {color: '#80CAF6'}
}]);

function updateGraph()
{
  var y = data;
  newArray = newArray.concat(y)
  newArray.splice(0, 1)

  var data_update = {
    y: [newArray]
};

  Plotly.update('graph', data_update)

}
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
TESTER = document.getElementById('tester');
	Plotly.plot( TESTER,
        [{
	      x: [1, 2, 3, 4, 5],
	      y: [1, 2, 4, 8, 16] }],
        {
	margin: { t: 0 } } );


  var button = document.getElementById("myBtn");
  button.addEventListener('click',function()
  {

      socket.emit('Pong','Turn On LED');
  });
