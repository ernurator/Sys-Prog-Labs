fn main() {
    // Setting up a heap-allocated string 
    let my_str = String::from("I love CS300!");
    
    // Make a new variable that points to the string we've just set up
    let my_new_str = my_str;

    // Once we're done processing my_str, we can free it
    drop(my_str);
    
    // Print out "I love CS300!"
    println!("{:?}", my_new_str);
}

