use crossbeam::channel::{self, Receiver};
use std::sync::{Arc, Mutex};
use std::thread;

static NUM_THREADS: i32 = 3;

#[derive(Debug, Clone)]
enum Transaction {
    Deposit,
    Withdraw,
}

#[derive(Debug, Clone)]
struct Request {
    transaction: Transaction,
    amount: i32,
}

struct Account {
    balance: i32,
}

fn main() {
    let account = Arc::new(Mutex::new(Account { balance: 0 }));

    let requests = vec![
        Request {
            transaction: Transaction::Deposit,
            amount: 10,
        },
        Request {
            transaction: Transaction::Withdraw,
            amount: 20,
        },
        Request {
            transaction: Transaction::Deposit,
            amount: 30,
        },
        Request {
            transaction: Transaction::Withdraw,
            amount: 40,
        },
        Request {
            transaction: Transaction::Deposit,
            amount: 50,
        },
        Request {
            transaction: Transaction::Withdraw,
            amount: 60,
        },
    ];

    // Channels have two endpoints: the `Sender` and `Receiver`. Channels must
    // be specialized to send a specific type of value, in this case a `Request`.
    // This channel is a multi-producer, multi-consumer (or MPMC) channel, which means many
    // threads can send to it and many threads can receive from it. For this case, we'll
    // have one sender and many receivers.
    let (sender, receiver) = channel::unbounded();

    let mut children = Vec::new();
    for _ in 0..NUM_THREADS {
        // each thread needs a reference to the account.
        let account_ref_for_this_thread = account.clone();

        // 1) FIXME: Each thread needs to be able to access the receiving end of the channel,
        // but the code below doesn't work. How can we make sure each thread has access to
        // the receiving end of the channel, without losing ownership in the main thread?
        // Fix the below code, and be prepared to explain your fix.
        // Hint: the spawn function takes a closure as an argument. A closure is like a function;
        // however, a closure has access to all variables from the scope in which it is called.
        // This example uses a move closure, which is a special kind of closer that forces ownership 
        // over the variables the closure captures. This means that if a move closure 
        // calls a function, it gains ownership over all variables that function uses.
        let child =
            thread::spawn(move || process_requests(&*account_ref_for_this_thread, receiver));

        children.push(child);
    }

    // Queue every element of the `requests` vector in the channel so the workers can
    // start pulling requests off and processing them.
    for request in requests {
        let b = request;
        sender.send(b).unwrap();
    }

    // 2) FIXME: What is error here? Why is it a bad idea to print the requests vector after
    // we've sent it's elements into the channel? Make sure you're able to explain the answer
    // to this question when a TA comes to check you off.
    // Note: you can comment this line out to get the code to compile.
    println!("Processing the following requests: {:?}", requests);

    // 3) TODO: close the `sender` end of the channel so that the workers know no more requests
    // will arrive.
    // Tip: closing the channel is equivalent to calling the destructor of `sender`. There is
    // a function in rust that you can call on any value to activate it's destructor behavior.
    // Check back over previous sections to find the correct function.

    for child in children {
        child.join().expect("oops! the child thread panicked");
    }

    // Print the results to check the final bank balance.
    println!("Final balance: {:?}", account.lock().unwrap().balance);
    println!("Expected final balance: -30");
}

fn process_requests(account: &Mutex<Account>, receiver: Receiver<Request>) {
    // loop is a equivalent to `while true` in other languages.
    loop {
        // `match` is like `switch` in C/C++, it lets us do something different
        // depending on whether `receiver.recv()` is an error or a value
        match receiver.recv() {
            Ok(request) => match request.transaction {
                Transaction::Deposit => {
                    let mut account = account.lock().unwrap();
                    account.balance += request.amount;
                }
                Transaction::Withdraw => {
                    let mut account = account.lock().unwrap();
                    account.balance -= request.amount;
                }
            },
            Err(_) => {
                // This branch represents the case when there are no more requests
                // waiting in the channel and the sender has closed, indicating that no
                // more requests need to be sent. We can break out of the loop.
                break;
            }
        }
    }
}
