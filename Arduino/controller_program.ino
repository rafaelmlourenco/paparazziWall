int CONTROL_BUTTON = 2;
int STATUS_LED = 3;

int INIT_STATUS = 1;
int INIT_STATUS_DURATION = 1000;
int STOP_STATUS = 3;
int STOP_STATUS_DURATION = 150;
int ERROR_SERIAL = 2;
int ERROR_SERIAL_DURATION = 500;

String START_FLASHING_MSG = "Start Flashing";
String READY_MSG = "Arduino is ready!";
int switchState = 0;
//long randNumber;
String rcvString;
bool flashState = false;

void setup() {
  //Initialize Serial Port (USB)
  Serial.begin(9600);

  // put your setup code here, to run once:
  pinMode(STATUS_LED, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  
  // Control button (stop button)
  pinMode(CONTROL_BUTTON, INPUT);

  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
  blinkStatusLED(INIT_STATUS, INIT_STATUS_DURATION);
  Serial.println(READY_MSG);
}

void loop() {
  // put your main code here, to run repeatedly:
  switchState = digitalRead(CONTROL_BUTTON);

  if (switchState == HIGH) {
    flashState = false;
    blinkStatusLED(STOP_STATUS, STOP_STATUS_DURATION);
  }

  if (Serial.available() > 0) {
    handleSerialMsg();
  }

  if (flashState) {
    int randomDuration = random(200, 300);
    flashSingleRandomly(randomDuration);
  }
} // go back to the beginning of the loop

void flashSingleRandomly(int duration) {
  int portNumber = random(4, 11);
  digitalWrite(11, HIGH);
  digitalWrite(portNumber, HIGH);
  delay(duration);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  delay(duration);
}

void handleSerialMsg() {
  rcvString = Serial.readString();
  if (rcvString == START_FLASHING_MSG) {
    digitalWrite(STATUS_LED, HIGH);
    flashState = true;
  } else {
    flashState = false;
    blinkStatusLED(ERROR_SERIAL,ERROR_SERIAL_DURATION);
  }
}

void blinkStatusLED(int number, int duration) {
  for (int i = 0; i < number; i++) {
    digitalWrite(STATUS_LED, HIGH);
    delay(duration);
    digitalWrite(STATUS_LED, LOW);
    delay(100);
  }
}

