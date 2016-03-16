// standard arduino library to access the lcd screen
#include <LiquidCrystal.h>

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int lcd_key = 0;
int adc_key_in = 0;

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

void setup()
{
	// begin serial communication at a baud rate of 9600
	Serial.begin(9600);
	
	// initialize the lcd with a two rows and 16 characters per row
	lcd.begin(16, 2);
	
	// ensure the screen is clear -- i have found this to be the most effect method of clearing the screen
	lcd.setCursor(0, 0);
	lcd.print("                ");
	lcd.setCursor(0, 1);
	lcd.print("                ");
}

void welcome()
{
	lcd.setCursor(0, 0);
	lcd.print("*** Welcome ***");
	lcd.setCursor(0, 1);
	
	switch read_LCD_buttons()
	{
		case 0:
			lcd.setCursor(0, 1);
			lcd.print("                ");
			lcd.setCursor(0, 1);
			
			lcd.print("right");
			break;
		case 1:
			lcd.setCursor(0, 1);
			lcd.print("                ");
			lcd.setCursor(0, 1);
			
			lcd.print("up");
			break;
		case 2:
			lcd.setCursor(0, 1);
			lcd.print("                ");
			lcd.setCursor(0, 1);
			
			lcd.print("down");
			break;
		case 3:
			lcd.setCursor(0, 1);
			lcd.print("                ");
			lcd.setCursor(0, 1);
			
			lcd.print("left");
			break;
		case 4:
			lcd.setCursor(0, 1);
			lcd.print("                ");
			lcd.setCursor(0, 1);
			
			lcd.print("select");
			break;
		case 5:  // 
			// print nothing -- leave old value
			break;
			
		default:
			// again do nothing
			break;
			
	}
}

// this was taken from the internet with a little modification to match the lcd shield
// read the buttons
int read_LCD_buttons()
{
	adc_key_in = analogRead(0);      // read the value from the sensor 
	if (adc_key_in > 650) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result

	// use +- 10 to get accurate button presses

	if (adc_key_in < 10)   return btnRIGHT;    // 0
	if (adc_key_in >= 90 && adc_key_in <= 110)  return btnUP;  // 99
	if (adc_key_in >= 245 && adc_key_in <= 265)  return btnDOWN;  // 255
	if (adc_key_in >= 308 && adc_key_in <= 418)  return btnLEFT;  // 408
	if (adc_key_in >= 630 && adc_key_in <= 650)  return btnSELECT;   // 640

	return btnNONE;  // when all others fail, return this...
}

