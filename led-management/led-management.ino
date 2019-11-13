int DELAY_SHORT = 42;
int DELAY_LONG = 3*DELAY_SHORT;
int LED_PIN = LED_BUILTIN;
int LED_AUX = 12;
int LED_RED = 6;
int LED_GREEN = 5;
int LED_BLUE = 3;

void ledUpLong(int led) {
  digitalWrite(led, HIGH);
  delay(DELAY_LONG);
}

void ledUpShort(int led) {
  digitalWrite(led, HIGH);
  delay(DELAY_SHORT);
}

void ledLowLong(int led) {
  digitalWrite(led, LOW);
  delay(DELAY_LONG);
}

void ledLowShort(int led) {
  digitalWrite(led, LOW);
  delay(DELAY_SHORT);
}

void sosBlink(int led) {
  for (int i = 0; i<3; i++) {
    ledUpShort(led);
    ledLowShort(led);
  }
  for (int i = 0; i<3; i++) {
    ledUpLong(led);
    ledLowShort(led);
  }
  for (int i = 0; i<3; i++) {
    ledUpShort(led);
    ledLowShort(led);
  }
}

void normalBlink(int led) {
  ledUpShort(led);
  ledLowShort(led);
}

void ledColorRGB(int red, int green, int blue) {
  analogWrite(LED_RED, red);
  analogWrite(LED_GREEN, green);
  analogWrite(LED_BLUE, blue);
}

void varColors(int redB, int redF, int greenB, int greenF, int blueB, int blueF, int steps, int delay_t) {
  /*
   * Ne fonctionne pas, affiche toujours les valeurs initiales
   */
  int red = 0;
  int green = 0;
  int blue = 0;
  for (int i = 0; i < steps ; i++) {
    red = i/steps * (redF - redB) + redB;
    green = i/steps * (greenF - greenB) + greenB;
    blue = i/steps * (blueF - blueB) + blueB;
    Serial.println(i); Serial.println(red); Serial.println(green); Serial.println(blue);
    Serial.println("---");
    ledColorRGB(red, green, blue);
    delay(delay_t);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Booting up...");
  //pinMode(LED_PIN, OUTPUT);
  //pinMode(LED_AUX, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}

void loop() {
  //ledColorRGB(0, 50, 0);
  varColors(200, 20, 0, 100, 75, 0, 5, 500);
}
