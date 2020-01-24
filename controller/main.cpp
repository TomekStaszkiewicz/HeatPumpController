#include <iostream>
#include "DBHandler.h"
#include "GPIOHandler.h"
#include <unistd.h>

void checkSettings( Settings* s, Data* d, int* is_h, Tools* t ); 
void getData( double* t, double* p,  Data* d );

int main(){
	sleep( 5 );
	ConnectToDB();
	int is_heating = 0;
	//int *is_h = &is_heating;
//default settings
	Settings defSet;
	if( !CreateSettings( &defSet ) )printf("ERROR!");
	defSet.temp_needed = 50;
	defSet.temp_max_in = 70;
	defSet.temp_max_out = 70;
	defSet.p_max_in = 1000;
	defSet.p_max_out = 1000;
	defSet.histereza = 5;
	defSet.temp_max_bufora = 100;
	defSet.turbo = 0;
	SaveSettings( &defSet );
//	free( &defSet );
	sleep( 1 );

	while( true )
	{	
		double* temp = (double*)malloc(4*sizeof(double));
		getTemperatures(temp);
		double* p = (double*)malloc( 2 * sizeof(double));
		getPressures( p );
		Data d;
		Settings s;
		Tools t;
		if( !CreateData( &d ) )printf("ERROR!");
		if( !CreateSettings( &s ) )printf("ERROR!");
		ReadSettings( &s );
		getData( temp, p, &d );
		checkSettings( &s, &d, &is_heating, &t );
		SaveData( &d );
		SaveTools( &t );
		free( temp );
//		free( &s );
//		free( &d );
	sleep(6);
	}
	DisconnectToDB();
}

void checkSettings( Settings* s, Data* d, int* is_h, Tools* t )
{
	printf("\nis_h = %d\n", *is_h);
	t->sprezarka = 0;
	t->pompy = 0;
	if( ( d->temp_in > s->temp_max_in ))
	{
	runAlarm();
	printf("\nTemp in too big!\n");
	}	
	else if( d->temp_out > s->temp_max_out )
	{
	runAlarm();
	printf("\nTemp out too big!\n");
	
	}	
	else if( d->p_in > s->p_max_in ) 
	{
	runAlarm();
	printf("\nP in too big!\n");
	
	}
	else if( d->p_out > s->p_max_out ) 
	{
	runAlarm();
	printf("\nP out too big!\n");
	
	}
	else if( d->temp_bufora > s->temp_max_bufora ) 
	{
	runAlarm();
	printf("\nTemp bufora too big!\n");
	}
	//podczas rozruchu najpierw dzialaja pompy a potem sprezarka
	else if( d->temp_bufora < ( s->temp_needed - s->histereza ) && *is_h < 3  ) 
	{
		startHeating( is_h, s->turbo );
		t->pompy = 1;
	}
	else if( d->temp_bufora > s->temp_needed && *is_h )
	{
		stopHeating( is_h, s->turbo );
		t->sprezarka = 1;
	}
	else if( *is_h == 3 )
	{
		t->sprezarka = 1;
		t->pompy = 1;
		turboCheck( s->turbo );
	}
	
}


void getData( double* t, double* p, Data* d )
{
	d->temp_ext = *t;
	d->temp_bufora = *(t + 1 );
	d->temp_in = *( t + 2 );
	d->temp_out = *( t + 3 );
	d->p_in = *p;
	d->p_out = *(p+1);
}


