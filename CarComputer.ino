/*
 Name:		CarComputer.ino
 Created:	9/9/2016 1:05:35 PM
 Author:	Benjamin
*/

/****************************************************************************************************************************************************************************
** The point of this will be to replace the clock in the WRX which does not work
** this will be broken into sections as sensors are added
** LCD display (  )
** Clock functionality (   )
** Gyro/Accelerometer (   )
** Compass (   )
** Temperature Cabin (   )
** Temperature Engine Compartment (   )
** Temperature Outside (   )
** GPS (  )
** Bluetooth (   )
** Boost Presure (   )
** Humidity (   )
****************************************************************************************************************************************************************************/

// Library Section
#include <Streaming.h>
#include <LiquidCrystal.h>

// initialize the LCD
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);


void setup() 
{
	// Start the LCD
	lcd.begin(16, 1);

	// Start the serial monitor.  This should be commented out in the final code to conserve memory and increase run speed.
}


void loop() {
  
}
