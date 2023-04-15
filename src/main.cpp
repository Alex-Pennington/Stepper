#include <Arduino.h>
#include <main.h>

void P_event() {
    P_counter++;
}

void setup() {
  Serial.begin(9600);

  //Configure the LED for output and sets the intial state to off
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  serial_commands_.SetDefaultHandler(cmd_unrecognized);
  serial_commands_.AddCommand(&cmd_led_on_);
  serial_commands_.AddCommand(&cmd_led_off_);
  serial_commands_.AddCommand(&cmd_stepper_ccw_);
  serial_commands_.AddCommand(&cmd_stepper_cw_);
  serial_commands_.AddCommand(&cmd_stepper_stop_);
  serial_commands_.AddCommand(&cmd_home_);
  serial_commands_.AddCommand(&cmd_0_);
  serial_commands_.AddCommand(&cmd_1_);
  serial_commands_.AddCommand(&cmd_s_);
  serial_commands_.AddCommand(&cmd_h_);
  serial_commands_.AddCommand(&cmd_p_);

  stepper.setMaxSpeed(700);
  stepper.setAcceleration(1);
  stepper.setMinPulseWidth(50);

  attachInterrupt(0,P_event,FALLING);

}

void loop() {
  //stepper.runSpeed();
  //stepper.setSpeed(analog_in);
  serial_commands_.ReadSerial();
  stepper.run();
}