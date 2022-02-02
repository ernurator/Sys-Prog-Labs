// struct for a node in a doubly linked list
typedef struct node {
  char* data;

  struct node* next;
  struct node* prev;
} node_t;

// function declarations
int length_list(node_t* head_list);
char* get_first(node_t* head_list);
char* get_last(node_t* head_list);
void insert_first(node_t** head_list, char* to_add);
void insert_last(node_t** head_list, char* to_add);
char* get(node_t* head_list, int index);
int remove_element(node_t** head_list, char* to_remove);
void reverse_helper(node_t** head_list);
void reverse(node_t** head_list);
char* remove_first(node_t** head_list);
char* remove_last(node_t** head_list);
