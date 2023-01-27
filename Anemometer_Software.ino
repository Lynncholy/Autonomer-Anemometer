#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
/*************************************************************/
//This part is needed if you want to set up an access point
#include <WiFiManager.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
/*************************************************************/

char auth[] = ""; //Your authentification token from the Blynk project
char ssid[] = "";  //Your SSID
char pass[] = ""; //Your WiFi password

/*****************************************************************************************************/

int windspeed = 0;
int sensor = A0;
int sensorvalue;                                                                  
int t = 1000;                                                                     //Time t in mili seconds. Delays the time intervalls in which
int windMeasurements[10];                                                         //a value is measured. t = (2,88*(10^7)) for measuring each 8 hours
int count = 0;                                                                    //t = 60000 for measuring each minunte
int sum = 0;
float windspeedAverage = 0;

void setup() 
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  /****************************************************************************************************/
  //Remove comments to set up WiFiManager and an accesspoint if you want to connect to an access point instead
  //WiFiManager wm;

  //wm.resetSettings();

  //bool res;
  //res = wm.autoConnect(); // auto generated AP name from chipid
  //res = wm.autoConnect("AutoConnectAP");

  //if (!res) {
    //Serial.println("Failed to connect");
    //ESP.restart();
  //}
  //else {
    //if you get here you have connected to the WiFi
    //Serial.println("connected...yeey :)");
  //}
  /****************************************************************************************************/
  
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop() 
{
  Blynk.run();
  sensorvalue=analogRead(sensor);
  delay(t); // t in mili seconds.
  windspeed= map(sensorvalue, 0, 500, 0, 50);                                      //Interpretation of sensor value must be adjusted and mapped
  Blynk.virtualWrite(V1, windspeed);

/************************************************************************************/
//Calculating the average Wind speed in this measuring time (last 10 seconds)

if(count > 9)
{
  sum = 0;
  for(int i = 0; i < 10; i++)
  {
    sum = sum + windMeasurements[i];
  }
  windspeedAverage = sum/10;
  count = 0;
  Blynk.virtualWrite(V5, windspeedAverage);
  if (windspeedAverage > 2)                                                           // Sends a notification to your phone if the average wind speed is higher than 75 km/h
  {
    Blynk.logEvent("storm_warning", "average wind speed is higher than 75 km/h");
    Serial.println();
    Serial.print("Storm warning! Average Wind speed is higher than 75 km/h! ");
    Serial.println();  
  }
  Serial.println();
  Serial.print("Average wind speed in the last 10 seconds: ");                     // Output in monitor
  Serial.println(windspeedAverage);
  Serial.println();
}
else
{
  windMeasurements[count] = windspeed;
  count++;
}

/************************************************************************************/

Serial.print("Wind speed in km/h: ");                                               //Output in monitor
Serial.println(windspeed);
Serial.println();
}

/****************************************************************************
 * Sleep Mode triggered through WiFi to disconnect from WiFi
BLYNK_WRITE (V2) {
  switch (param.asInt()) {
    case 0: {
        Blynk.virtualWrite(V0, windspeedAverage);
        Blynk.virtualWrite(V5, windspeed);
        //    WiFi.disconnect();
        Serial.println("Enter modem sleep mode");
        Blynk.notify("Your anemometer is going to sleep now!");
        WiFi.forceSleepBegin();
        break;
      }
    case 1: {
       WiFi.forceSleepWake();
       delay(1);
       Serial.println("Exit modem sleep mode");

       WiFi.mode(WIFI_STA);
       WiFi.begin(ssid, pass);
       Serial.println("");
       Blynk.notify("Wakey, wakey! Your anemometer just woke up!");
       break;
      }

    default: {
       WiFi.forceSleepWake();
       delay(1);
       Serial.println("Exit modem sleep mode");

       WiFi.mode(WIFI_STA);
       WiFi.begin(ssid, pass);
       Serial.println("");
        break;
      }

  }
}
************************************************************************************/
