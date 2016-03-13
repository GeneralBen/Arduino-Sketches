/*
Name:		servoDeg.ino
Created:	2/26/2016 6:15:43 PM
Author:	Benjamin
*/

// the setup function runs once when you press reset or power the board
#include <Servo.h>
#include <Streaming.h>

// servos are hightec HS-55
#define SERVO1_PWM 10
#define SERVO2_PWM 9

// laser is a KY-008 
#define LASER_PIN 52

Servo servo1;
Servo servo2;

int posServ1;
int posServ2;

String readSerialString = "";
char charFromSerial;
double serialX, serialY;

void setup()
{
	Serial.begin(9600);
	servo1.attach(SERVO1_PWM);
	servo2.attach(SERVO2_PWM);
	pinMode(LASER_PIN, OUTPUT);

	posServ1 = 90;
	posServ2 = 90;

	servo1.write(posServ1);
	servo2.write(posServ2);
	delay(1000);

	digitalWrite(LASER_PIN, HIGH);
	//testMode();
}

// the loop function runs over and over again until power down or reset
void loop()
{
	
	//drawSpiralCircle();
	//drawSpiralBox();
	readSerial();
}

void readSerial()
{
	readSerialString = "";
	//Serial.flush();
	while (Serial.available())
	{
		charFromSerial = Serial.read();
		readSerialString.concat(charFromSerial);
		if (readSerialString != "")
		{
			// parser calls draw function
			parser(readSerialString);
		}

	}

	drawPoint(serialX, serialY);
}

void parser(String word)
{
	// we are looking to convert 10,9 --> x = 10, y = 9 on seperate lines

	// this should only look for a given structure
	// x value is the number until the comma xxx,
	// y value is the number after the comma ,yyy
	// we will parse with that format

	String stringX = "";
	String stringY = "";
	int commaIndex;


	if (word != "")
	{
		// find the index of the comma
		for (int j = 0; j < word.length(); j++)
		{
			if (word.charAt(j) == ',')
			{
				commaIndex = j;
				j = word.length();
			}
		}

		for (int k = 0; k < commaIndex; k++)
		{
			stringX.concat(word.charAt(k));
		}

		for (int l = commaIndex + 1; l < word.length(); l++)
		{
			stringY.concat(word.charAt(l));
		}

		serialX = (double)stringX.toFloat() / 100;
		serialY = (double)stringY.toFloat() / 100;
	}
}


void drawPoint(double x, double y)
{
	// this uses trig to draw a point
	// uses dynamic distance

	// bounds are (-10, -10) , (10, 10) in inches

	// distance -- using a sharp 2Y0A21 F 5Y sensor
	double d = (((6787.0 / (analogRead(1) - 3.0)) - 4.0)*0.39370079) - .5;
	double hypotX = sqrt(pow(abs(x), 2) + pow(d, 2));
	double hypotY = sqrt(pow(abs(y), 2) + pow(d, 2));

	int posAngleX = round(degrees(asin(x / hypotX)));
	int posAngleY = round(degrees(asin(y / hypotY)));

	int drawAngleX = 90;
	int drawAngleY = 90;

	drawAngleX -= posAngleX;
	drawAngleY -= posAngleY;
	
	servo1.write(drawAngleX);
	servo2.write(drawAngleY);

	//Serial << "drawAngleX = " << drawAngleX << ", drawAngleY = " << drawAngleY << endl;
	//Serial << "posAngleX = " << posAngleX << ", posAngleY = " << posAngleY << endl;
	delay(100);
}

void testMode()
{
	// this will give 0, 90, 180 for each servo togethor
	for (int i = -90; i < 90; i += 90)
	{
		posServ1 = i;
		posServ2 = i;
		servo1.write(posServ1);
		servo2.write(posServ2);
		delay(1000);

	}

	// this will give 0, 90, 180 for each servo seperatly
	for (int j = -90; j < 90; j += 90)
	{
		posServ1 = j;
		servo1.write(posServ1);
		servo2.write(posServ2);
		delay(1000);

	}

	posServ1 = 0;
	servo1.write(posServ1);
	servo2.write(posServ2);

	// this will give 0, 90, 180 for each servo seperatly
	for (int k = -90; k < 0; k += 90)
	{
		posServ2 = k;

		servo1.write(posServ1);
		servo2.write(posServ2);
		delay(1000);
	}

	posServ2 = 0;
	servo1.write(posServ1);
	servo2.write(posServ2);

	delay(1000);

	drawPoint(0.0, 0.0);
	delay(1000);

	drawPoint(-10.0, -10.0);
	delay(1000);

	drawPoint(10.0, -10.0);
	delay(1000);

	drawPoint(10.0, 10.0);
	delay(1000);

	drawPoint(-10.0, 10.0);
	delay(1000);

	drawPoint(0.0, 0.0);
	delay(1000);

	drawPoint(-10.0, -10.0);
	delay(1000);

	drawPoint(10.0, -10.0);
	delay(1000);

	drawPoint(10.0, 10.0);
	delay(1000);

	drawPoint(-10.0, 10.0);
	delay(1000);
}

// draws a box and gets smaller.  goes in a clockwise motion
void drawSpiralBox()
{
	for (int i = 10; i > 0; i--)
	{

		int xNow = -i;
		int yNow = -i;
		drawPoint(xNow, yNow);
		//Serial << "xNow = " << xNow << ", yNow = " << yNow << endl;
		//delay(50);

		// up count
		do
		{
			xNow++;
			drawPoint((double)xNow, (double)yNow);
			//Serial << "xNow = " << xNow << ", yNow = " << yNow << endl;
			//delay(50);
		} while (xNow < i);

		do
		{
			yNow++;
			drawPoint((double)xNow, (double)yNow);
			//Serial << "xNow = " << xNow << ", yNow = " << yNow << endl;
			//delay(50);
		} while (yNow < i);



		// down count

		while (xNow > -i)
		{
			xNow--;
			drawPoint((double)xNow, (double)yNow);
			//Serial << "xNow = " << xNow << ", yNow = " << yNow << endl;
			//delay(50);
		}

		while (yNow > -i)
		{
			yNow--;
			drawPoint((double)xNow, (double)yNow);
			//Serial << "xNow = " << xNow << ", yNow = " << yNow << endl;
			//delay(50);
		}

	}
}

// draws a spiral going to the center clockwise 
void drawSpiralCircle()
{
	double radius = 10;
	double xNow = 0;
	double yNow = 0;
	double radAngle = 0.0;

	// update radius per rev
	for (int i = 10; i > 0; i--)
	{
		radius = i;

		// update angle per rev
		for (int j = 0; j < 360; j += 2)
		{
			radAngle = radians((double)j);
			xNow = cos(radAngle) * radius;
			yNow = sin(radAngle) * radius;
			drawPoint((double)xNow, (double)yNow);
			radius -= 1 / 180;
			//delay(15);
		}
		
	}
}
