#include "GPIOHandler.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#define BUFSIZE 128

const char* temp_ext_addr = "/sys/bus/w1/devices/28-0119523a7eff/w1_slave"; 
const char* temp_buf_addr = "/sys/bus/w1/devices/28-011952459cff/w1_slave";
const char* temp_in_addr  = "/sys/bus/w1/devices/28-00000a724d8e/w1_slave";
const char* temp_out_addr = "/sys/bus/w1/devices/28-0119523c2dff/w1_slave"; 

//zwraca tablice temperatur
double readTemperature(const char* path )
{
	double temp;
	int i, j;
	int fd;
	int ret;
	char buf[BUFSIZE];
	char tempBuf[5];

	while( 1 ){
	fd = open( path, O_RDONLY );
	if( -1 == fd ){
		printf("ERROR READING TEMPERATURE DATA!");
		return 1;		
	}
	while(1){
		ret = read(fd, buf, BUFSIZE);
		if(0 == ret){
			break;	
		}
		if(-1 == ret){
			if(errno == EINTR){
				continue;	
			}
			perror("read()");
			close(fd);
			return 1;
		}
	}
	for(i=0;i<sizeof(buf);i++){
		if(buf[i] == 't'){
			for(j=0;j<sizeof(tempBuf);j++){
				tempBuf[j] = buf[i+2+j]; 	
			}
		}	
	}

	temp = (float)atoi(tempBuf) / 1000;
	close(fd);
	return temp;
	}
	return 0;

}

void getTemperatures( double* tab  )
{
	*tab = readTemperature( temp_ext_addr );
	*(tab+1) = readTemperature( temp_buf_addr );
	*(tab+2) = readTemperature( temp_in_addr );
	*(tab+3) = readTemperature( temp_out_addr );
}

void getPressures( double* p  )
{
wiringPiSetup();
pinMode(11, INPUT );

if( digitalRead( 11 ) == 1 )
{
	*p = 100000;
	*(p+1) = 100000;
}
else
{
	*p = 0;
	*( p+1 ) = 0;
}

}

	
void startHeating( int*  monitor, int is_turbo  )
{
	switch( *monitor )
	{
		case 0 :
		pinMode( 16, OUTPUT );
		if( is_turbo)pinMode( 4, OUTPUT );
		break;


		case 1 :
		break;

		case 2 :
		pinMode( 15, OUTPUT );
		if( is_turbo )pinMode( 5, OUTPUT );
		break;
	}
	
	
	
	*monitor += 1;



}
void stopHeating( int*  monitor, int is_turbo )
{

	switch( *monitor )
	{
		case 1 :
		*monitor -= 1;
		pinMode( 16, INPUT );
		if( is_turbo )pinMode( 4, INPUT );
		break;
		case 2 :
		*monitor -= 1;
		break;
		case 3:
		pinMode(15, INPUT );
		if( is_turbo )pinMode( 5, INPUT );
		*monitor -= 1;
		break;
	}
}

void turboCheck( int is_turbo )
{
	if( is_turbo )
	{
	pinMode( 5, OUTPUT );
	pinMode( 4, OUTPUT );
	}
	else
	{
	pinMode( 5, INPUT );
	pinMode( 4, INPUT );
	}
}


void runAlarm()
{

  	wiringPiSetup () ;
  	
	pinMode (29, OUTPUT) ;

    digitalWrite (29, HIGH) ; delay (500) ;
    digitalWrite (29,  LOW) ; delay (500) ;
    digitalWrite (29, HIGH) ; delay (500) ;
    digitalWrite (29,  LOW) ; delay (500) ;
    digitalWrite (29, HIGH) ; delay (500) ;
    digitalWrite (29,  LOW) ; delay (500) ;



}
