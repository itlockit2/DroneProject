void setup() {
  
  //프로세싱과의 연결을 위한 시리얼을 사용
  //Serial1, Serial의 통신속도를 115200bps로 설정하고 있다. (초당 115200 비트)
  Serial1.begin(115200);
  Serial.begin(115200);
  
}

  //메세지는 11바이트로 구성된다 이 11바이트의 메세지는 차례대로 mspPacket 배열변수에 저장된다.
  unit8_t mspPacket[11];

void loop() {

  static unit32_t cnt;
  
  //데이터가 도착하면 그리고 데이터가 있는 동안에 데이터를 하나 읽어서 mspData에 저장해준다.
  //그리고 값을 mspPacket 배열변수에 저장한다.
  if(Serial1.available() > 0){
    while(Serial1.available() > 0){
      unit8_t mspData = Serial1.read();
      if(mspData == '$') cnt = 0;
      else cnt ++;

      mspPacket[cnt] = mspData;

      if(cnt == 10) printMspPacket();
    }
  }
}

void printMspPacket(); {
  Serial.print((char)mspPacket[0]);
  Serial.print((char)mspPacket[1]);
  Serial.print((char)mspPacket[2]);
  Serial.print(mspPacket[3]);
  Serial.print(' ');
  Serial.print(mspPacket[4]);
  Serial.print('\t');
  Serial.print("R: ");
  Serial.print(mspPacket[5]);
  Serial.print('\t');
  Serial.print("P: ");
  Serial.print(mspPacket[6]);
  Serial.print('\t');
  Serial.print("Y: ");
  Serial.print(mspPacket[7]);
  Serial.print('\t');
  Serial.print("T: ");
  Serial.print(mspPacket[8]);
  Serial.print('\t');
  Serial.print(mspPacket[9]);
  Serial.print(' ');
  Serial.print(mspPacket[10]);
  Serial.print('\n');
}

