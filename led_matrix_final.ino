const byte interruptPin = 2;
volatile byte state = LOW;
int voltage = 0;

int buttonState;
int lastButtonState = LOW;
// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  Serial.begin(9600);
  DDRD = B11111110; //controls pins 0-7
  DDRB = B00001111; //controls pins 8-13
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(A5, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), choose, RISING);
}

void loop() {
  
  if (state == HIGH) {
    voltage = analogRead(5);
    if(voltage <= 1023 && voltage >= 1020) {
      flashLeftArrow();
    } else if (voltage <= 820 && voltage >= 816) {
       flashRightArrow();
    } 
  }
  
  if (state == LOW) {
    off();
  }
  Serial.println(voltage);
  state=!state;
}

void choose() {

  // buttons sometimes generate odd transitions when pressed, and these transistions can 
  // be read as multiple button pushes, fooling the program. To fix this, we use the 
  // debounce function to debounce the input, which means it checks twice to see if the 
  // button was actually pressed
  
  // read the state of the switch into a local variable:
  int reading = digitalRead(interruptPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the state if the new button state is HIGH
      if (buttonState == HIGH) {
        state = !state;
      }
    }
  
  }
}

void off() {
  PORTD = B00000000; //0-7
  PORTB = B00000000; //8-13
}

void ptOne() {
  PORTD = B11111000;
  PORTB = B00000111;
}

void ptTwo() {
  PORTD = B01110000;
  PORTB = B00001011;
}

void ptThree() {
  PORTD = B00100000;
  PORTB = B00001101;
}

void ptFour() {
  PORTD = B00100000;
  PORTB = B00001110;
}

void flashLeftArrow() {
  ptOne();
  delay (10);
  ptTwo();
  delay (10);
  ptThree();
  delay(10);
  ptFour();
  delay(10);
}

void ptFive() {
  PORTD = B11111000;
  PORTB = B00001110;
}

void ptSix() {
  PORTD = B01110000;
  PORTB = B00001101;
}

void ptSeven() {
  PORTD = B00100000;
  PORTB = B00001011;
}

void ptEight() {
  PORTD = B00100000;
  PORTB = B00000111;
}

void flashRightArrow() {
  ptFive();
  delay (10);
  ptSix();
  delay (10);
  ptSeven();
  delay(10);
  ptEight();
  delay(10);
}
