#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>

int alarm(double lng, double lat){

	FILE *alm;
  	wiringPiSetup();
  	const int INPUT_PIN = 5;
	char buf1[1000];
  	pinMode(5, INPUT);
    	
	//detects high voltage from button input at 'GPIO 5'
        if(digitalRead(5) == HIGH)
	{
	//creates a text and audio log of the emergency
	alm = fopen("/home/pi/Desktop/Shared/emergency_log.txt","a");
	if(alm == NULL){
		printf("Err");
		exit(0);
	}
	fprintf(alm,"\n-------\nK191110 POSTED AN EMERGENCY\nLONGITUDE:%f LATITUDE: %f\nAN AUDIO LOG HAS BEEN SAVED", lng, lat);
	fclose(alm);

	//changes working directory to the shared folder and invokes recording utility 'arecord'
	system("cd /home/pi/Desktop/Shared/ && arecord -D plughw:1,0 -d 20 -f cd -r 44100 -t wav `date +%Y.%m.%d.%H:%M`.wav");

	//parses the lng and lat into system which invokes a chromium with a Google Maps url to display the GPS location posted
	snprintf(buf1,sizeof(buf1),"firefox http://www.google.com/maps/place/%f,%f", lng, lat);
	system(buf1);
  }

return 0;
}
