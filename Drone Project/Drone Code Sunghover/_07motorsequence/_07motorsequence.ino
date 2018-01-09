
void setup() {}


void loop() {

  analogWrite(3, 20); delay(1000);
  analogWrite(10, 20); delay(1000);
  analogWrite(9, 20); delay(1000);
  analogWrite(11, 20); delay(1000);

  analogWrite(3,0);
  analogWrite(10,0);
  analogWrite(9,0);
  analogWrite(11,0); delay(2000);
  
}



