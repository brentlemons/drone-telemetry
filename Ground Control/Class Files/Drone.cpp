class Drone {
    private:
    double motor1_power = 0;
    double motor2_power = 0;
    double motor3_power = 0;
    double motor4_power = 0;

    public:
    int max_angle = 0;
    void FrontBack ( double difference ) {
        this->motor1_power -= difference;
        this->motor2_power -= difference;
        this->motor3_power += difference;
        this->motor4_power += difference;
        // TODO: transmit
    }
    void LeftRight ( double difference ) {
        this->motor1_power -= difference;
        this->motor2_power += difference;
        this->motor3_power -= difference;
        this->motor4_power += difference;
        // TODO: transmit
    }
    void TurnLR ( double difference ) {
        this->motor1_power -= difference;
        this->motor2_power += difference;
        this->motor3_power += difference;
        this->motor4_power -= difference;
        // TODO: transmit
    }
    void UpDown ( double difference ) {
        this->motor1_power += difference;
        this->motor2_power += difference;
        this->motor3_power += difference;
        this->motor4_power += difference;
        // TODO: transmit
    }
};