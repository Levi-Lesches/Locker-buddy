#include <LiquidCrystal_I2C.h>

// loop for the classes, days
// leds 
// buttons
// lcd

// LED pins
#define LED1
#define LED2
#define LED3
#define LED4
#define LED5
#define LED6
#define LED7
#define LED8
#define LED9
#define LED10
#define LED11
#define LED12
#define LED13
#define LED14
#define LED15

// #define LCD_SDA
// #define LCD_SCL 

// to pick the class
#define CLASS_BUTTON_LEFT
#define CLASS_BUTTON_RIGHT

// to pick the day
#define DAY_BUTTON_LEFT
#define DAY_BUTTON_RIGHT

LiquidCrystal lcd()

void setup() {
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(LED3, OUTPUT);
	pinMode(LED4, OUTPUT);
	pinMode(LED5, OUTPUT);
	pinMode(LED6, OUTPUT);
	pinMode(LED7, OUTPUT);
	pinMode(LED8, OUTPUT);
	pinMode(LED9, OUTPUT);
	pinMode(LED10, OUTPUT);
	pinMode(LED11, OUTPUT);
	pinMode(LED12, OUTPUT);
	pinMode(LED13, OUTPUT);
	pinMode(LED14, OUTPUT);
	pinMode(LED15, OUTPUT);

	pinMode(CLASS_BUTTON_RIGHT, INPUT);
	pinMode(CLASS_BUTTON_LEFT, INPUT);

	pinMode(DAY_BUTTON_RIGHT, INPUT);
	pinMode(DAY_BUTTON_LEFT, INPUT);
}

void loop() {
	// listen for button presses
	// blink the LEDs
}