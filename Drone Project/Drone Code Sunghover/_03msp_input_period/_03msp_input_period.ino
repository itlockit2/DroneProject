void setup() {
  
  //프로세싱과의 연결을 위한 시리얼을 사용
  //Serial1, Serial의 통신속도를 115200bps로 설정하고 있다. (초당 115200 비트)
  Serial1.begin(115200);
  Serial.begin(115200);
  
}

void loop() {
  static unit32_t t_now, t_prev;
  static unit32_t msp_period;

  if(Serial1.available()) {
    unit8_t mspData = Serial1.read();
    
    //mspData 값이 '$'이면 즉 메세지의 시작이면
    if(mspData == '$'){
      
      //micors 함수를 이용해서 t_now 변수에 현재 시간을 마이크로 초 값으로 읽는다.
      t_now = micros();
      
      //msp_period 에는 현재 시간과 전의 시간을 빼준다.
      msp_period = t_now - t_prev;
      
      //예전 시간은 현재시간으로 변경해주고 
      t_prev = t_now;

      //msp_period변수값을 십진수로 출력한다.
      Serial.println(msp_period, DEC);
    }
  }
}
