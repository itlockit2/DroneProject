void setup() {
  
  //프로세싱과의 연결을 위한 시리얼을 사용
  //Serial1, Serial의 통신속도를 115200bps로 설정하고 있다. (초당 115200 비트)
  Serial.begin(115200);
  
}

void loop() {

  checkMspPacket();
  
}

//enum은 숫자에 이름을 붙이는 방법을 제공한다.
//HEAD1은 0 HEAD2는 1이다.
enum {
  HEAD1, HEAD2, HEAD3, DATASIZE, CMD,
  ROLL, PITCH, YAW, THROTTLE,
  AUX, CRC, PACKETSIZE,
};

//명령 메세지를 받을 수 있는 mspPacket 배열변수를 선언합니다.
uint8_t mspPacket[PACKETSIZE];


void printMspPacket() {
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


void checkMspPacket(){
  static uint32_t cnt;

  //Serial1에 데이터가 도착해 있고 데이터가 있는 동안에 데이터 하나를 읽는다.
  if(Serial.available() > 0){
    while(Serial.available() > 0) {
      uint8_t mspData = Serial.read();

      //mspData 값이 '$'이면 즉 메세지의 시작이면, cnt 값을 HEAD1으로 설정하여 메세지의 시작을 나타낸다.
      //HEAD1 은 그저 0이지만 가독성을 위해서 이렇게 지정해준다.
      //그렇게 데이터의 끝까지 cnt의 값을 증가시켜 준다.
      if(mspData == '$') cnt = HEAD1;
      else cnt++;

      
      mspPacket[cnt] = mspData;
      
      //그렇게 카운트 변수의값이 10이면 즉 CRC이면 데이터값을 출력한다.
      if(cnt == 10) {
      printMspPacket();
      }
    }
  }
}


