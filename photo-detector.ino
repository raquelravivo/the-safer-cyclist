////set pin numbers
////const won't change
//
//const int ledPin = 11; //the number of the LED pin
//const int ldrPin = A0; //the number of the LDR pin
//
//void setup() {
//
//  Serial.begin(9600);
//  pinMode(ledPin, OUTPUT); //initializes the LED pin as an output
//  pinMode(ldrPin, INPUT); //initializes the LDR pin as an input
//}
//
//void loop(){
//
//  int ldrStatus = analogRead(ldrPin); //read the status of the LDR value
//
//  // check if the LDR status <=300
//  //if it is, the LED is HIGH
//
//  if (ldrStatus <= 300) {
//    digitalWrite(ledPin, HIGH);
//    Serial.println(ldrStatus);
//  }
//
//  else {
//
//    digitalWrite(ledPin, LOW);
//    Serial.print (ldrStatus);
//    Serial.print ('\n');
//  }
//}
int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the sensor divider
int LEDpin = 11;          // connect Red LED to pin 11 (PWM pin)
int LEDbrightness;        //  brightness of LED 
void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);   
}
 
void loop(void) {
  photocellReading = analogRead(photocellPin); //reading the state of the photocell
 
  Serial.print("Analog reading = ");
  Serial.println(photocellReading); 
  Serial.println('\n');
 
  // LED gets brighter the darker it is at the sensor
  // that means we have to invert the reading from 0-1023 back to 1023-0
  photocellReading = 1023 - photocellReading;
  //now we have to map 0-1023 to 0-255 since thats the range analogWrite uses
  LEDbrightness = map(photocellReading, 0, 1023, 0, 255); // re-maps a number from one range to another
                                                            //map(value, fromLow, fromHigh, toLow, toHigh)
                                     
  analogWrite(LEDpin, LEDbrightness);
 
  delay(100);
}
