#include <Arduino.h>


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//ESP Web Server Library to host a web page
#include <ESP8266WebServer.h>

//SSID and Password of your WiFi router
 const char* ssid = "thmrb305";
 const char* password = "thmrbthmrbthmrb";

//Declare a global object variable from the ESP8266WebServer class.
ESP8266WebServer server(80); //Server on port 80

//On board LED Connected to GPIO2
#define LED 2  

//---------------------------------------------------------------
//On board LED Connected to GPIO2
#define LED1 2  // on board led
#define LED2 14  
#define LED3 12  
#define LED4 13  
#define LED5 15  


// void loop(){}
// void handleRoot(){}
// void handleLEDon(){}
// void handleLEDoff(){}
 void handleHome(){}
// void handleLED(){}
// void controlLED(String ledNum,String ledState) ;
//---------------------------------------------------------------
//Our HTML webpage contents in program memory

const char Main_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
<center>
<h1>ESP8266 WiFi control</h1><br>
<h2>Connect OK</h2><br> 
<hr>
</center>
</body>
</html>

)=====";



//===============================================================
// These routines are executed when you open their IP in browser
//===============================================================
void handleRoot() {
 Serial.println("You called root page");
 String s = Main_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void handleLEDon() { 
 Serial.println("LED on page");
 digitalWrite(LED,LOW); //LED is connected in reverse
 server.send(200, "text/html", "LED is ON"); //Send ADC value only to client ajax request
}

void handleLEDoff() { 
  Serial.println("LED off page");
  digitalWrite(LED,HIGH); //LED off
  server.send(200, "text/html", "LED is OFF"); //Send ADC value only to client ajax request
}

// //---------------------------------------------------------
// // void 0/() {
// //  Serial.println("You call home page");
// //  String s = "Home control link OK"; //Read HTML contents
// //  server.send(200, "text/html", s); //Send web page
// // }

//----------------------------------------------------------------------------------


//-----------------------------------------------------------
void controlLED(String ledNum,String ledState) { 
 Serial.println("LED on/off data");
 int ledNo = ledNum.toInt();
 switch(ledNo){
  case 1:
    if(ledState == "on"){
      digitalWrite(LED1,LOW); 

    }else{ 
      digitalWrite(LED1,HIGH); 

    }		
    break;

  case 2:
    if(ledState == "on"){
       digitalWrite(LED2,HIGH); 
         
    } else {
      digitalWrite(LED2,LOW);      
    }	  
    break;

  case 3:
    if(ledState == "on"){
      digitalWrite(LED3,HIGH); 
       	  
    } else { 
      digitalWrite(LED3,LOW);
      
    }		  
    break;

  case 4:
    if(ledState == "on"){
      digitalWrite(LED4,HIGH);
        
    }else {
      digitalWrite(LED4,LOW);
      
    }		  
    break;

  case 5:
    if(ledState == "on"){
      digitalWrite(LED5,HIGH);
    	  
    }else{ 
      digitalWrite(LED5,LOW);    
    }		  
    break;   
 }
  
} // end of control LED
void handleLED() { 
 Serial.println("LED control");
   if(server.method() == HTTP_POST){
      if (server.hasArg("led") ) {
        String ledNum = server.arg("led");
        String ledState = server.arg("state");
        Serial.print("Received POST led data: ");
        Serial.println(ledNum);
        Serial.println(ledState);
        controlLED(ledNum,ledState);
        server.send(200, "text/html", "LED ok : "+ledNum+" - "+ledState); //Send web page  
      } 
   } else { 
     server.send(200, "text/html", "LED control fail"); 
   } 
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,HIGH); //LED is connected in reverse
  
  //Onboard LED port Direction output
  // pinMode(LED1,OUTPUT); 
  // Power on LED state off
  // digitalWrite(LED1,LOW);
  
  pinMode(LED2,OUTPUT); 
  digitalWrite(LED2,LOW);
  
  pinMode(LED3,OUTPUT); 
  digitalWrite(LED3,LOW);
  
  pinMode(LED4,OUTPUT); 
  digitalWrite(LED4,LOW);

  pinMode(LED5,OUTPUT); 
  digitalWrite(LED5,LOW);
  

  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/on", handleLEDon); //as Per  <a href="ledOn">, Subroutine to be called
  server.on("/off", handleLEDoff);
  server.on("/home", handleHome);    
  server.on("/home/led", handleLED);  
  
  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();          //Handle client requests

}