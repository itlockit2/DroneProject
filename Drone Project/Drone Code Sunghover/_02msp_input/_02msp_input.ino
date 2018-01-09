void setup() {
  //프로세싱과의 연결을 위한 시리얼을 사용
  //Serial1, Serial의 통신속도를 115200bps로 설정하고 있다. (초당 115200 비트)
  Serial1.begin(115200);
  Serial.begin(115200);
}

void loop() {
  //Serial1에 데이터가 도착했는지 확인하는 메소드이다.
  //만약 데이터가 도착해 있으면 데이터를 읽어 Serial로 문자와 십진수로 출력해준다.
 if(Serial1.available()){
  unit8_t mspDate = Serial1.read();
  Serial.print((char)mspData);
  Serial.print('t');
  Serial.println(mspData, DEC);
 }
}
