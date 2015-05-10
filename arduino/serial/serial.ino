int incomingByte = 0;
int buf[2];
int idx = 0;

void setup() {
  // put your setup code here, to run once:
    pinMode(13, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    buf[idx] = Serial.read();
    idx = (idx+1) % 2;
    if (idx == 1) { // buf is full
      digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(500);              // wait for a second
      digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
      delay(500);      
    }
  }
}
