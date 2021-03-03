class Drone {
    private:
    motor1_power
    motor2_power
    motor3_power
    motor4_power
    max_angle

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