/*
 Chat  Server

 A simple server that distributes any incoming messages to all
 connected clients.  To use telnet to  your device's IP address and type.
 You can see the client's input in the serial monitor as well.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.


 Circuit:
 * CC3200 LaunchPad or 
   F5529/TivaC LaunchPad with CC3000/CC3100 BoosterPack

 created 18 Dec 2009
 by David A. Mellis
 modified 31 May 2012
 by Tom Igoe

 */

#ifndef __CC3200R1M1RGC__
// Do not include SPI for CC3200 LaunchPad
#include <SPI.h>
#endif
#include <WiFi.h>

/* Global VARS */

// your network name also called SSID
char ssid[] = "TPLINK_47AC";
// your network password
char password[] = "ClaraDee1)))$";

WiFiServer server(23);

boolean alreadyConnected = false; // whether or not the client was connected previously

#define DEVICE_ON   0
#define DEVICE_OFF  1

#define GLED GREEN_LED
#define YLED YELLOW_LED
#define RLED RED_LED

#define LIGHT_PIN  18
#define FAN_PIN  19
#define LED_PIN  17

#define COMP_MSG(x,y) (strncmp(x,y,sizeof(y))==0)?(1):(0)


static const char LIGHTON_MSG[] = {"lightON"};
static const char LIGHTOFF_MSG[] = {"lightOFF"};
static const char FANON_MSG[] =  {"fanON"};
static const char FANOFF_MSG[] = {"fanOFF"};
static const char LEDON_MSG[] =  {"ledON" };
static const char LEDOFF_MSG[] = {"ledOFF"};



char CLIENT_MSG[1000] = {0};
uint8_t iterMsg = 0;
const char TERM_CHAR = 'q'; 

/* Function Prototypes */
void setupDevices(void);
void exec_cmd(void);

void setup() {
  setupDevices();
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssid); 
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) {
    // print dots while we wait to connect
    Serial.print(".");
    delay(300);
  }
  
  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");
  IPAddress retIP(192,168,0,150);
  WiFi.config(retIP);
  while (WiFi.localIP() == INADDR_NONE) {
    // print dots while we wait for an ip addresss
    Serial.print(".");
    delay(300);
  }
  digitalWrite(GLED,HIGH);
  digitalWrite(RLED,LOW);
  
  Serial.println("\nIP Address obtained");

  // you're connected now, so print out the status:
  printWifiStatus();

  // start the server:
  server.begin();
}


void loop() {
  // wait for a new client:
  WiFiClient client = server.available();


  // when the client sends the first byte, say hello:
  if (client) {
    if (!alreadyConnected) {
      // clead out the input buffer:
      client.flush();
      //Serial.println("We have a new client");
      //client.println("Hello, client!");
      alreadyConnected = true;
    }

    if (client.available() > 0) {
      
      while(1){
        // read the bytes incoming from the client:
        char thisChar = client.read();
        // echo the bytes back to the client:
        //server.write(thisChar);
        // echo the bytes to the server as well:
        //Serial.write(thisChar);
        digitalWrite(YLED,HIGH);
        if(thisChar != TERM_CHAR){
          CLIENT_MSG[iterMsg] = thisChar;
          iterMsg+=1;
          #ifdef DEBUG
          Serial.print(" client msg is :" );
          Serial.print(CLIENT_MSG );
          Serial.print(" iterMsg:" );
          Serial.println(iterMsg);
          #endif        
        }
        else{
          exec_cmd();
          digitalWrite(YLED,LOW);
          memset(CLIENT_MSG, 0, sizeof(CLIENT_MSG));
          iterMsg =0;
          break;
          #ifdef DEBUG
          Serial.print(" client msg is :" );
          Serial.print(CLIENT_MSG );
          Serial.print(" iterMsg:" );
          Serial.println(iterMsg);
          #endif
        }
          
      }
      
    }
    
  }
  
  sleep(1000);

}


void exec_cmd(void){
  if(COMP_MSG(CLIENT_MSG,LIGHTON_MSG))
    digitalWrite(LIGHT_PIN,DEVICE_ON);
  else if(COMP_MSG(CLIENT_MSG,LIGHTOFF_MSG))
    digitalWrite(LIGHT_PIN,DEVICE_OFF);
  
  else if(COMP_MSG(CLIENT_MSG,FANON_MSG))
    digitalWrite(FAN_PIN,!DEVICE_ON);
  else if(COMP_MSG(CLIENT_MSG,FANOFF_MSG))
    digitalWrite(FAN_PIN,!DEVICE_OFF);

  else if(COMP_MSG(CLIENT_MSG,LEDON_MSG))
    digitalWrite(LED_PIN,DEVICE_ON);
  else if(COMP_MSG(CLIENT_MSG,LEDOFF_MSG))
    digitalWrite(LED_PIN,DEVICE_OFF);
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}



void setupDevices(void){  
  pinMode(GLED, OUTPUT);
  pinMode(YLED, OUTPUT);
  pinMode(RLED, OUTPUT);
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(GLED,LOW);
  digitalWrite(YLED,LOW);
  digitalWrite(RLED,HIGH);
  
  digitalWrite(LIGHT_PIN,DEVICE_OFF);
  digitalWrite(FAN_PIN,  DEVICE_OFF);
  digitalWrite(LED_PIN,  DEVICE_OFF);
}
