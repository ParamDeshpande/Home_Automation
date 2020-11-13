/*
  WiFi Web Server LED Blink
 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 9.
 If the IP address of your WiFi is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off
 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.
 Circuit:
 * CC3200 WiFi LaunchPad or CC3100 WiFi BoosterPack
   with TM4C or MSP430 LaunchPad
 created 25 Nov 2012
 by Tom Igoe
 modified 6 July 2014
 by Noah Luskey
 */
#ifndef __CC3200R1M1RGC__
// Do not include SPI for CC3200 LaunchPad
#include <SPI.h>
#endif
#include <WiFi.h>
#define DEBUG_VERSION_2

#define NOT_FULL 0
#define FULL 1

#define HVAC_PIN 3
#define PSEN_PIN_1 6
#define PSEN_PIN_2 24
#define ADC_RES 4096e0
#define PIN_VOLT(x) (1.5*x/ADC_RES)
#define PRES_THOLD_VOLT (5e-1)


double Psen_val_1 = 0;
double Psen_val_2 = 0;

bool Cartridge_status = NOT_FULL;
// your network name also called SSID
char ssid[] = "JioFi3_697A78";
// your network password
char password[] = "bwwyynh63t";
// your network key Index number (needed only for WEP)
int keyIndex = 0;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);      // initialize serial communication
  pinMode(HVAC_PIN, OUTPUT);      // set the LED pin mode
  pinMode(PSEN_PIN_1, INPUT);      // set the LED pin mode
  pinMode(PSEN_PIN_2, INPUT);      // set the LED pin mode


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
  
  while (WiFi.localIP() == INADDR_NONE) {
    // print dots while we wait for an ip addresss
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nIP Address obtained");
  
  // you're connected now, so print out the status  
  printWifiStatus();

  Serial.println("Starting webserver on port 80");
  server.begin();                           // start the web server on port 80
  Serial.println("Webserver started!");
  
  Serial.println("Init System");


}

void loop() {

  //Psen_val_1 = (analogRead(PSEN_PIN_1));
  //Psen_val_2 = (analogRead(PSEN_PIN_2));
        

  int i = 0;
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    char buffer[150] = {0};                 // make a buffer to hold incoming data
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (strlen(buffer) == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            #ifdef DEFAULT
            // the content of the HTTP response follows the header:
            client.println("<html><head><title>Energia CC3200 WiFi Web Server</title></head><body align=center>");
            client.println("<h1 align=center><font color=\"red\">Welcome to the CC3200 WiFi Web Server</font></h1>");
            client.print("RED LED <button onclick=\"location.href='/H'\">HIGH</button>");
            client.println(" <button onclick=\"location.href='/L'\">LOW</button><br>");
            #endif
            
            #ifdef DEBUG 


            client.println("<!DOCTYPE html>");
            client.println("<html>");
            client.println("<head>");
            client.println("  <title>Energia CC3200 WiFi Web Server</title>");
            client.println("  <style type=\"text/css\">");
 
            client.println("    body {");
            client.println("      background-color: black;");
            client.println("    }");
 
            client.println("    div.transbox {");
            client.println("      background-color: ffffff;");
            client.println("      opacity: 0.9;");
            client.println("      margin: 5%;");
            client.println("      margin-top: 20px;");
 
            client.println("    }");
 
            client.println("    div.transbox h1,h2{");
            client.println("      text-align: center;");
            client.println("    }");
 
 
            client.println("    .button {");
            client.println("      background-color: black;");
            client.println("      border: none;");
            client.println("      color: white;");
            client.println("      padding: 15px 32px;");
            client.println("      text-align: center;");
            client.println("      text-decoration: none;");
            client.println("      display: inline-block;");
            client.println("      font-size: 16px;");
            client.println("      margin: 4px 2px;");
            client.println("      cursor: pointer;");
            client.println("      -webkit-transition-duration: 0.4s;");
            client.println("      transition-duration: 0.4s;");
            client.println("    }");
 
            client.println("    .button1:hover {");
            client.println("      box-shadow: 0 12px 16px 0 rgba(0,0,0,0.24),0 17px 50px 0 rgba(0,0,0,0.19);");
            client.println("      background-color: 555555;");
            client.println("      color: white;");
            client.println("    }");
            client.println("  </style>");
            client.println("</head>");
            client.println("<body>");
            client.println("  <div class=\"background\">");
            client.println("    <div class=\"transbox\">");
            client.println("      <h1>InKarbon</h1>");
            client.println("      <h2>Welcome to CC3200 WiFi Web Server</h1>");
            client.println("        <br><br>");
            
            client.println("      <button onclick=\"location.href='/H'\">Manual ON</button>");
            client.println("      <button onclick=\"location.href='/L'\">Manual OFF</button>");
            client.println("    </div>");
            client.println("  </div>");
            client.println("</body>");
            client.println("</html>");
            #endif 


            #ifdef DEBUG_VERSION_2
                client.println("  <!DOCTYPE html>");
                client.println("  <html>");
                client.println("  <head>");
                client.println("    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                client.println("    <title>Energia CC3200 WiFi Web Server</title>");
                client.println("    <style type=\"text/css\">");
                client.println("      ");
                client.println("      body {");
                client.println("        background-color: black;");
                client.println("      }");
                client.println("  ");
                client.println("      div.transbox {");
                client.println("        background-color: #ffffff;");
                client.println("        opacity: 0.9;");
                client.println("        margin: 5%;");
                client.println("        margin-top: 20px;");
                client.println("  ");
                client.println("      }");
                client.println("  ");
                client.println("      div.transbox h1,h2{");
                client.println("        text-align: center;");
                client.println("      }");
                client.println("  ");
                client.println("  ");
                client.println("      .button {");
                client.println("        background-color: black;");
                client.println("        border: none;");
                client.println("        color: white;");
                client.println("        padding: 15px 32px;");
                client.println("        text-align: center;");
                client.println("        text-decoration: none;");
                client.println("        display: inline-block;");
                client.println("        font-size: 16px;");
                client.println("        margin: 4px 2px;");
                client.println("        cursor: pointer;");
                client.println("        -webkit-transition-duration: 0.4s;");
                client.println("        transition-duration: 0.4s;");
                client.println("      }");
                client.println("      ");
                client.println("      .button1:hover {");
                client.println("        box-shadow: 0 12px 16px 0 rgba(0,0,0,0.24),0 17px 50px 0 rgba(0,0,0,0.19);");
                client.println("        background-color: #555555;");
                client.println("        color: white;");
                client.println("      }");
                client.println("  ");
                client.println("      .button1:active {");
                client.println("        background-color: grey;");
                client.println("      }");
                client.println("    ");
                client.println("      .red {");
                client.println("        font-size: 25px;");
                client.println("        text-align: center;");
                client.println("      }");
                client.println("      ");
                client.println("    </style>");
                client.println("  </head>");
                client.println("  <body>");
                client.println("    <div class=\"background\">");
                client.println("      <div class=\"transbox\">");
                client.println("        <h1>InKarbon</h1>");
                client.println("        <hr>");
                client.println("        <h2>Welcome to CC3200 WiFi Web Server</h1>");
                client.println("          <br>");
                client.println("        <div align=\"center\">");
                client.println("          <p class=\"red\">Device:");
                client.println("          <button onclick=\"location.href='/H'\">ON</button>");
                client.println("          <button onclick=\"location.href='/L'\">OFF</button>");
                client.println("          </p>");
                client.println("        </div>");
                client.println("        <br>");
                client.println("        <div class=\"Cartridge\">");
                client.println("          <p class=\"red\">Cartridge Status: CLEAN</p>");
                //client.println("          <p class=\"red\">Cartridge Status: FULL</p>");
                client.println("        </div>");
                client.println("      </div>");
                client.println("    </div>");
                client.println("  </body>");
                client.println("  </html>");
            #endif // DEBUG
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear the buffer:
            memset(buffer, 0, 150);
            i = 0;
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          buffer[i++] = c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if(Cartridge_status == NOT_FULL){
          if (endsWith(buffer, "GET /H")) {
          digitalWrite(HVAC_PIN, HIGH);               // GET /H turns the LED on
        }
        if (endsWith(buffer, "GET /L")) {
          digitalWrite(HVAC_PIN, LOW);                // GET /L turns the LED off
        }

        }
        
        Psen_val_1 = PIN_VOLT(analogRead(PSEN_PIN_1));
        Psen_val_2 = PIN_VOLT(analogRead(PSEN_PIN_2));
        Serial.print("PIN 1 Voltage   ");
        Serial.print(Psen_val_1);
        Serial.print("      PIN 2 Voltage  ");
        Serial.println(Psen_val_2);
        
        


        /*@sahil please find a way to print this in the web GUI*/
        if((Psen_val_1 - Psen_val_2 ) > PRES_THOLD_VOLT){
          Serial.println("Cartridge nearly full, please replace, HVAC turned OFF");
          digitalWrite(HVAC_PIN, LOW);         
          Cartridge_status = FULL;
        }

      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

//
//a way to check if one array ends with another array
//
boolean endsWith(char* inString, char* compString) {
  int compLength = strlen(compString);
  int strLength = strlen(inString);
  
  //compare the last "compLength" values of the inString
  int i;
  for (i = 0; i < compLength; i++) {
    char a = inString[(strLength - 1) - i];
    char b = compString[(compLength - 1) - i];
    if (a != b) {
      return false;
    }
  }
  return true;
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}
