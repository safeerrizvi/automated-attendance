
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "alarm.h"

void parser(char buf[],double *lng,double *lat){
  
    char *pend;
    int j = 0;
    char *p = strtok (buf, ":, ");
    char *array[100];
    
    while (p != NULL)
    {
        array[j++] = p;
        p = strtok (NULL, ":, ");
    }
    
    printf("%s\n", array[4]);
    printf("%s\n", array[2]);
    //double f1 = strtod(array[2], &pend);
    //double f2 = strtod(array[4], &pend);
    *lng=24.856911;
    *lat=67.264200;
    //printf("%Lf",f1);
    //printf("\n%.15f\n%.15f", f1, f2);
    //printf("\nlongitude: %.15f",*lng);
    //printf("\nlatitude: %.15f",*lat);
}


void att(char num,struct tm *timeinfo, const char *a) {

  char path[100] = "/home/pi/Public/";
   strcat(path, a);
  FILE *ftp;
  ftp = fopen(path, "a");
  fprintf(ftp, "\n 19K-1110 Maaz Asim %c    %s\n", num, asctime(timeinfo));
}

int i;
int main() {
  //Intializing variables
  char num = 'A';
	double latitude = 67.264200;
	double longitude = 24.856911;

  char buffer[32];
  struct tm *ts;
  int serial_port;
  char dat, buff[100], GGA_code[3];
  unsigned char IsitGGAstring = 0;
  unsigned char GGA_index = 0;
  unsigned char is_GGA_received_completely = 0;
  size_t last;
  time_t timestamp = time(NULL);

  ts = localtime(&timestamp);
  last = strftime(buffer, 32, "%A", ts);
  buffer[last] = '\0';

  printf("%s\n", buffer);
  time_t rawtime;
  struct tm *timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);
  printf("Current local time and date: %s", asctime(timeinfo));
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  printf("now:%d:%d\n", tm.tm_hour, tm.tm_min);
  
  
  
  //Retrieves GPS data from NEO6M serial ports (TX & RX)
  if ((serial_port = serialOpen("/dev/ttyAMA0", 9600)) < 0) /* open serial port */
  {
    fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
    return 1;
  }

  if (wiringPiSetup() == -1) /* initializes wiringPi setup */
  {
    fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
    return 1;
  }

  while(1){
  
  if (serialDataAvail(serial_port)){ /* check for any data available on serial port */
        dat = serialGetchar(serial_port); /* receive character serially */
  
        if (dat == '$') {
        IsitGGAstring = 0;
        GGA_index = 0;
        } 
  
        else if (IsitGGAstring == 1) {
        buff[GGA_index++] = dat;
        if (dat == '\r')
          is_GGA_received_completely = 1;
        } 
  
        else if (GGA_code[0] == 'G' && GGA_code[1] == 'G' && GGA_code[2] == 'A'){
        IsitGGAstring = 1;
        GGA_code[0] = 0;
        GGA_code[0] = 0;
        GGA_code[0] = 0;
        } 
  
        else{
        GGA_code[0] = GGA_code[1];
        GGA_code[1] = GGA_code[2];
        GGA_code[2] = dat;
        }
    }
    
    if (is_GGA_received_completely == 1) {
      printf("GGA: %s", buff);
      is_GGA_received_completely = 0;
      //callinf parsing function.
      parser(buff,&longitude,&latitude);
    }
    
    
    
    
    
    
    
    
    
    
    
    int i = strcmp(buffer, "Thursday");
    if (i == 0)

      num = 'A';
      
    if (longitude < 24.856910 && longitude> 24.856838 && latitude< 67.264519 && latitude> 67.264211 && tm.tm_hour == 8 && tm.tm_min >= 00 &&
        tm.tm_min <= 15) 
      {
        num = 'P';

        att(num,timeinfo,"ICT.txt");

      }

      num = 'A';
      if (longitude < 24.856910 && longitude> 24.856838 && latitude< 67.264519 && latitude> 67.264211 && tm.tm_hour == 12 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) 
          {
        num ='p';
        att(num,timeinfo,"ENG.txt");
         }
      

      num = 'A';
      if (longitude < 24.856910 && longitude> 24.856838 && latitude< 67.264519 && latitude> 67.264211 && tm.tm_hour == 13 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) 
        {
          num = 'P';

          att(num,timeinfo,"CALC.txt");
          }
      

      num = 'A';
      if (longitude < 24.856910 && longitude> 24.856838 && latitude< 67.264519 && latitude> 67.264211 && tm.tm_hour == 15 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        
          num = 'P';

          att(num,timeinfo,"ENG.txt");
          }
      

      i = strcmp(buffer, "Tuesday");
      if (i == 0)

        num = 'A';
      if (longitude < 24.856910 && longitude> 24.856838 && latitude< 67.264519 && latitude> 67.264211 && tm.tm_hour == 9 &&
          tm.tm_min >= 00 && tm.tm_min <= 00) {
        
        att(num,timeinfo,"PF.txt");
           
      }

      num = 'A';
      if (longitude < 24.856910 && longitude> 24.856838 && latitude< 67.264519 && latitude> 67.264211 && tm.tm_hour == 10 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        
          num = 'P';

          att(num,timeinfo,"AP.txt");
      }

      num = 'A';
      if (longitude < 24.856910 && longitude> 24.856838 && latitude< 67.264519 && latitude> 67.264211 && tm.tm_hour == 12 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) 
        {
          num = 'P';

          att(num,timeinfo,"ENG.txt");
          }

      num = 'A';
      if (longitude < 24.856910 && longitude> 24.856838 && latitude< 67.264519 && latitude> 67.264211 && tm.tm_hour == 13 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
    
          num = 'P';

          att(num,timeinfo,"PST.txt");
          }
      

      num = 'A';
      if (longitude < 24.856910 && longitude> 24.856838 && latitude< 67.264519 && latitude> 67.264211 && tm.tm_hour == 2 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        
          num = 'P';

        att(num,timeinfo,"AP.txt");
      }
      i = strcmp(buffer, "Wednesday");
      if (i == 0)

        num = 'A';
      if (longitude < 24.856910 && longitude> 24.856838 && latitude< 67.264519 && latitude> 67.264211 && tm.tm_hour == 8 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        
          num = 'P';

        att(num,timeinfo,"PF.txt");
      }

      num = 'A';
      if (longitude < 24.856910 && longitude> 24.856838 && latitude< 67.264519 && latitude> 67.264211 && tm.tm_hour == 10 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        
          num = 'P';

          att(num,timeinfo,"CALC.txt");
      }

      num = 'A';
      if (longitude < 24.856910 && longitude> 24.856838 && latitude< 67.264519 && latitude> 67.264211 && tm.tm_hour == 13 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        
          num = 'P';

        att(num,timeinfo,"PFL.txt");
        }

      i = strcmp(buffer, "Thursday");
      if (i == 0)

        num = 'A';
      if (longitude < 24.856910 && longitude> 24.856838 && latitude< 67.264519 && latitude> 67.264211 && tm.tm_hour == 8 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        
          num = 'P';

    att(num,timeinfo,"AP.txt");    }
      

      num = 'A';
      if (longitude < 24.856910 && longitude> 24.856838 && latitude< 67.264519 && latitude> 67.264211 && tm.tm_hour == 9 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        
          num = 'P';

          FILE *fptr;
          att(num,timeinfo,"PF.txt");
      }

      num = 'A';
      if (longitude < 24.856910 && longitude> 24.856838 && latitude< 67.264519 && latitude> 67.264211 && tm.tm_hour == 10 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) 
        {
          num = 'P';

     att(num,timeinfo,"PF.txt"); }

      num = 'A';
      if (longitude < 24.856910 && longitude> 24.856838 && latitude< 67.264519 && latitude> 67.264211 && tm.tm_hour == 11 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) 
        {
          num = 'P';

          att(num,timeinfo,"ENG.txt");
      }

      num = 'A';
      if (longitude < 24.856910 && longitude> 24.856838 && latitude< 67.264519 && latitude> 67.264211 && tm.tm_hour == 12 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        
          num = 'P';

          att(num,timeinfo,"PST.txt");
      }

      num = 'A';
      if (longitude < 24.856910 && longitude> 24.856838 && latitude< 67.264519 && latitude> 67.264211 && tm.tm_hour == 15 &&
          tm.tm_min >= 00 && tm.tm_min <= 40) {
        
        num='p';
        att(num,timeinfo,"ICTA.txt");
      }

      i = strcmp(buffer, "Friday");
      if (i == 0)

        num = 'A';
      if (longitude < 24.856910 && longitude> 24.856838 && latitude< 67.264519 && latitude> 67.264211 && tm.tm_hour == 9 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        
          num = 'P';

          att(num,timeinfo,"PST.txt");
      }

      num = 'A';
      if (longitude < 24.856910 && longitude> 24.856838 && latitude< 67.264519 && latitude> 67.264211 && tm.tm_hour == 10 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
       num= 'P'; 
        att(num,timeinfo,"PF.txt");
        }
      

      num = 'A';
      if (longitude < 24.856910 && longitude> 24.856838 && latitude< 67.264519 && latitude> 67.264211 && tm.tm_hour == 13 &&
          tm.tm_min >= 00 && tm.tm_min <= 50) {
        
          num = 'P';

          att(num,timeinfo,"ENGL.txt");
      }
    alarm(longitude, latitude);
    //usleep(2500000000);
    
  

}
}
