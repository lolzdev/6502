int address[] = {23, 25, 27, 29, 41, 43, 45, 47, 49, 51};
int data[] = {9, 8, 7, 6, 5, 4, 3, 2};
#define OE 11
#define WE 10
#define CE 12
#define SIZE 0xfe

void setAddress(int a, int d) {
  digitalWrite(OE, HIGH);
  digitalWrite(WE, LOW);

  for (int i=0; i<=15; i++) {
    digitalWrite(address[i], ((a >> i) & 1) ? HIGH : LOW);
  }

  for (int i=8; i>=0; i--) {
    digitalWrite(data[i], ((d >> i) & 1) ? HIGH : LOW);
  }
}

void readAddress(int a) {
  digitalWrite(OE, LOW);
  digitalWrite(WE, HIGH);

  for (int i=0; i<=15; i++) {
    digitalWrite(address[i], ((a >> i) & 1) ? HIGH : LOW);
  }

  int n = 0;
  for (int i=8; i>=0; i--) {
    n = (n | (digitalRead(data[i]) ? 1 : 0) << i);
    Serial.print(digitalRead(data[i]) ? 1 : 0);
  }

  Serial.println();
  Serial.println(n);
}

void setup() {
  pinMode(OE, OUTPUT);
  pinMode(WE, OUTPUT);
  pinMode(CE, OUTPUT);

  digitalWrite(CE, LOW);

  for (int i=0; i<=15; i++) {
    pinMode(address[i], OUTPUT);
  }

  for (int i=0; i<=8; i++) {
    pinMode(data[i], OUTPUT);
  }

  Serial.begin(57600);

  for (int i=0; i<=SIZE; i++) {
    setAddress(i, 0);
  }

  setAddress(10, 14);
  readAddress(10);
}

void loop() {
  // put your main code here, to run repeatedly:

}
