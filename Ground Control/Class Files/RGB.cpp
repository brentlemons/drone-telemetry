class RGB {
    private:
    int r;
    int g;
    int b;
    int r_pin;
    int g_pin;
    int b_pin;
    int brightness;
    int negative_brightness

    public:
    void init ( int r_pin, int g_pin, int b_pin ) {
    this->r_pin = r_pin;
    this->g_pin = g_pin;
    this->b_pin = b_pin;
    pinMode (r_pin, OUTPUT);
    pinMode (g_pin, OUTPUT);
    pinMode (b_pin, OUTPUT);
    }
    void setColor ( int r, int g, int b ) {
        this->r = r;
        this->g = g;
        this->b = b;
        analogWrite ( this->r , r );
        analogWrite ( this->g , g );
        analogWrite ( this->b , b );
    }
    void setBrightness ( int brightness ) {
        this->brightness = brightness;
        this->negative_brightness = 255 - brightness;
        analogWrite ( this->r , r - this->negative_brightness );
        analogWrite ( this->g , g - this->negative_brightness );
        analogWrite ( this->b , b - this->negative_brightness );
    }
    void On () {
        analogWrite ( this->r , r - this->negative_brightness );
        analogWrite ( this->g , g - this->negative_brightness );
        analogWrite ( this->b , b - this->negative_brightness );
    }
    void Off () {
        digitalWrite ( r_pin, LOW );
        digitalWrite ( g_pin, LOW );
        digitalWrite ( b_pin, LOW );
    }
};

// this->XXX = XXX;
// this->XXX = XXX;
// this->XXX = XXX;