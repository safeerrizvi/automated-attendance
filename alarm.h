
#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
int alarm(float lng, float lat) {

  FILE *alm;
  wiringPiSetup();
  const int INPUT_PIN = 5;
  char buf1[100];
  pinMode(5, INPUT);
    // Detects High Voltage on GPIO5, creates a txt file with  invokes shell
    // command 'arecord'
        if(digitalRead(5) == HIGH)
      {
      // if statement to check weather the file contents are not null run
      // everything below USE r+:
      
        //alm = fopen("/home/pi/Desktop/Shared/emergency log.txt", "w+");
        //if (alm == NULL) {
        //printf("error opening file\n");
        //return 1;
        //}
         // fprintf(alm, "At long: %f lat: %f\nThere was an emergency was detected\nAn audio file is being saved has been", lng, lat);
          //fclose(alm);
          //system("cd /home/pi/Desktop/Shared && arecord -D plughw:1,0 -d 10 | `date +%Y%m%d%H%M`.wav");

      // else if file read is not null file
      //if (alm != NULL){
          alm = fopen("/home/pi/Desktop/Shared/emergency log.txt","a");
          fprintf(alm,"\n-------\nAt long: %f lat: %f\nThere was an emergency was detected\nAn audio file has been saved", lng, lat);
      fclose(alm);
      system("cd /home/pi/Desktop/Shared/ && arecord -D plughw:1,0 -d 10 -f cd -r 44100 -t wav `date +%Y.%m.%d.%H:%M`.wav");
      snprintf(buf1,sizeof(buf1),"chromium-browser http://www.google.com/maps/place/%f,%f", lng, lat);
	system(buf1);
    }
  return 0;
}
