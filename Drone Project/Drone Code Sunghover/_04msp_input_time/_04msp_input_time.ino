void setup() {
  
  //프로세싱과의 연결을 위한 시리얼을 사용
  //Serial1, Serial의 통신속도를 115200bps로 설정하고 있다. (초당 115200 비트)
  Serial1.begin(115200);
  Serial.begin(115200);
  
}

void loop() {

  static unit32_t t_head1, t_crc;
  static unit32_t msp_time;
  static unit32_t cnt;

  if(Serial1.available()){
    unit8_t mspData = Serial1.read();
    
    //만약 mspData 의 값이 '$'이면 즉 메세지의 시작이면
    //현재 시간을 마이크로 초 값으로 읽고 카운트값을 0으로 초기화 시켜준다.
    if(mspData == '$'){
      t_head1 = micros();
      cnt = 0;
    } else cnt++;

    //그렇게 값을 증가시켜서 카운트가 10이되면
    //micors함수를 다시 호출하여 t_crc변수에 현재시간을 마이크로 초 값으로 일고
    //그 시간을 메세지 시작할때 저장한 t_head1 에 빼서 msp_time에 저장한다.
    //그럼이제 msp_time의 값은 메세지전송시간이고 그 값을 십진수로 출력해준다.
    if(cnt == 10){
      t_crc = micros();
      msp_time = t_crc  - t_head1;

      Serial.println(msp_time, DEC);
    }
  }
  
}
