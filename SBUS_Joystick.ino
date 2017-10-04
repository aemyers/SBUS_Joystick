#include <SBUS.h>

#define SBUS_MIN 172 // minimum value SBUS input
#define SBUS_MAX 1811 // maximum value SBUS input
#define ANALOG_MIN 0 // minimum value analog joystick output
#define ANALOG_MAX 1023 // maximum value analog joystick output
#define SBUS_ON 1600; // minimum value SBUS input to determine if button should be considered pressed

SBUS sbus(Serial1);

uint16_t channels[16];
uint8_t failSafe;
uint16_t lostFrames = 0;

void setup() {
  sbus.begin();
}

void loop() {
  if (!sbus.read(&channels[0], &failSafe, &lostFrames)) return;
 
  Joystick.X(mapSbusToAnalog(channels[0]));
  Joystick.Y(mapSbusToAnalog(channels[1]));
  Joystick.Z(mapSbusToAnalog(channels[2]));
  Joystick.Zrotate(mapSbusToAnalog(channels[3]));
  Joystick.sliderLeft(mapSbusToAnalog(channels[4]));
  Joystick.sliderRight(mapSbusToAnalog(channels[5]));

  Joystick.button(1, mapSbusToDigital(channels[6]));
  Joystick.button(2, mapSbusToDigital(channels[7]));
  Joystick.button(3, mapSbusToDigital(channels[8]));
//  Joystick.button(4, mapSbusToDigital(channels[9]));
//  Joystick.button(5, mapSbusToDigital(channels[10]));
//  Joystick.button(6, mapSbusToDigital(channels[11]));
//  Joystick.button(7, mapSbusToDigital(channels[12]));
//  Joystick.button(8, mapSbusToDigital(channels[13]));
//  Joystick.button(9, mapSbusToDigital(channels[14]));
//  Joystick.button(10, mapSbusToDigital(channels[15]));
}

long mapSbusToAnalog(uint16_t& value) {
  return (value - SBUS_MIN) * (ANALOG_MAX - ANALOG_MIN + 1) / (SBUS_MAX - SBUS_MIN + 1) + ANALOG_MIN;
}

boolean mapSbusToDigital(uint16_t& value) {
  return value >= SBUS_ON;
}
