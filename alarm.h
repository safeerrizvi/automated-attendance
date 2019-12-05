#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>

int alarm(float lng, float lat) {

	FILE *alm;
  	wiringPiSetup();
  	const int INPUT_PIN = 5;
	char buf1[100];
  	pinMode(5, INPUT);
    	
	//detects high voltage from button input at 'GPIO 5'
        if(digitalRead(5) == HIGH)
	{
	//creates a log 
	alm = fopen("/home/pi/Desktop/Shared/emergency log.txt","a");
	fprintf(alm,"\n-------\n19K1110 HAD POSTED AN EMERGENCY AT LONG: %f LAT: %f\n\nA 20 SECOND AUDIO LOG IS BEING SAVED IN THIS DIRECTORY", lng, lat);
	fclose(alm);

	//changes working directory to the shared folder and invokes recording utility 'arecord'
	system("cd /home/pi/Desktop/Shared/ && arecord -D plughw:1,0 -d 20 -f cd -r 44100 -t wav `date +%Y.%m.%d.%H:%M`.wav");

	//parses the lng and lat into system which invokes a Google Maps url that displays the GPS location
	snprintf(buf1,sizeof(buf1),"chromium-browser http://www.google.com/maps/place/%f,%f", lng, lat);
	system(buf1);
   	}
return 0;
}
