#include <wiringPi.h>
#include <softTone.h>
int main(void)
{
	int i;
	wiringPiSetup();
	softToneCreate(1);
	pinMode(0, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(14,INPUT);
        for(;;)
	{
		if(digitalRead(14) == HIGH)
		{
			digitalWrite(0, HIGH);
			delay(500);
		}
		else {
			softToneWrite(1, 0);
		}
		delay(100);
		//digitalWrite(0,HIGH); delay(500);
		//digitalWrite(0, LOW); delay(500);
		//digitalWrite(2,HIGH); delay(500);
		//digitalWrite(2, LOW); delay(500);
		//digitalWrite(7,HIGH); delay(500);
		//digitalWrite(7, LOW); delay(500);

	}
	//softToneWrite(1, 0);
	return 0;
}
