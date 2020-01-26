//including every library possibly necessary
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>



/* 
 * VB: http://timme7893.nl/NLT/updateStatus.php?vakje=1&status=open
 *Reponse: ‘query executed’ -> Succesvol query uitgevoerd.
*/


//network ssid and pwd, if u don't get this u better not use this script,
const char* ssid     = "blabla";
const char* password = "blabla";

//giving pins names and stuff
const int LED_1 = 5;
const int LED_2 = 4;
const int LED_3 = 12;
const int LED_4 = 13;
const int BUZZER = 14;
const char* OPENSENSOR = "A0";

void setup() {
  //start serial monitor
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  //run network setup script 
  connectToNetwork();

  //set digital pins to output mode
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() { 
String httpCurrTime = httpCurrentTime();
if(httpCurrTime == httpBoxTime(1)) {
  digitalWrite(LED_1, HIGH);
  digitalWrite(BUZZER, HIGH);
  
  if(A0 > 500) {
    httpPostShit(1);
    digitalWrite(LED_1, LOW);
    digitalWrite(BUZZER, LOW);
  }

}
if(httpCurrTime == httpBoxTime(2)) {
  digitalWrite(LED_2, HIGH);
  digitalWrite(BUZZER, HIGH);
  
  if(A0 > 500) {
    httpPostShit(2);
    digitalWrite(LED_2, LOW);
    digitalWrite(BUZZER, LOW);
  }

}
if(httpCurrTime == httpBoxTime(3)) {
  digitalWrite(LED_3, HIGH);
  digitalWrite(BUZZER, HIGH);
  
  if(A0 > 500) {
    httpPostShit(3);
    digitalWrite(LED_3, LOW);
    digitalWrite(BUZZER, LOW);
  }

}
if(httpCurrTime == httpBoxTime(4)) {
  digitalWrite(LED_4, HIGH);
  digitalWrite(BUZZER, HIGH);
  
  if(A0  > 500) {
    httpPostShit(4);
    digitalWrite(LED_4, LOW);
    digitalWrite(BUZZER, LOW);
  }

}

}



void connectToNetwork() {
  // connecting to the network
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");
  int i = 0;
  //waiting untill the fucking network connects
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }
  // Sends everything needed to stalk the ESP (local ip only XD) over serial monitor
  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
}

void httpPostShit(int vakje) {
   Serial.println("http://timme7893.nl/NLT/updateStatus.php?vakje=" + String(vakje) + "&status=open");
   HTTPClient http;
   http.begin("http://timme7893.nl/NLT/updateStatus.php?vakje=" + String(vakje) + "&status=open");
   http.addHeader("Content-Type", "text/plain");
   int httpCode = http.POST("");
   String soarceOfPagePostHttp = http.getString();
   Serial.println(httpCode);
   Serial.println(soarceOfPagePostHttp);
   http.end();
}

String httpCurrentTime() {
  HTTPClient http;
  http.begin("http://timme7893.nl/NLT/getCurrentTime.php");
  http.addHeader("Content-Type", "text/plain");
  int httpCode = http.POST("");
  http.end();
  return http.getString();
}

String httpBoxTime(int wichBoxTime) {
   HTTPClient http;
   http.begin("http://timme7893.nl/NLT/getTime.php?vakje=" + String(wichBoxTime));
   http.addHeader("Content-Type", "text/plain");
   int httpCode = http.POST("");
   http.end();
   return http.getString();
}
