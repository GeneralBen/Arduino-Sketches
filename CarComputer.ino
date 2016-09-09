/*
 Name:    CarComputer.ino
 Created: 9/9/2016 1:05:35 PM
 Author:  Benjamin
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
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() 
{
  // Start the LCD
  lcd.begin(16, 2);

  // Start the serial monitor.  This should be commented out in the final code to conserve memory and increase run speed.
  Serial.begin(9600);  
}


void loop() 
{
  testLCD();
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
