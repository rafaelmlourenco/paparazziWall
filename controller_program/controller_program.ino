int CONTROL_BUTTON = 2;
int STATUS_LED = 3;
int FLASH_01 = 4;
int FLASH_02 = 5;
int FLASH_03 = 6;
int FLASH_04 = 7;
int FLASH_05 = 8;
int FLASH_06 = 9;
int FLASH_07 = 10;
int CAMERA_SHUTTER = 11;

int INIT_STATUS = 1;
int INIT_STATUS_DURATION = 1000;
int STOP_STATUS = 3;
int STOP_STATUS_DURATION = 150;
int ERROR_SERIAL = 2;
int ERROR_SERIAL_DURATION = 500;

unsigned long FLASHING_DURATION = 10000;

int switchState = 0;
bool flashState = true;
bool lastState = false;
bool isConnected = true;

unsigned long startTime = 0;
unsigned long currentTime = 0;

String START_FLASHING_MSG = "Start Flashing";
String READY_MSG = "Arduino is ready!";

String rcvString;

void setup() {
  //Initialize Serial Port (USB)
  Serial.begin(9600);

  // put your setup code here, to run once:
  pinMode(STATUS_LED, OUTPUT);
  pinMode(FLASH_01, OUTPUT);
  pinMode(FLASH_02, OUTPUT);
  pinMode(FLASH_03, OUTPUT);
  pinMode(FLASH_04, OUTPUT);
  pinMode(FLASH_05, OUTPUT);
  pinMode(FLASH_06, OUTPUT);
  pinMode(FLASH_07, OUTPUT);
  pinMode(CAMERA_SHUTTER, OUTPUT);

  // Control button (stop button)
  //  pinMode(CONTROL_BUTTON, INPUT);

  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
  blinkStatusLED(INIT_STATUS, INIT_STATUS_DURATION);
}

void loop() {
  while (!Serial) {
    // Do nothing... Wait for serial connection...
    isConnected = false;
  }

  // put your main code here, to run repeatedly:
  if (!isConnected) {
    isConnected = true;
    Serial.println(READY_MSG);
  }

  // readControlSwitch();
  updateFlashStateWithTimeCheck();
 
  if (Serial.available() > 0) {
    handleSerialMsg();
  }

  if (flashState) {
    int randomDuration = random(200, 300);
    flashSingleRandomly(randomDuration);
  }

  // Iterate (next time the lastState will be the current one)
  lastState = flashState;
  } // go back to the beginning of the loop

void updateFlashStateWithTimeCheck(){
  if (lastState == false && flashState == true) {
    startTime = millis();
  }

  currentTime = millis();

  if (currentTime - startTime >= FLASHING_DURATION) {
    flashState = false;
    digitalWrite(STATUS_LED, LOW);
  }
}

void readControlSwitch() {
  //  switchState = digitalRead(CONTROL_BUTTON);
  //
  //  if (switchState == HIGH) {
  //    flashState = false;
  //    blinkStatusLED(STOP_STATUS, STOP_STATUS_DURATION);
  //    startTime = 0;
  //  }
}

void flashSingleRandomly(int duration) {
  int portNumber = random(4, 11);
  digitalWrite(CAMERA_SHUTTER, HIGH);
  digitalWrite(portNumber, HIGH);

  delay(duration);

  digitalWrite(CAMERA_SHUTTER, LOW);
  digitalWrite(portNumber, LOW);
//  digitalWrite(FLASH_02, LOW);
//  digitalWrite(FLASH_03, LOW);
//  digitalWrite(FLASH_04, LOW);
//  digitalWrite(FLASH_05, LOW);
//  digitalWrite(FLASH_06, LOW);
//  digitalWrite(FLASH_07, LOW);

  delay(duration);
}

void handleSerialMsg() {
  rcvString = Serial.readString();
  if (rcvString == START_FLASHING_MSG) {
    digitalWrite(STATUS_LED, HIGH);
    flashState = true;
  } else {
    flashState = false;
    blinkStatusLED(ERROR_SERIAL, ERROR_SERIAL_DURATION);
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
