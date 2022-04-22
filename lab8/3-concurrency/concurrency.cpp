#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
#include <atomic>

typedef struct account {
    int balance;
    std::mutex balance_mtx;
} account_t;

/************************************** HELPER FUNCTION **************************************/

/* This function initializes a very large vector (5000 elts long) containing all the changes we'd like to 
   make to the account balance. 
*/
std::vector<int> make_large_vector() {
    std::vector<int> v;

    for (int i = 0; i < 5000; i++) {
        v.push_back(i - 300);
    }

    return v;
}

/************************************** THREAD FUNCTION **************************************/

/* This function will get passed into threads in order to modify an account with the requests. 
   Arguments: 
    - account_to_update: a pointer to the account whose balance we wish to modify
    - requests: a pointer to the vector containing all the requests
    - requests_mtx: a pointer to the mutex for the shared requests vector
    - requests_fulfilled: a pointer to the atomic boolean that dictates whether the threads can stop or not
*/
void update_account(account_t* account_to_update, std::vector<int>* requests, std::mutex* requests_mtx, std::atomic_bool* requests_fulfilled) {
    while (!*requests_fulfilled) {
        int current_request;
        requests_mtx->lock();
        
        if (requests->size() == 0) { 
            // Checks whether the requests are all fulfilled, and if so, set the boolean to true so other threads can stop
            *requests_fulfilled = true;
            requests_mtx->unlock();
            return;
        } else {
            // Otherwise, grab the first request
            current_request = requests->at(0);
            
            // Erase the request from the beginning of the vector and unlock the vector for other threads
            requests->erase(requests->begin());
            requests_mtx->unlock();

            // Add the amount in the request to the account's balance
            account_to_update->balance += current_request;
        }
    }   
}

/************************************** MAIN PROGRAM **************************************/

int main() {
    // Initialize an account with a balance
    account_t act;
    act.balance = 300;

    // Initialize vector with all the requests to add/subtract money from account
    std::vector<int> requests = make_large_vector();
    std::mutex requests_mtx;

    // atomic boolean that will get set to true when all requests have been fulfilled (so workers can stop working)
    std::atomic_bool all_requests_fulfilled = false;

    // Initialize worker pool and pass `update_account` function into threads
    std::vector<std::thread> workers;

    for (int i = 0; i < 6; i++) {
        workers.push_back(std::thread(update_account, &act, &requests, &requests_mtx, &all_requests_fulfilled));
    }
    
    // Wait for all threads to finish
    for (int i = 0; i < 6; i++) {
        workers.at(i).join();
    }

    // Print final balance
    std::cout << "Final balance = " << act.balance << std::endl;

    return 0;
}