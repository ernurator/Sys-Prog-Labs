#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>

int main() {
    // Setting up a heap-allocated string
    char* temp = "I love CS300!";
    char* my_str = (char*) malloc(14);
    memcpy(my_str, temp, 14);
    
    // Make a new variable that points to the string we've just set up
    char* my_new_str = my_str;
    
    // Once we're done processing my_str, we can free it
    free(my_str);
    
    // Print out "I love CS300!"
    printf("%s", my_new_str);
    return 0;
}