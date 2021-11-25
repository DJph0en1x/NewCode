#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int numStorage; //Stores the number to use for fib sequence
int idNum; //Thread ID Number
int *sequenceNums; //Array to store the sequence numbers. 

void *fibCreator(void *param); //Runs the fib sequence

int main(int argc, char *argv[]) {//Begin Main
	pthread_t *tidHolder; //Thread itself
	pthread_attr_t attrNum; //Thread's attribute
	
	if (argc != 2) { //If the argument in commandline is not 2...
		fprintf(stderr, "usage: a.out <integer value\n>");
		return -1;
	}
	if (atoi(argv[1]) < 0) { //If the input is less than 0...
		fprintf(stderr, "%d must be >= 0\n", atoi(argv[1]));
		return -1;
	}

	numStorage = atoi(argv[1]); //Retrieve the input number. 
	sequenceNums = (int *)malloc(numStorage * sizeof(int));
	//Create the size of the sequence array with input number
	tidHolder = (pthread_t *)malloc(numStorage * sizeof(pthread_t));
	//Create the threads with the input number

	pthread_attr_init(&attrNum); //Inititate the thread attribute
	
	//For every thread until the input number has been reached...
	for(idNum = 0; idNum < numStorage; idNum++) { 
		pthread_create(&tidHolder[idNum], &attrNum, fibCreator, NULL); 			//Create Thread
	}
	
	//For every thread until the input number has been reached...
	for(int join = 0; join < numStorage; join++) { //Using new integer for 								error prevention
		pthread_join(tidHolder[join], NULL);//Each thread waits until previous						 thread has been finished
	}
	
	//Scanning all the sequence numbers that has been made...
	for(int i = 0; i < numStorage - 1; i++) {
		printf("%d,", sequenceNums[i]); //Print the sequence numbers.
	}
	printf("%d\n", sequenceNums[numStorage - 1]); //Prints the last sequence 								number.
	return 0;
}//End Main

void *fibCreator(void *param) {
	int storage3;//Stores the next fib number	

	if(idNum == 0) {//If there's only 0 in input...
		sequenceNums[idNum] = 0; //Fib sequence number is 0
		pthread_exit(0);//Exit thread.	
	}
	
	if(idNum == 1) {//If there's 1 in input...
		sequenceNums[idNum] = 1;//Place 1 in fib sequence 
		pthread_exit(0);//Exit thread.
	}
	else {//Otherwise...
		int storage1 = 0;//Stores the first sequence number
		int storage2 = 1;//Stores the second sequence number
		sequenceNums[0] = 0; //Stores 0 as the first fib number
		sequenceNums[1] = 1; //Stores 1 as the second fib number

		//Starting at 2, scanning every number until input number has 			been reached...
		for(idNum = 2; idNum < numStorage; idNum++) {
			//Add first and second storage to third storage
			storage3 = storage1 + storage2; 
			sequenceNums[idNum] = storage3;//Add third storage as 								the next fib number
			storage1 = storage2;// First storage is second storage
			storage2 = storage3;// Second storage is third storage
		}
		pthread_exit(0);//Exit thread. 
	}//End else statement
}//End runner function. 
