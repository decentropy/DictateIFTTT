var host = "https://maker.ifttt.com/trigger/",
  event = "push",
  key = "your maker key here";

function send_message(message) {
  console.log(host + event + "/with/key/" + key);
  var url = host + event + "/with/key/" + key,
    data = {"value1": message};

  sendPOSTRequest(url, data, function() {
    console.log("Error!");
  });
}

function sendPOSTRequest(url, data, fallback) {
  var req = new XMLHttpRequest();
 
  req.onreadystatechange = function(e) {
    if (req.readyState == 4 && req.status == 200) {
      var response = JSON.parse(req.responseText);
      console.log("Response was ", response);
      
      if (response !== undefined && !response.error) {
        console.log("Message sent successfully.");                
      } else {
        console.log(response.error);
        if (fallback) fallback();
      }
    } else if (req.status == 404 || req.status == 500) {
      console.log("Error " + req.status);
      if (fallback) fallback();
    }
    
  };

  req.open("POST", url);
  req.setRequestHeader("Content-Type", "application/json");
  req.send(JSON.stringify(data));
}

Pebble.addEventListener("appmessage", function(e) {
  var message = e.payload["0"];
  console.log("Received message: " + message);
  send_message(message);
});