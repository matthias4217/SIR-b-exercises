int CAPTOR = A3;
int LED = 2;
int THRESHOLD = 50;

int torsion = 380;

int getTorsion(int captor) {
  return analogRead(captor);
}

int reactTorsion(int led, int torsion) {
  if (abs(torsion - 380) > THRESHOLD) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(CAPTOR, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  torsion = getTorsion(CAPTOR);
  reactTorsion(LED, torsion);
  delay(100);
}
