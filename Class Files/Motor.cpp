#include <math.h>

class Motor {
    private:
    bool state = false;
    double idlePower = 0.5;

    public:
    int pin;
    double power;
    
    void init () {
        pinMode( this->pin, OUTPUT );
    }

    double convertPower( double input ) {
        if ( input > 1 ) { input = 1; }
        else if ( input < 0 ) { input = 0; }

        return ( input * 127.5 ) + 127.5;
    }

    void setPower ( double power ) {
        if ( this->state ) {
            analogWrite ( this->pin, convertPower( power ) );
        }
        this->power = power;
    }

    void spinUp () {
        double timeTotal = 5;
        int increasesPerSecond = 5;

        if ( this->state ) {
            for ( int i = 0; i < timeTotal * increasesPerSecond; i++ ) {
                double currentTime = i / increasesPerSecond;

                setPower( pow( 1.2, i ) - ( 1 + ( 1 - idlePower ) ) );
                delay( timeTotal / delayPerSecond );
            }
        }
    }

    void off () {
        digitalWrite ( this->pin, LOW );
        this->state = false;
    }

    void on () {
        analogWrite ( this->pin, convertPower( this->power ) );
        this->state = true;
    }
}