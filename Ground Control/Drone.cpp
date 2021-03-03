class Drone {
    private:
    motor1_power = 0;
    motor2_power = 0;
    motor3_power = 0;
    motor4_power = 0;
    max_angle = 0;

    public:
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
}