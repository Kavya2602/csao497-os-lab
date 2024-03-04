#include <stdio.h>
#include <stdlib.h>

int main()

 {
    FILE *fptr1, *fptr2;
    char filename1[100], filename2[100], c;
    printf("Enter the filename to open for reading: ");
    scanf("%99s", filename1);
    if ((fptr1 = fopen(filename1, "r")) == NULL)
	 {
        printf("Cannot open file %s for reading\n", filename1);
        exit(EXIT_FAILURE);
    }
    printf("Enter the filename to open for writing: ");
    scanf("%99s", filename2);
    if ((fptr2 = fopen(filename2, "w")) == NULL) 
	{
        printf("Cannot open file %s for writing\n", filename2);
        fclose(fptr1); 
        exit(EXIT_FAILURE);
    }
    while ((c = fgetc(fptr1)) != EOF) 
	{
        fputc(c, fptr2);
    }
    printf("Contents copied from %s to %s\n", filename1, filename2);
    fclose(fptr1);
    fclose(fptr2);

    return 0;
}
