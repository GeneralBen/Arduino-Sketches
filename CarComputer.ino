/*
Name:    CarComputer.ino
Created: 9/9/2016 1:05:35 PM
Author:  Benjamin
*/

/****************************************************************************************************************************************************************************
** The point of this will be to replace the clock in the WRX which does not work
** this will be broken into sections as sensors are added
** LCD display ( X )
** Keypad control to change screens (   )
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
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// button designation for LCD Keypad
int keySelection;
#define btnSELECT	1	// 640
#define btnLEFT		2	//	408
#define btnRIGHT		3	// 0
#define btnUP			4	// 99
#define btnDOWN		5	// 255
#define btnNONE		0	// 1023

// Screen navigation
#define MAXSCREENS 2	// update this as screens are added 
int screen;
long unsigned int timer;


void setup()
{
	// Start the LCD
	lcd.begin(16, 2);

	// Start the serial monitor.  This should be commented out in the final code to conserve memory and increase run speed.
	Serial.begin(9600);

	// initialize key to 0
	keySelection = 0;

	// initialize screen variable
	screen = 1;

	timer = millis();
}


void loop()
{
	//testLCD();

	int tempKey = readKeys();

	if (tempKey != keySelection)
	{
		keySelection = tempKey;
		delay(10);
		if (keySelection != 0)
		{
			Serial.println(keySelection);

			if (keySelection == btnLEFT || keySelection == btnRIGHT)
			{
				screenSwitch(keySelection);
			}
		}
	}
	
	Serial << "millis -->  "<< millis() << " ,  timer -->  " << timer << "\n";

	// update screen
	displayScreen();
}

// this will allow user to switch between screens
void screenSwitch(int direction)
{
	// Screens can be added to this
	// ** currently there are only 2 screens **
	// ** update this as screens are added **

	if (direction == btnLEFT)
	{
		if (screen > 1)
		{
			screen--;
		}
		else
		{
			screen = MAXSCREENS;
		}
	}

	if (direction == btnRIGHT)
	{
		if (screen < MAXSCREENS)
		{
			screen++;
		}
		else
		{
			screen = 1;
		}
	}

	lcdLineClear(3);

	switch (screen)
	{
		// time
		case 1:
			lcd.setCursor(0, 0);
			lcd.print("Time");
			break;

		// about
		case 2:
			lcd.setCursor(0, 0);
			lcd.print("Ben made this");
			lcd.setCursor(0, 1);
			lcd.print("to be continued");
			break;

		default:
			break;
	}
}

void displayScreen()
{
	// Screens can be added to this
	// ** currently there are only 2 screens **
	// ** update this as screens are added **
	switch (screen)
	{
		// welcome screen -- time
	case 1:
		//if ()
		
		if ((timer + 1000) < millis())
		{
			lcdLineClear(2);
			lcd.setCursor(0, 1);
			timer = millis();
			
			lcd << "time " << timer;
			Serial << "time " << timer << endl;
		}
		break;
	default:
		break;
	}
}

int readKeys()
{
	int keyOmhs = analogRead(0);

	// this can be used to find button ohms
	//Serial.println(keyOmhs);

	if (keyOmhs < 10)
	{
		return btnRIGHT;		// return 5
	}

	else if (keyOmhs < 109 && keyOmhs > 89)
	{
		return btnUP;		// return 3	
	}

	else if (keyOmhs < 265 && keyOmhs > 245)
	{
		return btnDOWN;				// return 4
	}

	else if (keyOmhs < 418 && keyOmhs > 398)
	{
		return btnLEFT;			// return 2
	}

	else if (keyOmhs < 650 && keyOmhs > 630)
	{
		return btnSELECT;		// return 1
	}

	else 
	{
		return btnNONE;		// return 0
	}
}

void testLCD()
{
	int line = 1;

	// test the lcd by writing charicters and clearing them
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			lcd.setCursor(0, j);
			for (int k = 1; k <= 16; k++)
			{
				lcd.print(i);
			}
		}

		delay(500);

		lcdLineClear(line++);

		if (line == 4)
		{
			line = 1;
		}

		delay(500);

	}
}

// This function clears the lcd when called
void lcdLineClear(int line)
{
	switch (line)
	{

		// clear the first line
	case 1:
		lcd.setCursor(0, 0);
		lcd.print("                ");
		break;

		// clear second line
	case 2:
		lcd.setCursor(0, 1);
		lcd.print("                ");
		break;

		//clear both lines by calling self
	case 3:
		lcdLineClear(1);
		lcdLineClear(2);
		break;

	default:
		break;
	}
}
