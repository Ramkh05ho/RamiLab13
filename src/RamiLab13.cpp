/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/ramikhosho/RamiLab13/src/RamiLab13.ino"
#include "MQTT.h"
#include "oled-wing-adafruit.h"

void setup();
void loop();
void resetDisplay();
void caller();
#line 4 "/Users/ramikhosho/RamiLab13/src/RamiLab13.ino"
void callback(char *topic, byte *payload, unsigned int length);

MQTT client("lab.thewcl.com", 1883, callback);
OledWingAdafruit display;

double latitude = 0.00;
double longitude = 0.00;

String eTopicOne = "testtopic/RamiCool2";
String eTopicTwo = "testtopic/RamiCool1";

void setup()
{
    Serial.begin(9600);
    display.setup();
    resetDisplay();
    display.display();

    client.subscribe("testtopic/RamiCool2");
    client.subscribe("testtopic/RamiCool1");
}
void loop()
{
    display.loop();
    if (client.isConnected())
    {
        client.loop();
        client.publish("testtopic/RamiCool", "Send");
        delay(10000);
    }
    else
    {
        client.connect(System.deviceID());
        client.subscribe("testtopic/RamiCool2");
        client.subscribe("testtopic/RamiCool1");
        Serial.println("DIDN'T WORK");
    }
   
}
void resetDisplay()
{
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextColor(WHITE);
    display.setTextSize(1);
}
void callback(char *topic, byte *payload, unsigned int length)
{
    char p[length + 1];
    memcpy(p, payload, length);
    p[length] = NULL;
    String s = p;
    double value = s.toFloat();

    String callbackTopic = String(topic);

    Serial.printf("%s", p);
    Serial.println();
    Serial.println(value);
    if (callbackTopic.compareTo(eTopicOne))
    {
        Serial.println("LAT");
        latitude = value;
    }
    if (callbackTopic.compareTo(eTopicTwo))
    {
        Serial.println("LONG");
        longitude = value;
    }
    resetDisplay();
    display.println(latitude);
    display.println(longitude);
    display.display();
}
void caller()
{
    client.publish("testtopic/RamiCool", "Send");
}