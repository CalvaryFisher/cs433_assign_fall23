/**
* Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author Reece Harris & Calvary Fisher 
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <iostream>
#include "buffer.h"
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


using namespace std;

// global buffer object
Buffer buffer(5);
pthread_mutex_t mutex_lock;
sem_t *full;
sem_t *empty;



// Producer thread function
// TODO: Add your implementation of the producer thread here
void *producer(void *param) {
    // Each producer insert its own ID into the buffer
    // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.
    buffer_item item = *((int *) param);
    cout << "Producer " << item << endl;
    do {

        /* sleep for a random period of time */
        usleep(rand()%1000000);
        sem_wait(empty);
        pthread_mutex_lock(&mutex_lock);
        cout << "In Critical Section" << endl;
        // TODO: Add synchronization code here
        if (buffer.insert_item(item)) {
            cout << "Producer " << item << ": Inserted item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Producer error condition"  << endl;    // shouldn't come here
        }
        pthread_mutex_unlock(&mutex_lock);
        sem_wait(full);
    } while(true);
}

// Consumer thread function
// TODO: Add your implementation of the consumer thread here
void *consumer(void *param) {
    buffer_item item = *((int *) param);
    cout << "Consumer " << item << endl;
    do {
        /* sleep for a random period of time */
        usleep(rand() % 1000000);
        sem_wait(full);
        pthread_mutex_lock(&mutex_lock);
        cout << "In Critical Section" << endl;
        // TODO: Add synchronization code here
        if (buffer.remove_item(item)) {
            cout << "Consumer " << item << ": Removed item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Consumer error condition" << endl;    // shouldn't come here
        }
        pthread_mutex_unlock(&mutex_lock);
        sem_wait(empty);
        
    } while(true);
}

int main(int argc, char *argv[]) {
    
    //Initializing locks
    pthread_mutex_init(&mutex_lock, NULL);
    //Semaphore initialization (open) - named semaphore
    //WHAT DO THE FLAGS 0644 MEAN? SHARABLE BY OTHER FUNCITONS?
    empty = sem_open("empty", O_CREAT, 0644, 5);
    // in Chap 7.3 they gave an uppercase name to the semaphores in sem_open
    // Thinking this might help distinguish between variable empty
    // and initialized shared named semaphore?
    full = sem_open("full", O_CREAT, 0644, 0);
    

    cout << "CREATED SEMAPHORES AND MUTEX LOCK" << endl;
    /* TODO: 1. Get command line arguments argv[1],argv[2],argv[3] */
    string sleep_time_arg = argv[1];
    string num_producers_arg = argv[2];
    string num_consumers_arg = argv[3];
    //Type cast to integers
    int sleep_time = stoi(sleep_time_arg);
    int num_producers = stoi(num_producers_arg);
    int num_consumers = stoi(num_consumers_arg);

    //Print the buffer (only a test, delete later)
    buffer.print_buffer();

    /* TODO: 2. Initialize buffer and synchronization primitives */
    pthread_t producer_thread[num_producers];
    pthread_t consumer_thread[num_consumers];
    /* TODO: 3. Create producer thread(s).*/
    /* You should pass an unique int ID to each producer thread, starting from 1 to number of threads */

    //Loop for how many producers/consumers we say in command line
    for (int i = 0; i < num_producers; i++) {
        //id = index + 1
        int id2 = i + 1;
        int error_check_2 = pthread_create(&producer_thread[i], NULL, producer, &id2);
        //if thread doesn't return 0, error in creation
        if (error_check_2 != 0) {
            cout << "Error creating producer" << endl;
        }
    }
    /* TODO: 4. Create consumer thread(s) */
    for (int j = 0; j < num_consumers; j++) {
        //id = index + 1
        int id = j + 1;
        int error_check = pthread_create(&consumer_thread[j], NULL, consumer, &id);
        //if thread doesn't return 0, error in creation
        if (error_check != 0) {
            cout << "Error creating consumer" << endl;
        }
    }

    for (int i = 0; i < num_producers; i++) {
        cout << "Producer ID: " << producer_thread[i] << endl;
        pthread_join(producer_thread[i], NULL);
    }
    for (int j = 0; j < num_consumers; j++) {
        pthread_join(consumer_thread[j], NULL);
    }
    /* TODO: 5. Main thread sleep */
    usleep(sleep_time);
    /* TODO: 6. Exit */
    exit(0);


}



//How do we initialize semaphore values? What is the semaphore flag mean?
//Make sure to error check command line arguments 
//(are they provided? are they valid?