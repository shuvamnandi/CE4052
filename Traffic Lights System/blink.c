#include <wiringPi.h>
#include <softTone.h>
int main(void)
{
	wiringPiSetup();
	softToneCreate(1);
	pinMode(0, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(7, OUTPUT);
        for(;;)
	{
		softToneWrite(1,100);
		//digitalWrite(0,HIGH); delay(500);
		//digitalWrite(0, LOW); delay(500);
		//digitalWrite(2,HIGH); delay(500);
		//digitalWrite(2, LOW); delay(500);
		//digitalWrite(7,HIGH); delay(500);
		//digitalWrite(7, LOW); delay(500);

	}
	return 0;
}
