#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// ----- PIN SETUP -----
const int in1 = 14;  // D5 on NodeMCU
const int in2 = 12;  // D6
const int in3 = 13;  // D7
const int in4 = 15;  // D8

// ----- Your WiFi credentials -----
const char* ssid = "kemtan";
const char* password = "Kemtanbangetz";

ESP8266WebServer server(80);

// ===== MOTOR CONTROL LOGIC =====
void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void forward()  { digitalWrite(in1,HIGH); digitalWrite(in2,LOW);  digitalWrite(in3,HIGH); digitalWrite(in4,LOW); }
void backward() { digitalWrite(in1,LOW);  digitalWrite(in2,HIGH); digitalWrite(in3,LOW);  digitalWrite(in4,HIGH);}
void left()     { digitalWrite(in1,LOW);  digitalWrite(in2,HIGH); digitalWrite(in3,HIGH); digitalWrite(in4,LOW); }
void right()    { digitalWrite(in1,HIGH); digitalWrite(in2,LOW);  digitalWrite(in3,LOW);  digitalWrite(in4,HIGH); }

// ===== WEB UI =====
String html = R"rawliteral(
<!DOCTYPE html><html><head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family:sans-serif; text-align:center; background:#f2f2f2; }
    .btn { width:100px; height:60px; margin:10px; font-size:18px;
           border-radius:12px; border:none; background:#4CAF50; color:white; }
    .btn.stop { background:red; }
  </style>
</head><body>
  <h2>ESP8266 Car Control</h2>
  <div>
    <button id="forward" class="btn">Forward</button>
    <button id="left"    class="btn">Left</button>
    <button id="right"   class="btn">Right</button>
    <button id="backward"class="btn">Backward</button>
  </div>
<script>
  function sendCmd(dir){ fetch('/move?dir='+dir).catch(()=>{}); }
  function bindControl(id, cmd){
    const b = document.getElementById(id);
    b.addEventListener('mousedown',  ()=>sendCmd(cmd));
    b.addEventListener('mouseup',    ()=>sendCmd('stop'));
    b.addEventListener('touchstart', ()=>sendCmd(cmd));
    b.addEventListener('touchend',   ()=>sendCmd('stop'));
  }
  window.onload = ()=>{
    bindControl('forward',  'forward');
    bindControl('backward', 'backward');
    bindControl('left',     'left');
    bindControl('right',    'right');
  };
</script>
</body></html>
)rawliteral";

void handleRoot() {
  server.send(200, "text/html", html);
}

void handleMove() {
  String dir = server.arg("dir");
  Serial.println("Direction: " + dir);
  if      (dir=="forward")  forward();
  else if (dir=="backward") backward();
  else if (dir=="left")     left();
  else if (dir=="right")    right();
  else                      stopMotors();
  server.send(204, "text/plain","");
}

void setup() {
  Serial.begin(9600);
  pinMode(in1, OUTPUT); pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT); pinMode(in4, OUTPUT);
  stopMotors();

  WiFi.begin(ssid, password);
  Serial.print("Connecting...");
  while (WiFi.status()!=WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nIP: " + WiFi.localIP().toString());

  server.on("/",    handleRoot);
  server.on("/move",handleMove);
  server.begin();
}

void loop() {
  server.handleClient();
}
