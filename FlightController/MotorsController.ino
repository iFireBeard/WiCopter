#include <Servo.h>

#define PIN_M1 3
#define PIN_M2 5
#define PIN_M3 6
#define PIN_M4 9

#define MAX_SPEED 1600
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
    writeToMotors(i);
  }
  isMotorsRuning = true;
}

void DeactivateMotors() {
  isMotorsRuning = false;
  for (int i = MIN_SPEED; i <= MOTOR_ZERO;i-=10) {
    delay(50);
    writeToMotors(i);
  }
}

void UpdateMotors() {
  if (isMotorsRuning)
  for (byte i = 0; i <= 3; i++)
  if (motorsSpeed[i] < MIN_SPEED) {
    if (isMotorsRuning) {
    writeToMotors(MIN_SPEED);
    } else { writeToMotors(motorsSpeed[i]); }
  } else if (motorsSpeed[i] > MAX_SPEED) {
    writeToMotors(MAX_SPEED);
  } else {
    writeToMotors(motorsSpeed[i]);
  }
}

void writeToMotors(short unsigned int speed) {
    M1FrontLeft.writeMicroseconds(speed + pid_pitch_out);
    M2FrontRight.writeMicroseconds(speed + pid_roll_out);
    M3RearRight.writeMicroseconds(speed - pid_pitch_out);
    M4RearLeft.writeMicroseconds(speed - pid_roll_out);
    Serial.println("MOTOR1");Serial.print(speed + pid_pitch_out);
        Serial.println("MOTOR2");Serial.print(speed + pid_roll_out);
            Serial.println("MOTOR3");Serial.print(speed + pid_pitch_out);
                Serial.println("MOTOR4");Serial.print(speed - pid_roll_out);
}

