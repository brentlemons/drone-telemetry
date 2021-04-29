#include <Wire.h>
#include <ArduinoJson.h>

#define RF95_FREQ 948.3

void setup () {

}

bool transmitInput ( double roll, double pitch, double yaw ) {
    //TODO: add actual transmission code
    //? use arrays?
    //? something like transmitter.transmit( { roll, pitch, yaw } );
}

void loop () {
    //TODO: get control inputs
    double rollInput;
    double pitchInput;
    double yawInput;

    transmitInput( rollInput, pitchInput, yawInput );
}