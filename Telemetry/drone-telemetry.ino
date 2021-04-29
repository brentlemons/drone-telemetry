#include "config.h"
#include "Motor.cpp"

#include <Adafruit_GPS.h>

#include <SPI.h>
#include <RH_RF95.h>

//! Must be version 5 or we need to change to v6
#include <ArduinoJson.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
  
Adafruit_BNO055 bno = Adafruit_BNO055(55);

//? what's the name of the hardware serial port?
#define GPSSerial Serial1

// for feather m0  
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3

//! Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 948.3
 
// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

// Connect to the GPS on the hardware port
Adafruit_GPS GPS(&GPSSerial);
     
// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences
#define GPSECHO false
uint32_t timer = millis();

// Motor object creation
// Organized clockwise
Motor motor1;
Motor motor2;
Motor motor3;
Motor motor4;
Motor motors[4] = { motor1, motor2, motor3, motor4 }

//TODO motor pinmapping


bool moveDrone ( double roll, double pitch, double yaw ) {
    motor1.setPower( motor1.power - pitch - roll - yaw );
    motor2.setPower( motor2.power - pitch + roll + yaw );
    motor3.setPower( motor3.power + pitch + roll - yaw );
    motor4.setPower( motor4.power + pitch - roll + yaw );
}

void setup() {
    // Motor pinmap
    motor1.pin = 3;
    motor2.pin = 4;
    motor3.pin = 6;
    motor4.pin = 9;

    // Motor spinup
    // TODO: figure out power needed for takeoff
    for ( int i = 0; i < len( motors ); i++ ) {
        motors[i].init();
        motors[i].on();
        motors[i].spinUp();
    }

    pinMode(RFM95_RST, OUTPUT);
    digitalWrite(RFM95_RST, HIGH);

    Serial.begin(115200);
    while (!Serial) {
        delay(1);
    }

    delay(100);

    Serial.println("Feather LoRa TX Test!");

    // manual reset
    digitalWrite(RFM95_RST, LOW);
    delay(10);
    digitalWrite(RFM95_RST, HIGH);
    delay(10);

    while (!rf95.init()) {
        Serial.println("LoRa radio init failed");
        while (1);
    }
    Serial.println("LoRa radio init OK!");

    // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
    if (!rf95.setFrequency(RF95_FREQ)) {
        Serial.println("setFrequency failed");
        while (1);
    }
    Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);

    // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

    // The default transmitter power is 13dBm, using PA_BOOST.
    // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
    // you can set transmitter powers from 5 to 23 dBm:
    rf95.setTxPower(23, false);

    //while (!Serial);  // uncomment to have the sketch wait until Serial is ready
        
    // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
    GPS.begin(9600);
    // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    // uncomment this line to turn on only the "minimum recommended" data
    //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
    // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
    // the parser doesn't care about other sentences at this time
    // Set the update rate
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
    // For the parsing code to work nicely and have time to sort thru the data, and
    // print it out we don't suggest using anything higher than 1 Hz
        
    // Request updates on antenna status, comment out to keep quiet
    GPS.sendCommand(PGCMD_ANTENNA);

    delay(1000);

    // Ask for firmware version
    GPSSerial.println(PMTK_Q_RELEASE);

    /* Initialise the sensor */
    if(!bno.begin())
    {
        //! There was a problem detecting the BNO055 ... check your connections
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        while(1);
    } else {
        Serial.print("BNO055 detected");
    }

    delay(1000);

    bno.setExtCrystalUse(true);
}

int16_t packetnum = 0;  // packet counter, we increment per xmission

void loop() {    sensors_event_t event;     bno.getEvent(&event);
    double rollTelemetry = event.orientation.z;    double pitchTelemetry = event.orientation.y;    double yawTelemetry = event.orientation.x;

    /* Display the floating point data */
    /*
    Serial.print("X: ");
    Serial.print(event.orientation.x, 4);
    Serial.print("\tY: ");
    Serial.print(event.orientation.y, 4);
    Serial.print("\tZ: ");
    Serial.print(event.orientation.z, 4);
    Serial.println("");

    delay(100);
    */
    StaticJsonBuffer<200> jsonBuffer;    JsonObject& root = jsonBuffer.createObject();
        char radiopacket[20]; // = GPS.latitude + "n"; //"Hello World #      ";    gcvt(GPS.latitude, 8, radiopacket);    radiopacket[19] = 0;
    JsonObject& gps = root.createNestedObject("gps");    JsonArray& data = gps.createNestedArray("data");    data.add(GPS.latitudeDegrees);    data.add(GPS.longitudeDegrees);    gps["altitude"] = GPS.altitude;
    root["roll"] = roll;    root["pitch"] = pitch;    root["yaw"] = yaw;


    String jsonStr;
    root.printTo(jsonStr);

    int jsonStrLength = jsonStr.length();
    char char_array[jsonStrLength+1];
    char_array[jsonStrLength] = 0;

    strcpy(char_array, jsonStr.c_str());

    Serial.print("Sending "); Serial.print(char_array); Serial.println(RH_RF95_MAX_MESSAGE_LEN - jsonStrLength - 1);
    delay(10);

}
