#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
// TODO: Transform Array
// Input: 2D array, number of rows, number of cols
// For each row in the array, you will swap the first half of each row
// with its second half. For rows with an odd number, the middle
// element will stay in place
// e.g, input:
// [
// [1, 2, 3, 4],
// [5, 6, 7, 8],
// [9, 10, 11, 12]
// ]
// now swap the first half of the rows with the second half
// [
// [3, 4, 1, 2],
// [7, 8, 5, 6],
// [11, 12, 9, 10]
// ]
// DONE!
void transformArray(int **arr, int rows, int cols)
{
	//printf(stderr,"./hw1 transformArray");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols/2; j++)
        {
        	int temp = arr[i][j];
        	arr[i][j] = arr[i][cols/2+j+1];
        	arr[i][cols/2 +j+1] = temp;
        }
    }
    return;
}
typedef struct MusicRecord
{
    int id;
    char *name;
    int releaseYear;
} record_t;
// TODO: Number of Duplicate Records Input array of records, total number of records
// Identify the total number of duplicates (if any) in the record collection. A duplicate is a record of the same title and release year. e.g., RecordA 1970, RecordB 1968, RecordA 1970, RecordC 1970 there is a total of 1 duplicate
int numDuplicates(record_t *records, int numRecords)
{
	int duplicate=0;
	for(int x = 0; x< numRecords -1 ; x++){
		for(int j = x+1; j< numRecords; j++){
		if((strcmp(records[x].name,records[j].name)) ==0 && (records[x].releaseYear == records[j].releaseYear)){
		records[j].id = 0;
		}
	}  
	}  
	for(int x = 0; x< numRecords ; x++){
	if(records[x].id == 0){
		duplicate++;
	}
	}
    return duplicate;
}

void replaceLastNRandom(int *arr, int numElements, int numToReplace)
{
    srand(12345);
    int x = numToReplace;
    for(int i =numElements-x;i<numElements;i++){
    	arr[i] = rand();
    	x--;
    }
    
    return;
}
int main(int argc, char *argv[])
{
    // argc - number of cmd line args
    // argv - array of cmd line args
    //Ensure at least two command line args were given
    // e.g., ./hw1 {transformArray|numDuplicates|replaceLastNRandom}
    if (argc < 2)
    {
    //fprintf(stderr,"Usage: ./hw1 {transformArray|numDuplicates|replaceLastNRandom}\n ");
    return EXIT_FAILURE;
    }
        fprintf(stderr,"Usage: ./hw1 {transformArray|numDuplicates|replaceLastNRandom}\n ");
    if(strcmp(argv[1], "transformArray") == 0)
	{
        int rows = atoi(argv[2]);
    int cols = atoi(argv[3]);
    	
    // We are taking a 2d array as input
    // Thus, rows*cols is the number of elements in the array
    // We need to add 4 to skip the first four arguments:
    // program name, exercise name, num rows, num cols
    if ((rows * cols) + 4 != argc)
    {
	//fprintf(stderr, "Usage: ./hw1 transformArray {rows} {cols} {rows *cols elements}\n");
return EXIT_FAILURE;
    }
    // first, we need to allocate enough room for num rows arrays
    int **arr = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        // now, lets allocate enough room for num cols elements in each array
            arr[i] = (int *)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++)
        {
            // now lets load the elements
            arr[i][j] = atoi(argv[4 + i * cols + j]);
        }
    }
    // Now arr is a 2d array loaded with elements from command line args
        transformArray(arr, rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
        free(arr[i]);
    }
    free(arr);
}
else if(strcmp(argv[1], "numDuplicates") == 0)
{
    // each struct requires 3 elements: id, name, release year
    int numRecords = atoi(argv[2]);
    
    if (argc != (numRecords * 3) + 3)
    {
        return EXIT_FAILURE;
    }
    // allocate enough space for an array of numRecords record_t structs.
    record_t *records = (record_t *)malloc(numRecords * sizeof(record_t));
    
    for (int i = 0; i < numRecords; i++)
    {
        records[i].id = atoi(argv[3 + i * 3]);
        records[i].name = strdup(argv[4 + i * 3]);
       records[i].releaseYear = atoi(argv[5 + i * 3]);
    }
    int result = numDuplicates(records, numRecords);
 
    printf("%d", result);
        for (int i = 0; i < numRecords; i++)
    		{
        free(records[i].name);
    		}
    		free(records);
} else if(strcmp(argv[1], "replaceLastNRandom") == 0)
{
    int numToReplace = atoi(argv[2]);
    int numElements = atoi(argv[3]);
    if(numToReplace > numElements){
    	return EXIT_FAILURE;
    }
 
    // You can assume numToReplace <= numElements
    // You can assume all elements will be integers
    if (numElements +4 != argc)
    {
	
	return EXIT_FAILURE;
    }
    int* arr = (int*)malloc(numElements * sizeof(int*));
    for(int i =0; i<numElements;i++){
    	arr[i] = atoi(argv[4 + i]);
    }
    replaceLastNRandom(arr, numElements, numToReplace);
    
    // output should be:
    // 1 2 3 4 5
    for (int i = 0; i < numElements; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
}
else {
return EXIT_FAILURE;
}

return EXIT_SUCCESS;
}
