int alarm(float lng, float lat){

	FILE *alm;
	wiringPiSetup();
	pinMode(5, INPUT);

    while(true){
	//Detects High Voltage on GPIO5, creates a txt file with  invokes shell command 'arecord'
	if(digitalRead((5) == HIGH)
		{
			//if statement to check weather the file contents are not null run everything below USE r+:
			if(alm == NULL){
			alm = fopen("/home/pi/Desktop/emergency log.txt", "w+");
				printf("error opening file");
				return 1;
				}
			fprintf(alm, "At long: %f lat: %f\nThere was an emergency was detected\nAn audio file is being saved has been", lng, lat);
			fclose(alm);
			system("cd /home/pi/Desktop/ && arecord -d 10 -f cd -r 44100 -c2 -t wav | lame -S -x -h -b 128 - `date +%Y%m%d%H%M`.wav");

			//else if file read is not null file 
			else(alm != NULL){
			alm = fopen("/home/hp/Desktop/Shared/emergency log.txt", "a")
				}
			fprintf(alm, "\n-------\nAt long: %f lat: %f\nThere was an emergency was detected\nAn audio file is being saved has been", lng, lat);
			fclose(alm);
			system("cd /home/hp/Desktop/Shared && arecord -d 10 -f cd -r 44100 -c2 -t wav | lame -S -x -h -b 128 - `date +%Y%m%d%H%M`.wav");
		}
    return 0;
	}
}
