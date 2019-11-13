int CAPTOR = A3;
int LED = 3; // Port on which the led is
int THRESHOLD = 50;

// the torsion values  must be calibrated beforehand
int RAW_TORSION_MIN = 130;
int RAW_TORSION_MAX = 460;
int RAW_TORSION_MOY = 380;

// we initialize a variable to keep the current torsion stored
int torsion = RAW_TORSION_MOY;

int getTorsion(int captor) {
  return analogRead(captor);
}

/**
 * Set led on a digital pin
 * If the difference between the current raw torsion and
 * the average raw torsion is greater than THRESHOLD,
 * the led is lit.
 */
int reactTorsion(int led, int torsion) {
  if (abs(torsion - RAW_TORSION_MOY) > THRESHOLD) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}


int convertTorsion(int torsion) {
  return map(torsion, RAW_TORSION_MIN, RAW_TORSION_MAX, 0, 255);
}

void printTorsion(int torsion) {
  Serial.print("Torsion: ");
  Serial.print(torsion);
  Serial.print(" - Mapped torsion: ");
  Serial.println(convertTorsion(torsion));
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(CAPTOR, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  torsion = getTorsion(CAPTOR);
  printTorsion(torsion);
  analogWrite(LED, convertTorsion(torsion));
  //reactTorsion(LED, Torsion);
  delay(100);
}
