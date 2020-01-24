#ifndef	GPIOHANDLER
#define GPIOHANDLER



	void getTemperatures( double* );
	void getPressures( double*  );
	void startHeating( int*  monitor, int is_turbo );
	void stopHeating( int*  monitor, int is_turbo );
	void turboCheck( int );
	//alarm when temperature or pressure to big
	void runAlarm();
#endif
