#include "main.h"

// extern const char homePageStart[] asm("_binary_src_controller_html_start");
// extern const char homePageEnd[] asm("_binary_controller_html_end");

String homePage = "<!doctype html><html><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width,initial-scale=1\"><title>Controller</title><link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha3/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-KK94CHFLLe+nY2dmCWGMq91rCGa5gtU4mk92HdvYe+M/SXH301p5ILy+dN9+nJOZ\" crossorigin=\"anonymous\"><script src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha3/dist/js/bootstrap.bundle.min.js\" integrity=\"sha384-ENjdO4Dr2bkBIFxQpeoTz1HIcje39Wm4jDKdf19U8gI4ddQ3GYNS7NTKfAdVQSZe\" crossorigin=\"anonymous\"></script><script src=\"https://code.jquery.com/jquery-3.6.4.min.js\" integrity=\"sha256-oP6HI9z1XaZNBrJURtCoUT5SUnxFr8s3BzRl+cbzUq8=\" crossorigin=\"anonymous\"></script><script>let camera_ip=\"http://192.168.1.247\",robot_ip=\"http://192.168.1.4\"</script></head><body><div class=\"container\"><div class=\"row mt-3\"><div class=\"col\"></div><div class=\"col\"><center><div class=\"card p-0 m-0\" style=\"width:640px\"><img id=\"snapshot\" width=\"640px\" height=\"480px\" class=\"card-img\"><div class=\"card-img-overlay p-0 m-0\"><canvas id=\"fdc\" width=\"638px\" height=\"478px\"></canvas></div></div></center></div><div class=\"col\"></div></div><div class=\"row\" style=\"margin-top:40px\"><div class=\"col-sm\"></div><div class=\"col-sm-4\"><center><b>Motor</b><br><div class=\"btn-group btn-group-lg\" role=\"group\" aria-label=\"Basic example\"><button class=\"btn-dpad btn btn-light\">↖</button><button class=\"btn-dpad btn btn-primary\" ontouchstart=\"m(0)\" onmousedown=\"m(0)\" onmouseup=\"m(999)\">↑</button><button class=\"btn-dpad btn btn-light\">↗</button></div><br><div class=\"btn-group btn-group-lg\" role=\"group\" aria-label=\"Basic example\"><button class=\"btn-dpad btn btn-primary\" ontouchstart=\"m(2)\" onmousedown=\"m(2)\" onmouseup=\"m(999)\">←</button><button class=\"btn-dpad btn btn-light\">↔</button><button class=\"btn-dpad btn btn-primary\" ontouchstart=\"m(3)\" onmousedown=\"m(3)\" onmouseup=\"m(999)\">→</button></div><br><div class=\"btn-group btn-group-lg\" role=\"group\" aria-label=\"Basic example\"><button class=\"btn-dpad btn btn-light\">↙</button><button class=\"btn-dpad btn btn-primary\" ontouchstart=\"m(1)\" onmousedown=\"m(1)\" onmouseup=\"m(999)\">↓</button><button class=\"btn-dpad btn btn-light\">↘</button></div></center></div><div class=\"col-sm-4\"><center><b>Camera</b><br><div class=\"btn-group btn-group-lg\" role=\"group\" aria-label=\"Basic example\"><button class=\"btn-dpad btn btn-light\" ontouchstart=\"c(5)\" onmousedown=\"c(5)\" onmouseup=\"c(999)\">↖</button><button class=\"btn-dpad btn btn-warning\" ontouchstart=\"c(0)\" onmousedown=\"c(0)\" onmouseup=\"c(999)\">↑</button><button class=\"btn-dpad btn btn-light\" ontouchstart=\"c(6)\" onmousedown=\"c(6)\" onmouseup=\"c(999)\">↗</button></div><br><div class=\"btn-group btn-group-lg\" role=\"group\" aria-label=\"Basic example\"><button class=\"btn-dpad btn btn-warning\" ontouchstart=\"c(2)\" onmousedown=\"c(2)\" onmouseup=\"c(999)\">←</button><button class=\"btn-dpad btn btn-warning\" ontouchstart=\"c(4)\" onmousedown=\"c(4)\" onmouseup=\"c(999)\">↔</button><button class=\"btn-dpad btn btn-warning\" ontouchstart=\"c(3)\" onmousedown=\"c(3)\" onmouseup=\"c(999)\">→</button></div><br><div class=\"btn-group btn-group-lg\" role=\"group\" aria-label=\"Basic example\"><button class=\"btn-dpad btn btn-light\" ontouchstart=\"c(7)\" onmousedown=\"c(7)\" onmouseup=\"c(999)\">↙</button><button class=\"btn-dpad btn btn-warning\" ontouchstart=\"c(1)\" onmousedown=\"c(1)\" onmouseup=\"c(999)\">↓</button><button class=\"btn-dpad btn btn-light\" ontouchstart=\"c(8)\" onmousedown=\"c(8)\" onmouseup=\"c(999)\">↘</button></div></center></div><div class=\"col-sm\"></div></div><div class=\"row my-5\"><div class=\"col\"></div><div class=\"col-6\"><div class=\"form-check form-switch\"><input class=\"form-check-input\" type=\"checkbox\" role=\"switch\" onchange=\"l(this)\"><label class=\"form-check-label\" for=\"flexSwitchCheckDefault\">Light</label></div><div class=\"form-check form-switch\"><input class=\"form-check-input\" type=\"checkbox\" role=\"switch\" onchange=\"fd(this)\"><label class=\"form-check-label\" for=\"flexSwitchCheckDefault\">Face Detect</label></div><div class=\"form-check form-switch\"><input class=\"form-check-input\" type=\"checkbox\" role=\"switch\" id=\"rendering-option\" checked=\"checked\"><label class=\"form-check-label\" for=\"flexSwitchCheckDefault\">Render Overlay</label></div><div class=\"btn-toolbar mt-2\" role=\"toolbar\" aria-label=\"Toolbar with button groups\"><div class=\"btn-group me-2\" role=\"group\" aria-label=\"First group\"><button type=\"button\" class=\"btn btn-primary btn-sm\" onclick=\"oc()\">OTA Camera</button></div><div class=\"btn-group me-2\" role=\"group\" aria-label=\"Second group\"><button type=\"button\" class=\"btn btn-primary btn-sm\" onclick=\"or()\">OTA Robot</button></div></div></div><div class=\"col\"></div></div></div><script>var intervalId=null,canvas=document.getElementById(\"fdc\"),ctx=canvas.getContext(\"2d\");let stream_width=320,stream_height=240,stream_score_threshold=.05;function m(t){$.get(robot_ip+\"/robot?d=\"+t)}function c(t){$.get(robot_ip+\"/cam?d=\"+t)}function l(t){$(t).is(\":checked\")?$.get(camera_ip+\"/ledon\"):$.get(camera_ip+\"/ledoff\")}function fd(t){$(t).is(\":checked\")?$.get(camera_ip+\"/fdon\"):$.get(camera_ip+\"/fdoff\")}function oc(){$.get(camera_ip+\"/start_ota\")}function or(){$.get(robot_ip+\"/start_ota\")}function renderBar(t,e,a,r,c){ctx.fillText(a+\":\",t,e),ctx.fillRect(t+52,e-9,40*(1-r/c),10),ctx.strokeRect(t+52,e-9,40,10),ctx.fillText(parseInt((c-r)/1024)+\" / \"+parseInt(c/1024)+\" KB\",t+100,e)}function render(t){ctx.clearRect(0,0,ctx.canvas.width,ctx.canvas.height),ctx.fillStyle=\"#FFaa00\",ctx.strokeStyle=\"#FFaa00\",ctx.lineWidth=2,ctx.font=\"12px Arial\",ctx.fillText(\"Camera FPS: \"+parseInt(1e3/(t.read+.001)),10,20),ctx.fillText(\"Stream FPS: \"+parseInt(1e3/t.stream),10,36),ctx.fillText(\"Predict FPS: \"+parseInt(1e3/(t.decode+t.predict+t.draw)),10,52),ctx.fillText(\"Temp: \"+parseInt(t.temp),10,68),ctx.fillText(\"Battery: \"+parseInt(100*t.robot.batteryVoltage)/100+\"V\",10,84),renderBar(460,20,\"Heap\",t.heap.free,t.heap.total),renderBar(460,36,\"Psram\",t.psram.free,t.psram.total),renderBar(460,52,\"Rbheap\",t.robot.heap.free,t.robot.heap.total),ctx.fillStyle=\"#ffaa00\",ctx.strokeStyle=\"#0055FF\",ctx.lineWidth=3,t.faces.forEach((t=>{if(t.score>=stream_score_threshold){let e=t.box[0]*ctx.canvas.width/stream_width,a=t.box[1]*ctx.canvas.height/stream_height,r=t.box[2]*ctx.canvas.width/stream_width-e,c=t.box[3]*ctx.canvas.height/stream_height-a;ctx.strokeRect(e,a,r,c),ctx.fillText(parseInt(1e4*t.score)/100+\" %\",e+4,a+16)}}))}function pingStreamStatus(){$(\"#rendering-option\").is(\":checked\")?$.get(camera_ip+\"/report\",(function(t){render(t)})):ctx.clearRect(0,0,ctx.canvas.width,ctx.canvas.height)}!function(t){t(document).ready((function(){t(\"#snapshot\").attr(\"src\",camera_ip+\":81/stream\"),pingStreamStatus(),intervalId=setInterval((()=>{pingStreamStatus()}),200)}))}(jQuery)</script></body></html>"; //For the Web Server

String responseSuccess = "{\"status_code\": 0}";

ESP8266WebServer server(80);

void handleHome();
void handleStartOTA();

void initWebServer() {
  // Start the server
  server.enableCORS(true); //This is the magic
  server.on("/", handleHome);
  server.on("/robot", []{
    String dirStr = server.arg("d"); //this lets you access a query param (http://x.x.x.x/action1?value=1)
    int dirCode = dirStr.toInt();
    handleRobotCmd(dirCode);
    server.send(200, "application/json", responseSuccess);
  });
  server.on("/cam", []{
    String dirStr = server.arg("d"); //this lets you access a query param (http://x.x.x.x/action1?value=1)
    int dirCode = dirStr.toInt();
    handleCamCmd(dirCode);
    server.send(200, "application/json", responseSuccess);
  });
  server.on("/start_ota", handleStartOTA);

  server.begin();
}

void updateWebServer() {
    server.handleClient();
}

void handleHome() {
  // Serial.println("Open: Homepage");
  server.send(200, "text/html", homePage);
}

void handleStartOTA() {
  // IPAddress ip = WiFi.localIP();
	String message = "Going into OTA mode";
	message += "\n";
	server.send(200, "text/plain", message);
  
	enableOTA();
}