#include <stddef.h>
#include <stdio.h>

typedef struct list {
  int val;
  struct list *next;
} list_t;

list_t make_list(int *starting_value) {
  list_t list_node_2 = {*starting_value + 1, NULL};

  list_t list_node_1 = {*starting_value, &list_node_2};

  return list_node_1;
}

int main() {
  int val = 1;
  list_t l = make_list(&val);
  printf("First list element: %d\n", l.val);
  printf("Second list element: %d\n", l.next->val);
}
