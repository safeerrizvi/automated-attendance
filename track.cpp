#include "alarm.h"
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringSerial.h>

int i;
int main() {
  char num = 'A';
  int latitude = 2;
  int longitude = 2;

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
  if ((serial_port = serialOpen("/dev/ttyAMA0", 9600)) <
      0) /* open serial port */
  {
    fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
    return 1;
  }

  if (wiringPiSetup() == -1) /* initializes wiringPi setup */
  {
    fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
    return 1;
  }

  while (1) {
    if (serialDataAvail(
            serial_port)) /* check for any data available on serial port */
    {
      dat = serialGetchar(serial_port); /* receive character serially */
      if (dat == '$') {
        IsitGGAstring = 0;
        GGA_index = 0;
      } else if (IsitGGAstring == 1) {
        buff[GGA_index++] = dat;
        if (dat == '\r')
          is_GGA_received_completely = 1;
      } else if (GGA_code[0] == 'G' && GGA_code[1] == 'G' &&
                 GGA_code[2] == 'A') {
        IsitGGAstring = 1;
        GGA_code[0] = 0;
        GGA_code[0] = 0;
        GGA_code[0] = 0;
      } else {
        GGA_code[0] = GGA_code[1];
        GGA_code[1] = GGA_code[2];
        GGA_code[2] = dat;
      }
    }
    if (is_GGA_received_completely == 1) {
      printf("GGA: %s", buff);
      is_GGA_received_completely = 0;

      double longitude;
      double latitude;
      char *pend;
      int i = 0;
      char *p = strtok(buff, ":,");
      char *array[20];

      while (p != NULL) {
        array[i++] = p;
        p = strtok(NULL, ":,");
      }

      printf("%s\n", array[2]);
      printf("%s\n", array[4]);
      double f1 = strtod(array[2], &pend);
      double f2 = strtod(array[4], &pend);
      longitude = f1;
      latitude = f2;
      printf("%.15F", longitude);
    }
    int i = strcmp(buffer, "Thursday");
    if (i == 0)

      num = 'A';
    if (longitude == 2 && latitude == 2 && tm.tm_hour == 8 && tm.tm_min >= 00 &&
        tm.tm_min <= 15) {
      {
        num = 'P';

        FILE *fptr;
        fptr = fopen("/Users/maaz/Public/ICT.txt", "a");
        if (fptr == NULL) {
          printf("Error!");
          exit(1);
        }

        fprintf(fptr, "\n 19K-1110 Maaz Asim %c    %s\n", num,
                asctime(timeinfo));
        fclose(fptr);
      }

      num = 'A';
      if (longitude == 2 && latitude == 2 && tm.tm_hour == 12 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        {
          num = 'P';

          FILE *fptr;
          fptr = fopen("/Users/maaz/Public/ENG.txt", "a");
          if (fptr == NULL) {
            printf("Error!");
            exit(1);
          }

          fprintf(fptr, "\n 19K-1110 Maaz Asim %c    %s\n", num,
                  asctime(timeinfo));
          fclose(fptr);
        }
      }

      num = 'A';
      if (longitude == 2 && latitude == 2 && tm.tm_hour == 13 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        {
          num = 'P';

          FILE *fptr;
          fptr = fopen("/Users/maaz/Public/CALC.txt", "a");
          if (fptr == NULL) {
            printf("Error!");
            exit(1);
          }

          fprintf(fptr, "\n 19K-1110 Maaz Asim %c    %s\n", num,
                  asctime(timeinfo));
          fclose(fptr);
        }
      }

      num = 'A';
      if (longitude == 2 && latitude == 2 && tm.tm_hour == 15 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        {
          num = 'P';

          FILE *fptr;
          fptr = fopen("/Users/maaz/Public/ENG.txt", "a");
          if (fptr == NULL) {
            printf("Error!");
            exit(1);
          }

          fprintf(fptr, "\n 19K-1110 Maaz Asim %c    %s\n", num,
                  asctime(timeinfo));
          fclose(fptr);
        }
      }

      i = strcmp(buffer, "Tuesday");
      if (i == 0)

        num = 'A';
      if (longitude == 2 && latitude == 2 && tm.tm_hour == 9 &&
          tm.tm_min >= 00 && tm.tm_min <= 00) {
        {
          num = 'P';

          FILE *fptr;
          fptr = fopen("/Users/maaz/Public/PF.txt", "a");
          if (fptr == NULL) {
            printf("Error!");
            exit(1);
          }

          fprintf(fptr, "\n 19K-1110 Maaz Asim %c    %s\n", num,
                  asctime(timeinfo));
          fclose(fptr);
        }
      }

      num = 'A';
      if (longitude == 2 && latitude == 2 && tm.tm_hour == 10 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        {
          num = 'P';

          FILE *fptr;
          fptr = fopen("/Users/maaz/Public/AP.txt", "a");
          if (fptr == NULL) {
            printf("Error!");
            exit(1);
          }

          fprintf(fptr, "\n 19K-1110 Maaz Asim %c    %s\n", num,
                  asctime(timeinfo));
          fclose(fptr);
        }
      }

      num = 'A';
      if (longitude == 2 && latitude == 2 && tm.tm_hour == 12 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        {
          num = 'P';

          FILE *fptr;
          fptr = fopen("/Users/maaz/Public/ENG.txt", "a");
          if (fptr == NULL) {
            printf("Error!");
            exit(1);
          }

          fprintf(fptr, "\n 19K-1110 Maaz Asim %c    %s\n", num,
                  asctime(timeinfo));
          fclose(fptr);
        }
      }

      num = 'A';
      if (longitude == 2 && latitude == 2 && tm.tm_hour == 13 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        {
          num = 'P';

          FILE *fptr;
          fptr = fopen("/Users/maaz/Public/PST.txt", "a");
          if (fptr == NULL) {
            printf("Error!");
            exit(1);
          }

          fprintf(fptr, "\n 19K-1110 Maaz Asim %c    %s\n", num,
                  asctime(timeinfo));
          fclose(fptr);
        }
      };

      num = 'A';
      if (longitude == 2 && latitude == 2 && tm.tm_hour == 2 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        {
          num = 'P';

          FILE *fptr;
          fptr = fopen("/Users/maaz/Public/AP.txt", "a");
          if (fptr == NULL) {
            printf("Error!");
            exit(1);
          }

          fprintf(fptr, "\n 19K-1110 Maaz Asim %c    %s\n", num,
                  asctime(timeinfo));
          fclose(fptr);
        }
      };
      i = strcmp(buffer, "Wednesday");
      if (i == 0)

        num = 'A';
      if (longitude == 2 && latitude == 2 && tm.tm_hour == 8 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        {
          num = 'P';

          FILE *fptr;
          fptr = fopen("/Users/maaz/Public/PF.txt", "a");
          if (fptr == NULL) {
            printf("Error!");
            exit(1);
          }

          fprintf(fptr, "\n 19K-1110 Maaz Asim %c    %s\n", num,
                  asctime(timeinfo));
          fclose(fptr);
        }
      };

      num = 'A';
      if (longitude == 2 && latitude == 2 && tm.tm_hour == 10 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        {
          num = 'P';

          FILE *fptr;
          fptr = fopen("/Users/maaz/Public/CALC.txt", "a");
          if (fptr == NULL) {
            printf("Error!");
            exit(1);
          }

          fprintf(fptr, "\n 19K-1110 Maaz Asim %c    %s\n", num,
                  asctime(timeinfo));
          fclose(fptr);
        }
      }

      num = 'A';
      if (longitude == 2 && latitude == 2 && tm.tm_hour == 13 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        {
          num = 'P';

          FILE *fptr;
          fptr = fopen("/Users/maaz/Public/PFL.txt", "a");
          if (fptr == NULL) {
            printf("Error!");
            exit(1);
          }

          fprintf(fptr, "\n 19K-1110 Maaz Asim %c    %s\n", num,
                  asctime(timeinfo));
          fclose(fptr);
        }
      }

      i = strcmp(buffer, "Thursday");
      if (i == 0)

        num = 'A';
      if (longitude == 2 && latitude == 2 && tm.tm_hour == 8 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        {
          num = 'P';

          FILE *fptr;
          fptr = fopen("/Users/maaz/Public/AP.txt", "a");
          if (fptr == NULL) {
            printf("Error!");
            exit(1);
          }

          fprintf(fptr, "\n 19K-1110 Maaz Asim %c    %s\n", num,
                  asctime(timeinfo));
          fclose(fptr);
        }
      }

      num = 'A';
      if (longitude == 2 && latitude == 2 && tm.tm_hour == 9 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        {
          num = 'P';

          FILE *fptr;
          fptr = fopen("/Users/maaz/Public/PF.txt", "a");
          if (fptr == NULL) {
            printf("Error!");
            exit(1);
          }

          fprintf(fptr, "\n 19K-1110 Maaz Asim %c    %s\n", num,
                  asctime(timeinfo));
          fclose(fptr);
        }
      }

      num = 'A';
      if (longitude == 2 && latitude == 2 && tm.tm_hour == 10 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        {
          num = 'P';

          FILE *fptr;
          fptr = fopen("/Users/maaz/Public/PF.txt", "a");
          if (fptr == NULL) {
            printf("Error!");
            exit(1);
          }

          fprintf(fptr, "\n 19K-1110 Maaz Asim %c    %s\n", num,
                  asctime(timeinfo));
          fclose(fptr);
        }
      }

      num = 'A';
      if (longitude == 2 && latitude == 2 && tm.tm_hour == 11 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        {
          num = 'P';

          FILE *fptr;
          fptr = fopen("/Users/maaz/Public/ENG.txt", "a");
          if (fptr == NULL) {
            printf("Error!");
            exit(1);
          }

          fprintf(fptr, "\n 19K-1110 Maaz Asim %c    %s\n", num,
                  asctime(timeinfo));
          fclose(fptr);
        }
      }

      num = 'A';
      if (longitude == 2 && latitude == 2 && tm.tm_hour == 12 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        {
          num = 'P';

          FILE *fptr;
          fptr = fopen("/Users/maaz/Public/PST.txt", "a");
          if (fptr == NULL) {
            printf("Error!");
            exit(1);
          }

          fprintf(fptr, "\n 19K-1110 Maaz Asim %c    %s\n", num,
                  asctime(timeinfo));
          fclose(fptr);
        }
      }

      num = 'A';
      if (longitude == 2 && latitude == 2 && tm.tm_hour == 15 &&
          tm.tm_min >= 00 && tm.tm_min <= 40) {
        {
          num = 'P';

          FILE *fptr;
          fptr = fopen("/Users/maaz/Public/ICTA.txt", "a");
          if (fptr == NULL) {
            printf("Error!");
            exit(1);
          }

          fprintf(fptr, "\n 19K-1110 Maaz Asim %c    %s\n", num,
                  asctime(timeinfo));
          fclose(fptr);
        }
      }

      i = strcmp(buffer, "Friday");
      if (i == 0)

        num = 'A';
      if (longitude == 2 && latitude == 2 && tm.tm_hour == 9 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        {
          num = 'P';

          FILE *fptr;
          fptr = fopen("/Users/maaz/Public/PST.txt", "a");
          if (fptr == NULL) {
            printf("Error!");
            exit(1);
          }

          fprintf(fptr, "\n 19K-1110 Maaz Asim %c    %s\n", num,
                  asctime(timeinfo));
          fclose(fptr);
        }
      };

      num = 'A';
      if (longitude == 2 && latitude == 2 && tm.tm_hour == 10 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        {
          num = 'P';

          FILE *fptr;
          fptr = fopen("/Users/maaz/Public/PF.txt", "a");
          if (fptr == NULL) {
            printf("Error!");
            exit(1);
          }

          fprintf(fptr, "\n 19K-1110 Maaz Asim %c    %s\n", num,
                  asctime(timeinfo));
          fclose(fptr);
        }
      }

      num = 'A';
      if (longitude == 2 && latitude == 2 && tm.tm_hour == 14 &&
          tm.tm_min >= 00 && tm.tm_min <= 15) {
        {
          num = 'P';

          FILE *fptr;
          fptr = fopen("/Users/maaz/Public/ENGL.txt", "a");
          if (fptr == NULL) {
            printf("Error!");
            exit(1);
          }

          fprintf(fptr, "\n 19K-1110 Maaz Asim %c    %s\n", num,
                  asctime(timeinfo));
          fclose(fptr);
        }
      }
      alarm(lonitude, latitude);
      usleep(2500000000);
    }
  }
}
