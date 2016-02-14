#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PID.h"

void usage( const char *cmd )
{
	{	
		printf( "\n%s\n"
				"\t-t [ target ]\n" 
				"\t-s [ sweep value ]\n" 
				"\t-g [ gain limit ]\n" 
				"\t-k [ K value ]\n" 
				"\t-p [ P value ]\n" 
				"\t-i [ I value ]\n" 
				"\t-d [ D value ]\n" 
				"\t-b [ beginning value ]\n" 
				"\t-c [ number of iterations ]\n", 
				cmd );

		printf( "Example:\n"
			"%s -t 3000 -b 200 -s 255 -g 30 -k .5 -p .2 -i .3 -d .4 -c 100\n\n",
			cmd );

		exit(1);
	}
}

int main( int argc, char **argv )
{

	int Argc = argc;
	char **Argv = argv;

	double k=0.0, p=0.0, i=0.0, d=0.0;
	double s=0.0, t=0.0;
	double g=0.0, b=0.0;
	int    c=0;



	if( argc < 19 )
		usage( argv[0] );

	for( int x=1; x < Argc; x++ )
	{

		if( x+1 < Argc )
		{
			switch( Argv[x][1] )
			{
				case 'k':
					k = atof( Argv[++x] );
					break;
				case 'p':
					p = atof( Argv[++x] );
					break;
				case 'i':
					i = atof( Argv[++x] );
					break;
				case 'd':
					d = atof( Argv[++x] );
					break;
				case 'c':
					c = atoi( Argv[++x] );
					break;
				case 's':
					s = atof( Argv[++x] );
					break;
				case 'g':
					g = atof( Argv[++x] );
					break;
				case 'b':
					b = atof( Argv[++x] );
					break;
				case 't':
					t = atof( Argv[++x] );
					break;

			}
		}
		else
		{
			usage( argv[0] );
		}
	}

	PID pid( t, k, p, i, d );

	pid.set_sweep( s );
	pid.set_gain_limit( g );

	double current = b;
	double drive = 0.0;

	printf( "%f,%f,%f,%f,%f,%f\n", t, current, drive, 
			pid.pTerm(), pid.iTerm(), pid.dTerm() );


	for( int i=0; i < c; i++ )
	{
		double drive = pid.update( current );

		double r = (double)rand() / (double)RAND_MAX;

		current = current + (drive * ((r * 10.0) - 5.0)) + (.98 * (t - current));

		printf( "%f,%f,%f,%f,%f,%f\n", t, current, drive, 
				pid.pTerm(), pid.iTerm(), pid.dTerm() );
		fflush(stdout);
	}

	exit(0);
}



