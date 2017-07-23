//set pin numbers
//const won't change

const int ledPin = 11; //the number of the LED pin
const int ldrPin = A0; //the number of the LDR pin

void setup() {

  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); //initializes the LED pin as an output
  pinMode(ldrPin, INPUT); //initializes the LDR pin as an input
}

void loop(){

  int ldrStatus = analogRead(ldrPin); //read the status of the LDR value

  // check if the LDR status <=300
  //if it is, the LED is HIGH

  if (ldrStatus <= 300) {
    digitalWrite(ledPin, HIGH);
    Serial.println(ldrStatus);
  }

  else {

    digitalWrite(ledPin, LOW);
    Serial.print (ldrStatus);
    Serial.print ('\n');
  }
}

