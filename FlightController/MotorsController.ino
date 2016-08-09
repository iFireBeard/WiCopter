#include <Servo.h>

#define PIN_M1 3
#define PIN_M2 5
#define PIN_M3 6
#define PIN_M4 9

#define MAX_SPEED 1250
#define MIN_SPEED 1000
#define MOTOR_ZERO 800 

Servo M1FrontLeft;
Servo M2FrontRight;
Servo M3RearRight;
Servo M4RearLeft;

short unsigned int motorsSpeed[4] = {MOTOR_ZERO,MOTOR_ZERO,MOTOR_ZERO,MOTOR_ZERO};
bool isMotorsRuning = false;

void MotorsInitialize() {
  M1FrontLeft.attach(PIN_M1);
  M2FrontRight.attach(PIN_M2);
  M3RearRight.attach(PIN_M3);
  M4RearLeft.attach(PIN_M4);
  M1FrontLeft.writeMicroseconds(MOTOR_ZERO);
  M2FrontRight.writeMicroseconds(MOTOR_ZERO);
  M3RearRight.writeMicroseconds(MOTOR_ZERO);
  M4RearLeft.writeMicroseconds(MOTOR_ZERO);
}

void ActivateMotors() {
  delay(2000);
  for (int i = MOTOR_ZERO; i >= MIN_SPEED;i+=10) {
    delay(50);
    if (i == 800) delay(1000);
    motorsSpeed[i] = i;
    writeToMotors(i, 4);
  }
  isMotorsRuning = true;
}

void DeactivateMotors() {
  isMotorsRuning = false;
  for (int i = MIN_SPEED; i <= MOTOR_ZERO;i-=10) {
    delay(50);
    writeToMotors(i, 4);
  }
}

void UpdateMotors() {
  int throttle = 1100;
//    m0 = throttle + pid_pitch_out ;//+ pid_yaw_out;
//  m1 = throttle + pid_roll_out ;//- pid_yaw_out;
//  m2 = throttle - pid_pitch_out ;//+ pid_yaw_out;
//  m3 = throttle - pid_roll_out ;//- pid_yaw_out;
//  motorsSpeed[0] = throttle + pid_pitch_out ;//+ pid_yaw_out;
//  motorsSpeed[1] = throttle + pid_roll_out ;//- pid_yaw_out;
//  motorsSpeed[2] = throttle - pid_pitch_out ;//+ pid_yaw_out;
//  motorsSpeed[3] = throttle - pid_roll_out ;//- pid_yaw_out;
  motorsSpeed[1] = throttle - pid_pitch_out + pid_roll_out;// - pid_output_yaw; //Calculate the pulse for esc 1 (front-right - CCW)
  motorsSpeed[2] = throttle + pid_pitch_out + pid_roll_out;// + pid_output_yaw; //Calculate the pulse for esc 2 (rear-right - CW)
  motorsSpeed[3] = throttle + pid_pitch_out - pid_roll_out;// - pid_output_yaw; //Calculate the pulse for esc 3 (rear-left - CCW)
  motorsSpeed[0] = throttle - pid_pitch_out - pid_roll_out;// + pid_output_yaw; //Calculate the pulse for esc 4 (front-left - CW)


  //Serial.print("ROLL=");Serial.print(pid_roll_out);Serial.print("(");Serial.print(roll);Serial.println(")");
  //Serial.print("PICTH=");Serial.print(pid_pitch_out);;Serial.print("(");Serial.print(pitch);Serial.println(")");
  
  if (isMotorsRuning)
  for (byte i = 0; i <= 3; i++)
  if (motorsSpeed[i] < MIN_SPEED) {
    if (isMotorsRuning) {
    writeToMotors(MIN_SPEED, i);
    } else { writeToMotors(motorsSpeed[i], i); }
  } else if (motorsSpeed[i] > MAX_SPEED) {
    writeToMotors(MAX_SPEED, i);
  } else {
    writeToMotors(motorsSpeed[i], i);
  }
}

void writeToMotors(short unsigned int speed, int motor) {
    switch (motor) {
    case 0: M1FrontLeft.writeMicroseconds(speed); break;
    case 1: M2FrontRight.writeMicroseconds(speed); break;
    case 2: M3RearRight.writeMicroseconds(speed); break;
    case 3: M4RearLeft.writeMicroseconds(speed); break;
    case 4: 
    M1FrontLeft.writeMicroseconds(speed);
    M2FrontRight.writeMicroseconds(speed);
    M3RearRight.writeMicroseconds(speed);
    M4RearLeft.writeMicroseconds(speed); break;
    }
    Serial.println("");Serial.print(motor);Serial.print("MOTOR=(");Serial.print(speed);Serial.print(")");
    //Serial.println("");Serial.print("roll");Serial.print(roll);Serial.print("pitch");Serial.print(pitch);Serial.print("yaw");Serial.print(yaw);
}

