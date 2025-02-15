#include <Servo.h> //Servo Motor Library
#include <NewPing.h> //Ultrasonic function Library

// Define Pins for L298N
int motorR1 = 6;  // IN1 του L298N
int motorR2 = 5;  // IN2 του L298N
int motorL1 = 4;  // IN3 του L298N
int motorL2 = 3;  // IN4 του L298N

// Define Pins for HC-SR04
int trigPin = 12;  // TRIG του HC-SR04
int echoPin = 11; // ECHO του HC-SR04


// Define Servo
Servo myServo;

void setup() {
    //  Define OUTPUTS and INPUTS of motors
    pinMode(motorR2, OUTPUT);
    pinMode(motorR1, OUTPUT);
    pinMode(motorL2, OUTPUT);
    pinMode(motorL1, OUTPUT);

    // Define OUTPUTS and INPUTS of HC-SR04
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
  
    digitalWrite(trigPin, LOW);   //Ultrasonic sensor 

 	myServo.attach(9); //Pin of Arduino,connected to signal pin
 	myServo.write(45); //Rotate the servo 90 degrees
 	delay(500); 


}

// Measurment of distance
int getDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    long duration = pulseIn(echoPin, HIGH);
    int distance = duration * 0.034 / 2; // distance in cm
    return distance;
}

// movements of the car
void moveForward() {
    digitalWrite(motorR2, HIGH);
    digitalWrite(motorR1, LOW);
    digitalWrite(motorL2, HIGH);
    digitalWrite(motorL1, LOW);
}

// CAr stops
void stopCar() {
    digitalWrite(motorR2, LOW);
    digitalWrite(motorR1, LOW);
    digitalWrite(motorL2, LOW);
    digitalWrite(motorL1, LOW);
}

// Car turning Left
void turnLeft() {
    digitalWrite(motorR2, LOW);
    digitalWrite(motorR1, HIGH);
    digitalWrite(motorL2, HIGH);
    digitalWrite(motorL1, LOW);
}

// Car turning Right
void turnRight() {
    digitalWrite(motorR2, HIGH);
    digitalWrite(motorR1, LOW);
    digitalWrite(motorL2, LOW);
    digitalWrite(motorL1, HIGH);
}

void loop() {
    //moveForward(); // Car moves forward

    int distance = getDistance();

    if (distance <= 40) {  // If obstacle detect < 40cm
        stopCar();  // Car stops
        delay(500);

        myServo.write(0);   // Servo looking Left
        delay(500);
        int distanceLeft = getDistance();
        
        myServo.write(90); // Servo looking Right
        delay(500);
        int distanceRight = getDistance();
        
        myServo.write(45);  // Servo return forward
        delay(500);
      

        // Confortate Distances
        if (distanceLeft > distanceRight) {
            turnLeft();  // Car turning Left
            delay(150);
        } 
        else {
           turnRight(); // Car turning Right
            delay(150);
        } 
    } 
    else {  moveForward(); // Car moves forward
           int distance = getDistance();
    }
}
