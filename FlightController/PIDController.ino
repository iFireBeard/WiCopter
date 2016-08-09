#include <PID_v1.h>

#define ROLL_PID_MIN  -200.0
#define ROLL_PID_MAX  200.0
#define PITCH_PID_MIN  -200.0
#define PITCH_PID_MAX  200.0
#define YAW_PID_MIN  100.0
#define YAW_PID_MAX  100.0

PID roll_controller(&pid_roll_in,   &pid_roll_out,  &pid_roll_setpoint,  1.0, 0.0, 0.0, DIRECT);
PID pitch_controller(&pid_pitch_in, &pid_pitch_out, &pid_pitch_setpoint, 1.0, 0.0, 0.0, DIRECT);
PID yaw_controller(&pid_yaw_in,     &pid_yaw_out,   &pid_yaw_setpoint,   1.0, 0.0, 0.0, DIRECT); 


void pid_initialize() {
  roll_controller.SetOutputLimits(ROLL_PID_MIN,ROLL_PID_MAX);
  pitch_controller.SetOutputLimits(PITCH_PID_MIN,PITCH_PID_MAX);
  yaw_controller.SetOutputLimits(YAW_PID_MIN,YAW_PID_MAX);
  roll_controller.SetMode(AUTOMATIC);
  pitch_controller.SetMode(AUTOMATIC);
  yaw_controller.SetMode(AUTOMATIC);
  roll_controller.SetSampleTime(10);
  pitch_controller.SetSampleTime(10);
  yaw_controller.SetSampleTime(10);
}

void roll_tuning(double tkP, double tkI, double tkD) {
  roll_controller.SetTunings(tkP,tkI,tkD);
}
void pitch_tuning(double tkP, double tkI, double tkD) {
  pitch_controller.SetTunings(tkP,tkI,tkD);
}

void pid_update(){
  pid_roll_in = roll;
  pid_pitch_in = pitch;
  pid_yaw_in = yaw; 
}

void pid_compute() {
   roll_controller.Compute();
   pitch_controller.Compute();
   yaw_controller.Compute();
}
