

void parse (char buf[])
    char *pend;
    int i = 0;
    char *p = strtok (buf, ":,");
    char *array[100];
    
    while (p != NULL)
    {
        array[i++] = p;
        p = strtok (NULL, ":,");
    }
    
    printf("%s\n", array[4]
    printf("%s\n", array[2]);
    double f1 = strtod(array[2], &pend);
    double f2 = strtod(array[4], &pend);
    longitude=f1;
    latitude=f2;
    printf("longitude:%.15F",longitude);
    printf("latitude:%.15F",latitude);
    
    return 0;
}
