#include <Arduino.h>
#include <main.h>

void P_event()
{
  P_counter++;
}

void setup()
{
  Serial.begin(9600);

  // Start the I2C Bus as Slave on address 9
  Wire.begin(9);
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);

  // Configure the LED for output and sets the intial state to off
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

  attachInterrupt(0, P_event, FALLING);

  engine.init();
  stepper = engine.stepperConnectToPin(stepPinStepper);
  if (stepper)
  {
    stepper->setDirectionPin(dirPinStepper);
    stepper->setEnablePin(enablePinStepper);
    stepper->setAutoEnable(true);

    // If auto enable/disable need delays, just add (one or both):
    // stepper->setDelayToEnable(50);
    // stepper->setDelayToDisable(1000);
    stepper->setSpeedInHz(8000);
    stepper->setAcceleration(1000);
    stepper->move(100000);
  }
}

void loop()
{
  if (recBuffer != 0)
  {
    //Serial.println(recBuffer);
    if (recBuffer == 1)
    {
      digitalWrite(LED_BUILTIN, HIGH);
      recBuffer = 0;
    }
    if (recBuffer == 2)
    {
      digitalWrite(LED_BUILTIN, LOW);
      recBuffer = 0;
    }
    if (recBuffer == 3)
    {
      stepper->setSpeedInHz(8000);
      stepper->setAcceleration(1000);
      stepper->move(100000);
      recBuffer = 0;
    }
    if (recBuffer == 4)
    {
      stepper->setSpeedInHz(8000);
      stepper->setAcceleration(1000);
      stepper->move(-100000);
      recBuffer = 0;
    }
    if (recBuffer == 99)
    {
      recBuffer = 0;
    }
  }
}