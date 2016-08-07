#include <Arduino.h>

// PID variables
double pid_roll_in,   pid_roll_out,   pid_roll_setpoint = 0;
double pid_pitch_in,  pid_pitch_out,  pid_pitch_setpoint = 0;
double pid_yaw_in,    pid_yaw_out,    pid_yaw_setpoint = 0;

void setup() {
  Serial.begin(115200);
  MpuInitialize();
  Serial.println("");Serial.print("MPU DONE");
  MotorsInitialize();
  ActivateMotors();
  Serial.println("");Serial.print("MOTORS DONE");
  pid_initialize();
}

void loop() {
   ReadFromWifi();
   MpuUpdate();
   pid_update();
   pid_compute();
   UpdateMotors();
}
