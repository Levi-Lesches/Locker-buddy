#include <LiquidCrystal_I2C.h>

// LED pins
#define LED1 2
#define LED2 3
#define LED3 4
#define LED4 5
#define LED5 6
#define LED6 7
#define LED7 8 
#define LED8 9 
// #define LED9 10
// #define LED10 11
// #define LED11 12
// #define LED12 13
// #define LED13 14
// #define LED14
// #define LED15

// #define LCD_SDA
// #define LCD_SCL 

// to pick the class
#define CLASS_BUTTON_LEFT 10
#define CLASS_BUTTON_RIGHT 11

// to pick the day
#define DAY_BUTTON_LEFT 12
#define DAY_BUTTON_RIGHT 13

// define constant numbers (Save memory!)
#define NUMBER_OF_CLASSES_IN_DAY 11
#define NUMBER_OF_DAYS

LiquidCrystal_I2C lcd(1, 2, 3);

int buttonState = 0;
int lastButtonState = 0;
int classIndex = 0;

const String classes[2] = {"English", "Spanish"}  // change
const int LEDs[2] = {}

void switchClass(int increment) {
	classIndex += increment;
	if (classIndex < 0) classIndex = NUMBER_OF_CLASSES_IN_DAY;
	else if (classIndex > NUMBER_OF_CLASSES_IN_DAY) classIndex = 0;
}

void switchDay(int increment) {
	dayIndex += increment;
	if (dayIndex < 0) dayIndex = NUMBER_OF_DAYS;
	else if (dayIndex > NUMBER_OF_DAYS) dayIndex = 0;
}

void setup() {
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(LED3, OUTPUT);
	pinMode(LED4, OUTPUT);
	pinMode(LED5, OUTPUT);
	pinMode(LED6, OUTPUT);
	pinMode(LED7, OUTPUT);
	pinMode(LED8, OUTPUT);
	// pinMode(LED9, OUTPUT);
	// pinMode(LED10, OUTPUT);
	// pinMode(LED11, OUTPUT);
	// pinMode(LED12, OUTPUT);
	// pinMode(LED13, OUTPUT);
	// pinMode(LED14, OUTPUT);
	// pinMode(LED15, OUTPUT);

	pinMode(CLASS_BUTTON_RIGHT, INPUT);
	pinMode(CLASS_BUTTON_LEFT, INPUT);

	pinMode(DAY_BUTTON_RIGHT, INPUT);
	pinMode(DAY_BUTTON_LEFT, INPUT);
}

void loop() {
	// listen for button presses
	// blink the LEDs

	if (digitalRead(CLASS_BUTTON_LEFT) == HIGH) switchClass(-1);
	if (digitalRead(CLASS_BUTTON_RIGHT) == HIGH) switchClass (1);
	if (digitalRead(DAY_BUTTON_LEFT) == HIGH) switchDay (-1);
	if (digitalRead(DAY_BUTTON_RIGHT) == HIGH) switchDay (1);
}

// class Schedule {
// 	public;

// 	Day days[NUMBER_OF_DAYS];

// 	Schedule (Day days_[NUMBER_OF_DAYS]) {
// 		days = days_;
// 	}
// }