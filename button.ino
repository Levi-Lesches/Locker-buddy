#include <Keypad.h>

#define rows 1
#define cols 4
#define LED 13

const char keys [rows] [cols] = {
  {'A', 'B', 'C', 'D'}
};
const byte rowPins[rows] = {2};
const byte colPins[cols] = {3, 4, 5, 6};
Keypad keypad = Keypad (makeKeymap (keys), rowPins, colPins, rows, cols);

void setup() {
//  pinMode (BUTTON, INPUT);
  pinMode (LED, OUTPUT);
  keypad.addEventListener (handle);
}

void handle(KeypadEvent key) {
  KeyState state = keypad.getState();
  switch (state) {
    case PRESSED: 
        digitalWrite (LED, HIGH);
        delay (1000);
        break;      
    case RELEASED: 
      digitalWrite (LED, LOW);
      break;
  }
}

void loop() {
  char input = keypad.getKey();  
}
