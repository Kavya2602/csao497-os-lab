# include <stdio.h>
# include <string.h>

int main( )
{

	FILE *filePointer ;
	
	
	char dataToBeWritten[50]
		= "Programming is the must";

	filePointer = fopen("GfgTest.c", "w") ;
	
	
	if ( filePointer == NULL )
	{
		printf( "Program.c file failed to open." ) ;
	}
	else
	{
		
		printf("The file is now opened.\n") ;
		

		if ( strlen ( dataToBeWritten ) > 0 )
		{
		
			fputs(dataToBeWritten, filePointer) ;
			fputs("\n", filePointer) ;
		}
		fclose(filePointer) ;
		
		printf("Data successfully written in file Program.c\n");
		printf("The file is now closed.") ;
	}
	return 0;	
}
