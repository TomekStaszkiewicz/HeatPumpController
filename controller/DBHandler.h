#ifndef	DBHANDLER
#define DBHANDLER
/*	1. temp_needed - wymagana temperatura
 *	2. temp_max_in/out - maksymalna temperatura zasilania/powrotu
 *	3. p_max/in/out - maksymalne cisnienie ssania i tloczenia
 *
 *
 *
 * */



	typedef struct Settings{
		double temp_needed;
		double temp_max_in;
		double temp_max_out;
		double p_max_in;
		double p_max_out;
		double histereza;
		double temp_max_bufora;
		int    turbo;
	}Settings;

	typedef struct Data{
		double temp_ext;
		double temp_in;
		double temp_out;
		double p_in;
		double p_out;
		double temp_bufora;
		long int timestamp;
	}Data;

	typedef struct Tools{
		int sprezarka;
		int pompy;
		}Tools;
	
	int 	ConnectToDB();
	int 	CreateTools( Tools* t );
	int 	CreateSettings( Settings* s );
	int 	CreateData( Data* d );
	void 	SaveData( Data* d  );
	void 	SaveSettings( Settings* s  );
	void 	SaveTools( Tools* t  );
	
	void		 ReadSettings( Settings* s );
	void	  	 ReadData( Data* d );
	void	         ReadTools( Tools* t );
	int 		 DisconnectToDB();


#endif
