/*
HC-SR04 Ping distance sensor]
VCC to arduino 5v GND to arduino GND
Echo to Arduino pin 13 Trig to Arduino pin 12
Red POS to Arduino pin 11
Green POS to Arduino pin 10
560 ohm resistor to both LED NEG and GRD power rail
More info at: http://goo.gl/kJ8Gl
Original code improvements to the Ping sketch sourced from Trollmaker.com
Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
*/

const int trigPin = 13; //trig pins connected to a ditialpin
                   //and sends a pulse out when a signal (high or low)
                   //is sent to the transmitter
const int echoPin = 12; //echo pin receives the sound pulse when it bounces off the object.
const int led = 11;
const int led2 = 10;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  //when trigger is given high pulse for 10 microseconds
  //the transmitter emits ultrasound and the timer begins
  //the emitted ultrasound bounce back to the receiver once
  //it hit any obstacle and the timer stops.

  long duration, distance;

  
  //to start, give a short LOW pulse beforehand to ensure a clean HIGH pulse
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);

  //the sensor is triggered by a HIGH pulse of 10 or more microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  //set the trig pin to LOW so that the echo pin will
  //only measure the HIGH pulse that was sent previously
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // high means that the pulsin() will
                                    //wait for the pin to go HIGH caused by the 
                                    //bounce sound wave and it will start timing
                                    //then it will wait fo the pin to go LOW when the
                                    //sound wave will end, which will stop the timing.
                                    //At the end the funciton will return the length
                                    //of the pulse in microseconds 
  distance = duration * 0.0341/2; //speed of sound is 0.034cm/us
//                                    // divide by 2 because sound wave travels forward
//                                    //and bounces back. distance in cm is s=t*0.034/2
  if (distance < 30) {  // This is where the LED On/Off happens
    digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
  digitalWrite(led2,LOW);
}
  else {
    digitalWrite(led,LOW);
    digitalWrite(led2,HIGH);
  }
  delay(100); //delays the next wave --> the higher the number, the longer
              //it takes for the lights to react
}

