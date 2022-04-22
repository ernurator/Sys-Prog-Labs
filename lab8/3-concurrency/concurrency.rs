use std::sync::{Mutex, Arc};
use std::sync::atomic::{AtomicBool, Ordering};
use std::thread;
        
struct Account {
    balance: Mutex<i32>
}

/************************************** HELPER FUNCTION **************************************/

/* This function initializes a very large vector (5000 elts long) containing all the changes we'd like to 
   make to the account balance. 
*/
fn make_large_vector() -> Vec<i32> {
    let mut v = vec![];
    for i in 0..5000 {
        v.push(i - 300);
    }
    return v
}

/************************************** THREAD FUNCTION **************************************/

/* This function will get passed into threads in order to modify an account with the requests. 
   Arguments: 
    - account_to_update: a reference to the account whose balance we wish to modify
    - requests: a reference to the vector containing all the requests
    - requests_fulfilled: a reference to the atomic boolean that dictates whether the threads can stop or not
*/
fn update_account(account_to_update: &Account, requests: &Mutex<Vec<i32>>, requests_fulfilled: &AtomicBool) -> () {
    while !(requests_fulfilled.load(Ordering::Relaxed)) {
        // Lock the vector containing the requests and acquire a mutex guard
        let mut requests_guard = requests.lock().unwrap();

        if (*requests_guard).len() == 0 {
            // Checks whether the requests are all fulfilled, and if so, set the boolean to true so other threads can stop
            requests_fulfilled.store(true, Ordering::Relaxed);

            // Drop mutex guard to prevent deadlock!
            drop(requests_guard);
            return
        } else {
            // Otherwise, copy the first request (via clone) so that it persists after we remove the element from the vector!
            let current_request = (*requests_guard).get(0).unwrap().clone();

            // Erase the request from the beginning of the vector and drop the mutex guard for other threads
            (*requests_guard).remove(0);
            drop(requests_guard);

            // Add the amount in the request to the account's balance
            account_to_update.balance += current_request;
        }

    }
}

/************************************** MAIN PROGRAM **************************************/

fn main() {
    // Initialize a new account (reference counted in order for the compiler to know that it won't be dropped by any function)
    let act = Arc::new(Account { balance: Mutex::new(300) });

    // Initialize vector with all the requests to add/subtract money from account
    let requests = Arc::new(Mutex::new(make_large_vector()));
    
    // Initialize atomic boolean that will get set to true when all requests have been fulfilled (so workers can stop working)
    let all_requests_fulfilled = Arc::new(AtomicBool::new(false));

     // Initialize worker pool and pass `update_account` function into threads
    let mut workers = vec![];

    for _ in 0..6 {
        let act_ref = Arc::clone(&act);
        let requests_ref = Arc::clone(&requests);
        let req_fulfilled_ref = Arc::clone(&all_requests_fulfilled);

        let worker_thread = thread::spawn(move || update_account(&*act_ref, &*requests_ref, &*req_fulfilled_ref));
        workers.push(worker_thread);
    }

    // Wait for all threads to finish
    for worker in workers {
        worker.join().unwrap();
    }

    // Print final balance
    println!("Final balance = {:?}", *(act.balance.lock().unwrap()));
}