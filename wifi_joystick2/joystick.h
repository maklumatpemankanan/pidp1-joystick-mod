// Pinout - do not change anything in the config of the pinout
// Joystick A
#define PIN_A_UP     18 //purple
#define PIN_A_DOWN   5  //grey
#define PIN_A_LEFT   17 //white
#define PIN_A_RIGHT  16 //black
#define PIN_A_BUTTON 19 //blue
// Joystick B 
#define PIN_B_UP     25 //purple 
#define PIN_B_DOWN   26 //grey
#define PIN_B_LEFT   27 //white     
#define PIN_B_RIGHT  14 //black
#define PIN_B_BUTTON 33 //blue

// Bit-Positions in the IO-Register
// postition 0 to 17 is possible
#define JOYA_BIT_UP     2
#define JOYA_BIT_DOWN   4
#define JOYA_BIT_LEFT   0
#define JOYA_BIT_RIGHT  1
#define JOYA_BIT_BUTTON 3

#define JOYB_BIT_UP     16
#define JOYB_BIT_DOWN   13
#define JOYB_BIT_LEFT   14
#define JOYB_BIT_RIGHT  15
#define JOYB_BIT_BUTTON 17


void joystick_init(){

  pinMode(PIN_A_UP, INPUT_PULLDOWN);
  pinMode(PIN_A_DOWN, INPUT_PULLDOWN);
  pinMode(PIN_A_LEFT, INPUT_PULLDOWN);
  pinMode(PIN_A_RIGHT, INPUT_PULLDOWN);
  pinMode(PIN_A_BUTTON, INPUT_PULLDOWN);
  Serial.println("Joystick A Ready");

  pinMode(PIN_B_UP, INPUT_PULLDOWN);
  pinMode(PIN_B_DOWN, INPUT_PULLDOWN);
  pinMode(PIN_B_LEFT, INPUT_PULLDOWN);
  pinMode(PIN_B_RIGHT, INPUT_PULLDOWN);
  pinMode(PIN_B_BUTTON, INPUT_PULLDOWN);
  Serial.println("Joystick A Ready");

}

uint32_t Joysticks_read(){
  //read status of both joysticks and collect a 18 bit value for returning in the io-register
  uint32_t joystickState = 0;
  //joystick a
  if (digitalRead(PIN_A_UP))     joystickState |= (1 << JOYA_BIT_UP);
  if (digitalRead(PIN_A_DOWN))   joystickState |= (1 << JOYA_BIT_DOWN);
  if (digitalRead(PIN_A_LEFT))   joystickState |= (1 << JOYA_BIT_LEFT);
  if (digitalRead(PIN_A_RIGHT))  joystickState |= (1 << JOYA_BIT_RIGHT);
  if (digitalRead(PIN_A_BUTTON)) joystickState |= (1 << JOYA_BIT_BUTTON);
  //joystick b
  if (digitalRead(PIN_B_UP))     joystickState |= (1 << JOYB_BIT_UP);
  if (digitalRead(PIN_B_DOWN))   joystickState |= (1 << JOYB_BIT_DOWN);
  if (digitalRead(PIN_B_LEFT))   joystickState |= (1 << JOYB_BIT_LEFT);
  if (digitalRead(PIN_B_RIGHT))  joystickState |= (1 << JOYB_BIT_RIGHT);
  if (digitalRead(PIN_B_BUTTON)) joystickState |= (1 << JOYB_BIT_BUTTON);
  //return the value
  return joystickState;

}

