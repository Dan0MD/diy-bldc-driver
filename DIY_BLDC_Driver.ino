

//char PWMValue;
char bldc_step = 0;
char motorSpeed;
int i= 0;
//char PWM_MAX_DUTY = 200;
//char PWM_MIN_DUTY = 50;
char PWM_START_DUTY = 100;
char pwmA = 11;
char pwmB = 10;
char pwmC = 9;
char coilA = 8;
char coilB = 7;
char coilC = 6;
char crossA = 5;
char crossB = 4;
char crossC = 3;
char ZERO_CROSS_A = 0;
char ZERO_CROSS_B = 0;
char ZERO_CROSS_C = 0;
boolean MOTOR_WARM = false;
void setup() {
  Serial.begin(9600);
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(pwmC, OUTPUT);
  pinMode(coilA, OUTPUT);
  pinMode(coilB, OUTPUT);
  pinMode(coilC, OUTPUT);
  pinMode(crossA, INPUT);
  pinMode(crossB, INPUT);
  pinMode(crossC, INPUT);
  motorSpeed = PWM_START_DUTY;
}
void bldc_move(){
  switch(bldc_step){
    case 0:
      AH_BL();
      BEMF_C_RISING();
      break;
    case 1:
      AH_CL();
      BEMF_B_FALLING();
      break;
    case 2:
      BH_CL();
      BEMF_A_RISING();
      break;
    case 3:
      BH_AL();
      BEMF_C_FALLING();
      break;
    case 4:
      CH_AL();
      BEMF_B_RISING();
      break;
    case 5:
      CH_BL();
      BEMF_A_FALLING();
      break;
  }
}

void loop() {
//  while(MOTOR_WARM == false){
////    SET_PWM_DUTY(PWM_START_DUTY);
//    motorSpeed = PWM_START_DUTY;
//    i = 5000;
//    while(i > 100) {
//      delayMicroseconds(i);
//      bldc_move();
////      bldc_step++;
////      bldc_step %= 6;
//      i = i - 20;
//    }
//    MOTOR_WARM = true;
//  }
  bldc_move();
}
void BEMF_A_RISING(){
  while (bldc_step == 2){
//    if (ZERO_CROSS_A == 0)
      ZERO_CROSS_A = digitalRead(crossA);
    if (ZERO_CROSS_A == 1)
      bldc_step = 3; 
  }
}
void BEMF_A_FALLING(){
  while (bldc_step == 5)
//    if (ZERO_CROSS_A == 1)
      ZERO_CROSS_A = digitalRead(crossA);
    if (ZERO_CROSS_A == 0) 
      bldc_step = 0; 
}
void BEMF_B_RISING(){
  while (bldc_step == 4){
//    if (ZERO_CROSS_B == 0)
      ZERO_CROSS_B = digitalRead(crossB);
    if (ZERO_CROSS_B == 1)
      bldc_step = 5;
  }
}
void BEMF_B_FALLING(){
  while (bldc_step == 1)
//    if (ZERO_CROSS_B == 1)
      ZERO_CROSS_B = digitalRead(crossB);
    if (ZERO_CROSS_B == 0)
      bldc_step = 2;
}
void BEMF_C_RISING(){
  while (bldc_step == 0){
//    if (ZERO_CROSS_C == 0)
      ZERO_CROSS_C = digitalRead(crossC);
    if (ZERO_CROSS_C == 1) 
      bldc_step = 1;
  }
}
void BEMF_C_FALLING(){
  while (bldc_step == 3)
//    if (ZERO_CROSS_C == 1)
      ZERO_CROSS_C = digitalRead(crossC);
    if (ZERO_CROSS_C == 0)
      bldc_step = 4;  
}
void AH_BL(){
  digitalWrite(pwmC, LOW);
  digitalWrite(pwmB, LOW);
  digitalWrite(coilA, HIGH);
  digitalWrite(coilB, LOW);
  analogWrite(pwmA, motorSpeed);
  digitalWrite(pwmB, HIGH);
}
void AH_CL(){
  digitalWrite(pwmA, LOW);
  digitalWrite(pwmB, LOW);
  digitalWrite(coilA, HIGH);
  digitalWrite(coilC, LOW);
  analogWrite(pwmA, motorSpeed);
  digitalWrite(pwmC, HIGH);
}
void BH_CL(){
  digitalWrite(pwmA, LOW);
  digitalWrite(pwmC, LOW);
  digitalWrite(coilB, HIGH);
  digitalWrite(coilC, LOW);
  analogWrite(pwmB, motorSpeed);
  digitalWrite(pwmC, HIGH);
}
void BH_AL(){
  digitalWrite(pwmB, LOW);
  digitalWrite(pwmC, LOW);
  digitalWrite(coilB, HIGH);
  digitalWrite(coilA, LOW);
  analogWrite(pwmB, motorSpeed);
  digitalWrite(pwmA, HIGH);
}
void CH_AL(){
  digitalWrite(pwmB, LOW);
  digitalWrite(pwmA, LOW);
  digitalWrite(coilC, HIGH);
  digitalWrite(coilA, LOW);
  analogWrite(pwmC, motorSpeed);
  digitalWrite(pwmA, HIGH);
}
void CH_BL(){
  digitalWrite(pwmC, LOW);
  digitalWrite(pwmA, LOW);
  digitalWrite(coilC, HIGH);
  digitalWrite(coilB, LOW);
  analogWrite(pwmC, motorSpeed);
  digitalWrite(pwmB, HIGH);
}
//void SET_PWM_DUTY(char duty){
//  if(duty < PWM_MIN_DUTY)
//    duty = PWM_MIN_DUTY;
//  if(duty > PWM_MAX_DUTY)
//    duty = PWM_MAX_DUTY;
//}
