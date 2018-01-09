void setup() {
  //프로세싱과의 연결을 위한 시리얼을 사용
  //Serial1, Serial의 통신속도를 115200bps로 설정하고 있다. (초당 115200 비트)
  Serial.begin(19200);
}

  

void loop() {
  uint8_t userInput;
  //available 함수를 이용해서 Serial1에 데이터가 도착했는지를 확인한다.
  //available 함수는 도착한 데이터바이트의 개수를 리턴한다.
  if(Serial.available() >0){

    //read함수를 이용해서 1바이트(8비트)를 읽어낸다.
    userInput = Serial.read();

    //읽어낸 1바이트 데이터를 문자 형태로 Serial로 출력한다.
    Serial.println((char)userInput);
  }
}
