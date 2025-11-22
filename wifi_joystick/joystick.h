// Pinout
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

// Bit-Positions 
#define BIT_UP     0
#define BIT_DOWN   1
#define BIT_LEFT   2
#define BIT_RIGHT  3
#define BIT_BUTTON 4

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

int JoystickA_read(){
  byte joystickState = 0;
  
  // Joystick-Zustände einlesen und ins Byte schreiben
  if (digitalRead(PIN_A_UP))     joystickState |= (1 << BIT_UP);
  if (digitalRead(PIN_A_DOWN))   joystickState |= (1 << BIT_DOWN);
  if (digitalRead(PIN_A_LEFT))   joystickState |= (1 << BIT_LEFT);
  if (digitalRead(PIN_A_RIGHT))  joystickState |= (1 << BIT_RIGHT);
  if (digitalRead(PIN_A_BUTTON)) joystickState |= (1 << BIT_BUTTON);

  return joystickState;

}

int JoystickB_read(){
  byte joystickState = 0;
  
  // Joystick-Zustände einlesen und ins Byte schreiben
  if (digitalRead(PIN_B_UP))     joystickState |= (1 << BIT_UP);
  if (digitalRead(PIN_B_DOWN))   joystickState |= (1 << BIT_DOWN);
  if (digitalRead(PIN_B_LEFT))   joystickState |= (1 << BIT_LEFT);
  if (digitalRead(PIN_B_RIGHT))  joystickState |= (1 << BIT_RIGHT);
  if (digitalRead(PIN_B_BUTTON)) joystickState |= (1 << BIT_BUTTON);
  
  return joystickState;

}

// int joystick_read(){
//   byte joystickState = 0;
  
//   // Joystick-Zustände einlesen und ins Byte schreiben
//   if (digitalRead(PIN_UP))     joystickState |= (1 << BIT_UP);
//   if (digitalRead(PIN_DOWN))   joystickState |= (1 << BIT_DOWN);
//   if (digitalRead(PIN_LEFT))   joystickState |= (1 << BIT_LEFT);
//   if (digitalRead(PIN_RIGHT))  joystickState |= (1 << BIT_RIGHT);
//   if (digitalRead(PIN_BUTTON)) joystickState |= (1 << BIT_BUTTON);
  
//   // display the binary data on the serial monitor
//   Serial.print("0b");
//   for (int i = 7; i >= 0; i--) {
//     Serial.print((joystickState >> i) & 1);
//   }
//   Serial.println();

//   return joystickState;
//   //delay(100); // Kurze Pause zwischen den Messungen
// }