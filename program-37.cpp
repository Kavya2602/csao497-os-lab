#include <stdio.h>
#include <stdlib.h>
int main() 
{
    int ReadyQueue[100], i, n, TotalHeadMov = 0, initial;
    printf("Enter the number of disk requests: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 100)
	 {
        printf("Invalid number of requests.\n");
        return 1; 
    }
    printf("Enter the disk requests: ");
    for (i = 0; i < n; i++) {
        if (scanf("%d", &ReadyQueue[i]) != 1) 
		{
            printf("Invalid input.\n");
            return 1; 
        }
    }

    printf("Enter the initial position of the disk head: ");
    if (scanf("%d", &initial) != 1) {
        printf("Invalid input.\n");
        return 1; 
    }
    for (i = 0; i < n; i++)
	 {
        TotalHeadMov += abs(ReadyQueue[i] - initial);
        initial = ReadyQueue[i];
    }
    printf("Total Head Movement = %d\n", TotalHeadMov);
    return 0; 
}
