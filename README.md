# Locker buddy

An Arduino-powered device to help dispense the correct materials from your locker depending on what class you have now.

# Wiring: 

Here is a lookup chart for how each pin is referred to in the code: 

* For the LCD: 
	* From the left: 
		* 1: GND
		* 2: VCC
		* 3: Potentiometer (resistor support TBD)
		* 4: LCD_1
		* 5: GND
		* 6: LCD_2
	* From the right: 
		* 1: GND
		* 2: VCC
		* 3: LCD_3
		* 4: LCD_4
		* 5: LCD_5
		* 6: LCD_6
* For the Button panel: 
	* SWITCH1: SWITCH
	* SWITCH-GND-1: SWITCH_GND_1
	* SWITCH-GND-2: SWITCH_GND_2
	* SWITCH-GND-3: SWITCH_GND_3
	* SWITCH-GND-4: SWITCH_GND_4
* For the LEDs: 
	Every entry in the `ledPins` list should correspond to the class of the same index in the `uniquesClasses` list.