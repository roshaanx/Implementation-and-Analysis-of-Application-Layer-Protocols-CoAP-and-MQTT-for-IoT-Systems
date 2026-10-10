#include <WiFi.h>
#include <WiFiUdp.h>
#include <coap-simple.h>   // ✅ Correct

WiFiUDP udp;
Coap coap(udp);


IPAddress serverIP(192, 168, 100, 28);
int serverPort = 5683;

const char* ssid = "Khan Crew";
const char* password = "35216803";

void connectWiFi()
 {
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void callback_response(CoapPacket &packet, IPAddress ip, int port) 
{
  Serial.println("Response from server:");

  char p[packet.payloadlen + 1];
  memcpy(p, packet.payload, packet.payloadlen);
  p[packet.payloadlen] = NULL;

  Serial.println(p);
}

void setupCoAP() 
{
  coap.response(callback_response);
  coap.start();
}

void sendCoAPRequest() 
{
  Serial.println("Sending CoAP request...");
  coap.put(serverIP, serverPort, "test", "IoT Application Layer Protocol");

  delay(5000);
}

void coapLoop()
 {
  coap.loop();
}

void setup()
 {
  Serial.begin(115200);

  connectWiFi();
  setupCoAP();
}

void loop()
 {
  sendCoAPRequest();
  coapLoop();
}