#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main ()
{
    double longitude;
    double latitude;
    char buf[] ="4.44141345/qwe/6.7";
    char *pend;
    int i = 0;
    char *p = strtok (buf, "/");
    char *array[3];
    
    while (p != NULL)
    {
        array[i++] = p;
        p = strtok (NULL, "/");
    }
    
        printf("%s\n", array[0]);
    printf("%s\n", array[2]);
    double f1 = strtod(array[0], &pend);
    double f2 = strtod(array[0], &pend);
    longitude=f1;
    latitude=f2;
    printf("%.15F",longitude);
    printf
    
    return 0;
}
