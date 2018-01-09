void setup() {
  Serial1.begin(115200);

  //모터의 속도를 초기화 하는 함수이다.
  initMotorSpeed();
  
}

void loop() {
  //모터의 속도를 조절하는 함수이다.
  controlMotorSpeed();
}

//모터의 최대속도, 최저속도, 초기속도를 위해 
//상수값을 정의해 놓는다.
#define THROTTLE_MAX 255
#define THROTTLE_MIN 0
#define THROTTLE_INI 5

//throttle 변수는 모터의 속도를 저장할 변수이며
//최소값으로 초기화 하고 있다.
int throttle = THROTTLE_MIN;

//4개의 핀번호를 설정해놓는다.
int motorA_pin = 6;
int motorB_pin = 10;
int motorC_pin = 9;
int motorD_pin = 5;

//모터의 속도를 초기값으로 초기화 해주는 함수
//모든 핀번호의 모터의속도를 0으로 초기화 해준다.
void initMotorSpeed(){
  analogWrite(motorA_pin, THROTTLE_INI); delay(1000);
  analogWrite(motorB_pin, THROTTLE_INI); delay(1000);
  analogWrite(motorC_pin, THROTTLE_INI); delay(1000);
  analogWrite(motorD_pin, THROTTLE_INI); delay(1000);
}

//MSP 패킷을 확인하고, 모터의 속도를 수정한다.
void controlMotorSpeed(){
  //모터의 속도가 바뀌엇는지 확인하는 함수
  checkMspPacket();
  //모터의 속도를 수정하는 함수
  updateMotorSpeed();
}

//enum은 숫자에 이름을 붙이는 방법을 제공한다.
//HEAD1은 0 HEAD2는 1이다.
enum {
  HEAD1, HEAD2, HEAD3, DATASIZE, CMD,
  ROLL, PITCH, YAW, THROTTLE,
  AUX, CRC, PACKETSIZE,
};

void checkMspPacket(){
  static unit32_t cnt;

  //Serial1에 데이터가 도착해 있고 데이터가 있는 동안에 데이터 하나를 읽는다.
  if(Serial1.available() > 0){
    while(Serial1.available() > 0) {
      unit8_t mspData = Serial1.read();

      //mspData 값이 '$'이면 즉 메세지의 시작이면, cnt 값을 HEAD1으로 설정하여 메세지의 시작을 나타낸다.
      //HEAD1 은 그저 0이지만 가독성을 위해서 이렇게 지정해준다.
      //그렇게 데이터의 끝까지 cnt의 값을 증가시켜 준다.
      if(mspData == '$') cnt = HEAD1;
      else cnt++;

      
      mspPacket[cnt] = mspData;
      
      //그렇게 카운트 변수의값이 10이면 즉 CRC이면 
      //CMD가 저장되어있는 곳의 값을 확인해서 150이면 저장한 throttle의 값을 변경해준다.
      if(cnt == CRC) {
        if(mspPacket[CMD] == 150){
          throttle = mspPacket[THROTTLE];
        }
      }
    }
  }
}

//모터의 속도를 수정된 값으로 업데이트 해준다.
void updateMotorSpeed() {
  analogWrite(motorA_pin, throttle); 
  analogWrite(motorB_pin, throttle); 
  analogWrite(motorC_pin, throttle); 
  analogWrite(motorD_pin, throttle);
}

