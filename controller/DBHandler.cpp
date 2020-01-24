#include "DBHandler.h"
#include <sqlite3.h> //include sqlite library
#include <ctime> //data library
#include <string>
#include <memory.h>

using namespace std;

	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	const char* data = "Callback function: ";
	char const *sql; //pointer created for sql statements


//////////////////////////////////////////////private methods
string SQLVALUE( float value )
{
	return "'" + std::to_string( value ) + "'";
}

////////////////////////////////////////////////
static int callbackSettings( void* sSet, int argc, char **argv, char **azColName )
{
//	string* tab;
//	for( int i = 1 ; i<=6; i++)
//	{
//		*(tab+i) = *argv[i];
//	}
	 Settings* s = ( Settings * )sSet;

	for( int i = 1; i<=8; i++ )
	{
		if( strcmp( azColName[i], "TEMP_MAX_IN" ) == 0 )
			s->temp_max_in = atof( argv[i] );
		else if( strcmp( azColName[i], "TEMP_MAX_OUT" ) == 0 )
			s->temp_max_out = atof( argv[i] );
		else if( strcmp( azColName[i], "TEMP_NEEDED" ) == 0 )
			s->temp_needed = atof( argv[i] );
		else if( strcmp( azColName[i], "P_MAX_IN" ) == 0 )
			s->p_max_in = atof( argv[i] );
		else if( strcmp( azColName[i], "P_MAX_OUT" ) == 0 )
			s->p_max_out = atof( argv[i] );
		else if( strcmp( azColName[i], "HISTEREZA" ) == 0 )
			s->histereza = atof( argv[i] );
		else if( strcmp( azColName[i], "TEMP_MAX_BUFORA" ) == 0 )
			s->temp_max_bufora = atof( argv[i] );
		else if( strcmp( azColName[i], "TURBO" ) == 0)					s->turbo = atoi( argv[i] );
}



//	s->temp_max_in = atof( (tab[1]).c_str());
//	s->temp_max_out = atof((tab[2]).c_str());
//	s->p_max_in = atof((tab[3]).c_str());
//	s->p_max_out = atof((tab[4]).c_str());
//	s->histereza = atof((tab[5].c_str()));
//	s->temp_max_bufora = atof((tab[6]).c_str());
	return 0;

}
static int callbackTools( void* tTool, int argc, char **argv, char **azColName )
{
//	string* tab;
//	for( int i = 1 ; i<=6; i++)
//	{
//		*(tab+i) = *argv[i];
//	}
	 Tools* t = ( Tools * )tTool;

	for( int i = 1; i<=2; i++ )
	{
		if( strcmp( azColName[i], "SPREZARKA" ) == 0 )
			t->sprezarka = atoi( argv[i] );
		else if( strcmp( azColName[i], "POMPY" ) == 0 )
			t->pompy = atoi( argv[i] );
	
	}


//	s->temp_max_in = atof( (tab[1]).c_str());
//	s->temp_max_out = atof((tab[2]).c_str());
//	s->p_max_in = atof((tab[3]).c_str());
//	s->p_max_out = atof((tab[4]).c_str());
//	s->histereza = atof((tab[5].c_str()));
//	s->temp_max_bufora = atof((tab[6]).c_str());
	return 0;

}
static int callbackData( void* dData, int argc, char **argv, char **azColName )
{
//	string* tab;
//	for( int i = 1 ; i<=6; i++)
//	{
//		*(tab+i) = *argv[i];
//	}
	 Data* d = ( Data * )dData;

	for( int i = 1; i<=6; i++ )
	{
		if( strcmp( azColName[i], "TEMP_EXT" ) == 0 )
			d->temp_ext = atof( argv[i] );
		else if( strcmp( azColName[i], "TEMP_IN" ) == 0 )
			d->temp_in = atof( argv[i] );
		else if( strcmp( azColName[i], "TEMP_OUT" ) == 0 )
			d->temp_out = atof( argv[i] );
		else if( strcmp( azColName[i], "P_IN" ) == 0 )
			d->p_in = atof( argv[i] );
		else if( strcmp( azColName[i], "P_OUT" ) == 0 )
			d->p_out = atof( argv[i] );
		else if( strcmp( azColName[i], "TEMP_BUFORA" ) == 0 )
			d->temp_bufora = atof( argv[i] );
	}
	return 0;

}



static int callback( void *NotUsed, int argc, char** argv, char** azColName)
{
return 0;

}


/////////////////////////////////////////////	
int 	ConnectToDB()
{
	rc = sqlite3_open("heatpump.db", &db);
	if( rc )
	{
		fprintf( stderr, "Error connecting to database:  %s\n ", sqlite3_errmsg( db ) );	
		return 0;
	}
		fprintf( stdout, "Succesfully connected to database!\n" );
	
		sql = "CREATE TABLE IF NOT EXISTS SETTINGS("   \
	      	"ID 		INTEGER		PRIMARY KEY		AUTOINCREMENT	NOT NULL,"\
		"TEMP_NEEDED	FLOAT					NOT NULL,"\
		"TEMP_MAX_IN	FLOAT					NOT NULL,"\
	      	"TEMP_MAX_OUT	FLOAT					NOT NULL,"\
	      	"P_MAX_IN	FLOAT					NOT NULL,"\
		"P_MAX_OUT	FLOAT					NOT NULL,"\
		"HISTEREZA	FLOAT					NOT NULL,"\
		"TURBO		INTEGER					NOT NULL,"\
		"TEMP_MAX_BUFORA	FLOAT				NOT NULL);";

		rc = sqlite3_exec( db, sql, callback, 0, &zErrMsg );

		if( rc != SQLITE_OK )
		{
			fprintf( stderr, "ERROR CREATING TABLE:  %s\n", zErrMsg );
			sqlite3_free( zErrMsg );
		}	 
		else
		{	
			fprintf( stdout, "Table SETTINGS created successfully!\n" );
		}


		sql = "CREATE TABLE IF NOT EXISTS DATA("   \
	      	"ID 		INTEGER		PRIMARY KEY		AUTOINCREMENT	NOT NULL,"\
	      	"TEMP_EXT	FLOAT					NOT NULL,"
		"TEMP_IN	FLOAT					NOT NULL,"\
	      	"TEMP_OUT	FLOAT					NOT NULL,"\
	      	"P_IN		FLOAT					NOT NULL,"\
		"P_OUT		FLOAT					NOT NULL,"\
		"TEMP_BUFORA	FLOAT					NOT NULL,"\
		"TIMESTAMP	DATETIME	DEFAULT CURRENT_TIMESTAMP	);";

		rc = sqlite3_exec( db, sql, callback, 0, &zErrMsg );

		if( rc != SQLITE_OK )
		{
			fprintf( stderr, "ERROR CREATING TABLE:  %s\n", zErrMsg );
			sqlite3_free( zErrMsg );
		}	 
		else
		{	
			fprintf( stdout, "Table DATA created successfully!\n" );
		}


		sql = "CREATE TABLE IF NOT EXISTS TOOLS("   \
	      	"ID 		INTEGER		PRIMARY KEY		AUTOINCREMENT	NOT NULL,"\
	      	"SPREZARKA	INTEGER					NOT NULL		,"\
	      	"POMPY		INTEGER					NOT NULL		);";
		rc = sqlite3_exec( db, sql, callback, 0, &zErrMsg );

		if( rc != SQLITE_OK )
		{
			fprintf( stderr, "ERROR CREATING TABLE:  %s\n", zErrMsg );
			sqlite3_free( zErrMsg );
		}	 
		else
		{	
			fprintf( stdout, "Table TOOLS created successfully!\n" );
		}
	sql = "CREATE TABLE IF NOT EXISTS AVERAGES("   \
	      	"ID 		INTEGER		PRIMARY KEY		AUTOINCREMENT	NOT NULL,"\
	      	"TEMP_EXT	FLOAT					NOT NULL,"
		"TEMP_IN	FLOAT					NOT NULL,"\
	      	"TEMP_OUT	FLOAT					NOT NULL,"\
	      	"P_IN		FLOAT					NOT NULL,"\
		"P_OUT		FLOAT					NOT NULL,"\
		"TEMP_BUFORA	FLOAT					NOT NULL,"\
		"SPREZARKA	INTEGER					NOT NULL,"
		"POMPA_DOL	INTEGER					NOT NULL,"\
	      	"POMPA_GORA	INTEGER					NOT NULL);";

		rc = sqlite3_exec( db, sql, callback, 0, &zErrMsg );

		if( rc != SQLITE_OK )
		{
			fprintf( stderr, "ERROR CREATING TABLE:  %s\n", zErrMsg );
			sqlite3_free( zErrMsg );
		}	 
		else
		{	
			fprintf( stdout, "Table AVERAGES created successfully!\n" );
		}
		return 1;
}

/////////////////////////////////////////////////
int 	CreateTools( Tools* t )
{
	t = (Tools*)malloc( sizeof( Tools ) );

	if( !t ) return 0;

	memset( t, 0, sizeof( Tools ));
	return 1;
}

/////////////////////////////////////////////////
int 	CreateSettings( Settings* s )
{
	s = (Settings*)malloc( sizeof( Settings ) );

	if( !s ) return 0;

	memset( s, 0, sizeof( Settings ));
	return 1;
}

////////////////////////////////////////////////
int 	CreateData( Data* d )
{
	d = (Data*)malloc( sizeof( Data ) );

	if( !d ) return 0;

	memset( d, 0, sizeof( Data ));
	return 1;

}

///////////////////////////////////////////////////
void	SaveData( Data* d  )
{
	string sqlquery;
	sqlquery = "INSERT INTO DATA (TEMP_EXT, TEMP_IN, TEMP_OUT, P_IN, P_OUT, TEMP_BUFORA ) "\
	      "VALUES (" + SQLVALUE( d->temp_ext )  + ", " + SQLVALUE( d->temp_in ) + "," + SQLVALUE( d->temp_out ) + "," + SQLVALUE( d->p_in ) + "," + SQLVALUE( d->p_out) + "," + SQLVALUE( d->temp_bufora) +  ");";

	rc = sqlite3_exec( db, sqlquery.c_str(), callback, 0, &zErrMsg );

	if( rc != SQLITE_OK )
	{
		fprintf( stderr, "Error inserting data  %s\n", zErrMsg );
		sqlite3_free( zErrMsg );
	}	
	else
	{
		fprintf( stdout, "Inserted successfully!\n" );
	
	}
}

//////////////////////////////////////////////////
void 	SaveSettings( Settings* s  )
{
	string sqlquery;
	sqlquery = "INSERT INTO SETTINGS (TEMP_NEEDED, TEMP_MAX_IN, TEMP_MAX_OUT, P_MAX_IN, P_MAX_OUT, HISTEREZA, TEMP_MAX_BUFORA, TURBO) "\
	      "VALUES (" + SQLVALUE( s->temp_needed ) + ", " + SQLVALUE( s->temp_max_in )  + ", " + SQLVALUE( s->temp_max_out ) + "," + SQLVALUE( s->p_max_in ) + "," + SQLVALUE( s->p_max_out ) + ", " + SQLVALUE( s->histereza) + ", " + SQLVALUE( s->temp_max_bufora ) + ", " + SQLVALUE(s->turbo) +  ");";

	rc = sqlite3_exec( db, sqlquery.c_str(), callback, 0, &zErrMsg );

	if( rc != SQLITE_OK )
	{
		fprintf( stderr, "Error inserting data  %s\n", zErrMsg );
		sqlite3_free( zErrMsg );
	}	
	else
	{
		fprintf( stdout, "Inserted successfully!\n" );
	
	}

}

/////////////////////////////////////////////////////
void 	SaveTools( Tools* t  ){
	string sqlquery;
	sqlquery = "INSERT INTO TOOLS ( SPREZARKA, POMPY ) "\
	      "VALUES (" + SQLVALUE( t->sprezarka )  + ", " + SQLVALUE( t->pompy ) + ");";

	rc = sqlite3_exec( db, sqlquery.c_str(), callback, 0, &zErrMsg );

	if( rc != SQLITE_OK )
	{
		fprintf( stderr, "Error inserting data  %s\n", zErrMsg );
		sqlite3_free( zErrMsg );
	}	
	else
	{
		fprintf( stdout, "Inserted successfully!\n" );
	}

}
//////////////////////////////////////////////////////
void  ReadSettings( Settings* s )
{
	Settings ret;
	string sqlquery = "SELECT * from SETTINGS ORDER BY ID DESC LIMIT 1";
	rc = sqlite3_exec( db, sqlquery.c_str(), callbackSettings, &ret , &zErrMsg );
	if( rc != SQLITE_OK ) 
	{
	fprintf( stderr, "\nERROR FETCHING DATA: %s\n", zErrMsg);
	sqlite3_free(zErrMsg);
	}
	else
	{
	fprintf(stdout, "DATA FETCHED");
	}
	*s = ret;	
	
}
//@TODO zmienic funkcje rzeby zwracaly te wskazniki
//////////////////////////////////
void ReadData( Data* d )
{
	Data ret;
	string sqlquery = "SELECT * from DATA ORDER BY ID DESC LIMIT 1";
	rc = sqlite3_exec( db, sqlquery.c_str(), callbackData, &ret , &zErrMsg );
	if( rc != SQLITE_OK ) 
	{
	fprintf( stderr, "\nERROR FETCHING DATA: %s\n", zErrMsg);
	sqlite3_free(zErrMsg);
	}
	else
	{
	fprintf(stdout, "DATA FETCHED");
	}
	*d = ret;

}
void ReadTools( Tools* t )
{
	Tools ret;
	string sqlquery = "SELECT * from TOOLS ORDER BY ID DESC LIMIT 1";
	rc = sqlite3_exec( db, sqlquery.c_str(), callbackTools, &ret , &zErrMsg );
	if( rc != SQLITE_OK ) 
	{
	fprintf( stderr, "\nERROR FETCHING DATA: %s\n", zErrMsg);
	sqlite3_free(zErrMsg);
	}
	else
	{
	fprintf(stdout, "DATA FETCHED");
	}
	*t = ret;
}

int DisconnectToDB()
{
	sqlite3_close( db );
	return 1;
}

