#include <Servo.h>

Servo myServo;

int servo_pin = 9;

int yellow_led = 3;
int green_led = 4;
int red_led = 2;

int buzzpin = 8;

int delay_time = 500;

int angle0 = 0;
int angle90 = 90;
int angle180 = 180;

int distance50 = 1000;
int distance25 = 500;
int distance0 = 200;

// Ultrasonic sensor
int echo_pin = 10;
int trig_pin = 11;

long duration;
int distance;


// ==========================
// ULTRASONIC FUNCTION
// ==========================
int getDistance() {

  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);

  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trig_pin, LOW);

  duration = pulseIn(echo_pin, HIGH);

  distance = duration * 0.034 / 2;

  return distance;
}


// ==========================
// SERVO SCANNING FUNCTION
// ==========================
void ultra_response(int num) {

  myServo.write(angle0);
  delay(150);

  myServo.write(angle90);
  delay(150);

  myServo.write(angle180);
  delay(150);

  myServo.write(angle90);

  delay(num);
}


// ==========================
// LED BLINK FUNCTION
// ==========================
void blinkLED(int ledPin, int blinkDelay) {

  for(int i = 0; i < 3; i++) {

    digitalWrite(ledPin, HIGH);
    delay(blinkDelay);

    digitalWrite(ledPin, LOW);
    delay(blinkDelay);
  }
}


// ==========================
// SETUP
// ==========================
void setup() {

  pinMode(yellow_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(red_led, OUTPUT);

  pinMode(buzzpin, OUTPUT);

  myServo.attach(servo_pin);

  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  Serial.begin(9600);
}


// ==========================
// LOOP
// ==========================
void loop() {

  distance = getDistance();

  Serial.print("The current distance is:\t");
  Serial.println(distance);


  // ==========================
  // SAFE ZONE
  // ==========================
  if(distance >= 50) {

    digitalWrite(buzzpin, LOW);

    blinkLED(green_led, delay_time);

    ultra_response(distance50);

    Serial.println("SAFE ZONE");
  }


  // ==========================
  // WARNING ZONE
  // ==========================
  else if(distance >= 25 && distance < 50) {

    digitalWrite(buzzpin, HIGH);

    blinkLED(yellow_led, delay_time);

    ultra_response(distance25);

    Serial.println("WARNING ZONE");
  }


  // ==========================
  // DANGER ZONE
  // ==========================
  else if(distance >= 0 && distance < 25) {

    for(int i = 0; i < 5; i++) {

      digitalWrite(red_led, HIGH);
      digitalWrite(buzzpin, HIGH);

      delay(150);

      digitalWrite(red_led, LOW);
      digitalWrite(buzzpin, LOW);

      delay(150);
    }

    ultra_response(distance0);

    Serial.println("DANGER ZONE");
  }
}