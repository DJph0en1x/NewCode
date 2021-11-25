#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define PTHREAD_SYNC

int SharedVariable = 0;//Contains the variable created from threads. 
pthread_mutex_t locking; //Locks the thread
pthread_barrier_t barrier; //Protects the thread process

void *SimpleThread(void *which) {//Begin function
	int *pointStorage; //Stores the input gained from the parameter
	pointStorage = which; //Assign the parameter to storage
	int num, val = 0; //number to use for loop and value to store thread's 					number into
	//Reading every number until 20 has been reached...
	for(num = 0; num < 20; num++) {//Begin Loop
		#ifdef PTHREAD_SYNC //Pthread_sync begins
		pthread_mutex_lock(&locking); //Locks the thread in place.
		/*put your synchronization-related code here*/
		#endif //Ends the Pthread_Sync definition
		//If the random number is less than the equation's results...
		//if(random() > RAND_MAX / 2) 
			//usleep(10); //Put Thread to sleep

		val = SharedVariable; //Stores the value to the variable to be 						shared.
		//Prints the thread's value
		printf("*** thread %d sees value %d\n", *pointStorage, val);
		SharedVariable = val + 1; //Add 1 point to the shared value.
		
		#ifdef PTHREAD_SYNC //Begin Pthread_Sync definition
		pthread_mutex_unlock(&locking); //Unlocking thread.
		#endif //Ending Definition
	} //End Loop
	pthread_barrier_wait(&barrier);//Create barrier to keep the thread's 						contents safe
	val = SharedVariable; //Value becomes the variable to be shared.
	//Prints the thread's final value.
	printf("Thread %d sees final variable %d\n", *pointStorage, val);
}//End Function.

int main(int argc, char *argv[]) {//Begin Main.
	pthread_t *th1; //Thread to be created
	int idNum; //Thread's ID number
	
	if(argc != 2) { //If the first's parameter is not 2...
		printf("Wrong number of arguments\n");//Print error message
		return 0;//End Function
	}	
	else {//Otherwise...
		int value = 1;//Value starting at 1
		//Scanning the argument in commandline...
		for (idNum = 0; idNum < strlen(argv[1]); idNum++) {//Begin Loop
			//If argument is not between 0 or 9...
			if(argv[1][idNum] < '0' || argv[1][idNum] > '9') {
				value = 0;//Value becomes 0
				break; //End the program.
			}
		}//End Loop

		if(value == 0) { //If value is 0...
			printf("\n Please give a positive number\n");
		}
		else {//Otherwise...
			int numThreads = atoi(argv[1]);//Store input value.
			//Creates the thread with input as it's size.
			th1 = (pthread_t *)malloc(sizeof(pthread_t) * atoi(argv [1]));
			//Creates the storage of threads with input as it's size
			int *threadList = (int *)malloc(sizeof(int) * numThreads);
			//Initialize the locking mechanism
			pthread_mutex_init(&locking, NULL);
			//Initialize the thread barrier.
			pthread_barrier_init(&barrier, NULL, numThreads);
			
			//Scanning every threads to be created...
			for(idNum = 0; idNum < numThreads; idNum++) {					//Begin Loop
				//Store thread into the list.
				threadList[idNum] = idNum;
			}//End Loop

			//Scanning every thread to be created...
			for(idNum = 0; idNum < numThreads; idNum++) {					//Begin Loop
				//Create the thread.
				pthread_create(&th1[idNum], NULL, SimpleThread, &threadList[idNum]);
			}//End Loop

			//For every loop that's been created...
			for(idNum = 0; idNum < numThreads; idNum++) {					//Begin Loop
				//Make each and every thread wait.
				pthread_join(th1[idNum], NULL);
			}//End Loop
		}//End Else statement.
	}//End first Else statement.	
	exit(0);//Exit program.
}//End Main
