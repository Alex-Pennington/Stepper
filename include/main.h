//As in StepperDemo for Motor 1 on AVR
#define dirPinStepper    6
#define enablePinStepper 7
#define stepPinStepper   9  // OC1A in case of AVR
#define speedometerPin 3

#include <Wire.h>
int recBuffer =0;

#include "FastAccelStepper.h"
#include "AVRStepperPins.h"

FastAccelStepperEngine engine = FastAccelStepperEngine();
FastAccelStepper *stepper = NULL;

int long P_counter = 0;

#include <SerialCommands.h>
char serial_command_buffer_[32];
SerialCommands serial_commands_(&Serial, serial_command_buffer_, sizeof(serial_command_buffer_), "\r\n", " ");

//This is the default handler, and gets called when no other command matches. 
// Note: It does not get called for one_key commands that do not match
void cmd_unrecognized(SerialCommands* sender, const char* cmd)
{
  sender->GetSerial()->print("Unrecognized command [");
  sender->GetSerial()->print(cmd);
  sender->GetSerial()->println("]");
}

//called for ON command, or one_key '1' command
void cmd_led_on(SerialCommands* sender)
{
  digitalWrite(LED_BUILTIN, HIGH);  
  sender->GetSerial()->println("Led is on");
}

void cmd_led_off(SerialCommands* sender)
{
  digitalWrite(LED_BUILTIN, LOW);  
  sender->GetSerial()->println("Led is off");
}

void cmd_stepper_ccw(SerialCommands* sender) {
}

void cmd_stepper_cw(SerialCommands* sender) {
 }

void cmd_stepper_stop(SerialCommands* sender) {
}

void cmd_home(SerialCommands* sender) {
  }

void cmd_print_position(SerialCommands* sender) {
}

//Note: Commands are case sensitive
SerialCommand cmd_led_on_("on", cmd_led_on);
SerialCommand cmd_led_off_("off", cmd_led_off);
SerialCommand cmd_stepper_ccw_("ccw", cmd_stepper_ccw);
SerialCommand cmd_stepper_cw_("cw", cmd_stepper_cw);
SerialCommand cmd_stepper_stop_("stop", cmd_stepper_stop);
SerialCommand cmd_home_("home", cmd_home);

// Add one_key commands to call the same on and off function but by simply
// pressing '1' or '0' without needing a terminating key stroke.
// One_key commands are ONLY tested when they are the first key pressed on
// startup, or the first key after a previous terminating keystroke.
SerialCommand cmd_1_("1", cmd_stepper_ccw, true);
SerialCommand cmd_0_("0", cmd_stepper_cw, true);
SerialCommand cmd_s_("s", cmd_stepper_stop, true);
SerialCommand cmd_h_("h", cmd_home, true);
SerialCommand cmd_p_("p", cmd_print_position, true);

  void receiveEvent(int bytes) {
    recBuffer = Wire.read();    // read one character from the I2C
  }
