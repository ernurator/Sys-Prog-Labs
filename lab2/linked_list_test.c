#include "linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_student_implementation() {
  // EMPTY LIST
  node_t* empty_list = NULL;

  // ONE ELEMENT LIST
  char* str1 = "systems";
  node_t* one_list = malloc(sizeof(node_t));
  one_list->data = malloc(8);
  memcpy(one_list->data, str1, 8);
  one_list->prev = NULL;
  one_list->next = NULL;

  // FOUR ELEMENT LIST
  char* check[] = {"hello", "world", "how", "cool"};
  node_t* four_list = malloc(sizeof(node_t));
  four_list->data = "hello";
  node_t* fl2 = malloc(sizeof(node_t));
  fl2->data = "world";
  node_t* fl3 = malloc(sizeof(node_t));
  fl3->data = "how";
  node_t* fl4 = malloc(sizeof(node_t));
  fl4->data = "cool";
  four_list->prev = NULL;
  four_list->next = fl2;
  fl2->prev = four_list;
  fl2->next = fl3;
  fl3->prev = fl2;
  fl3->next = fl4;
  fl4->prev = fl3;
  fl4->next = NULL;
  for (int i = 0; i < 4; i++) {
    assert(!strcmp(get(four_list, i), check[i]));
  }
  free(four_list);
  free(fl2);
  free(fl3);
  free(fl4);

  // TEST GET
  assert(!get(empty_list, 0));
  assert(!get(empty_list, 2));

  char* one_list_get = get(one_list, 0);
  assert(!strcmp(one_list_get, str1));
  assert(!get(one_list, 1));

  // TEST INSERT FIRST
  // insert to empty list
  insert_first(&empty_list, "programming");
  assert(length_list(empty_list) == 1);
  assert(!strcmp(get_first(empty_list), get_last(empty_list)));
  assert(!empty_list->prev);
  assert(!empty_list->next);

  // insert to one element list
  // computer -> systems
  insert_first(&one_list, "computer");
  assert(!strcmp(get_first(one_list), "computer"));
  assert(!one_list->prev);
  node_t* next_element = one_list->next;
  assert(next_element->prev == one_list);
  assert(!strcmp(next_element->data, "systems"));
  assert(!strcmp(get(one_list, 1), "systems"));

  // TEST REMOVE LAST
  char* removed_empty = remove_last(&empty_list);
  assert(!get_last(empty_list));
  assert(!get(empty_list, 0));
  assert(!length_list(empty_list));
  assert(!empty_list);
  assert(!remove_last(&empty_list));
  free(removed_empty);

  char* removed_one = remove_last(&one_list);

  assert(!strcmp(removed_one, "systems"));
  free(removed_one);

  assert(length_list(one_list) == 1);
  assert(!one_list->next);
  assert(!one_list->prev);
  assert(!get(one_list, 1));
  assert(!strcmp(get(one_list, 0), "computer"));
  remove_element(&one_list, "computer");
}

/**
 * test function that calls the other functions to be tested
 */
void test_linked_list() {
  // EMPTY LIST
  node_t* empty_list = NULL;

  // THREE ELEMENT LIST
  char* str1 = "test";
  node_t* new_list = malloc(sizeof(node_t));
  new_list->data = malloc(5);
  new_list->prev = NULL;
  memcpy(new_list->data, str1, 5);

  char* str2 = "test1";
  node_t* next_element = malloc(sizeof(node_t));
  next_element->data = malloc(6);
  memcpy(next_element->data, str2, 6);
  new_list->next = next_element;
  next_element->prev = new_list;

  char* str3 = "test2";
  node_t* last_element = malloc(sizeof(node_t));
  last_element->data = malloc(6);
  memcpy(last_element->data, str3, 6);
  last_element->prev = next_element;
  next_element->next = last_element;
  last_element->next = NULL;

  // TEST LENGTH
  // list with three elements
  int three_element_len = length_list(new_list);
  assert(three_element_len == 3);

  // TEST GETTING FIRST ELEMENT
  char* first_empty = get_first(empty_list);
  assert(!first_empty);

  char* first_three_elements = get_first(new_list);
  assert(!strcmp(first_three_elements, "test"));

  // TEST REMOVE FIRST
  char* removed = remove_first(&new_list);

  assert(!strcmp(removed, "test"));
  free(removed);
  // now the list looks like: test1 -> test2

  // TEST INSERT LAST AND GET LAST
  // adds the last element to new_list
  // new list would look like: test1 -> test2 -> test3
  insert_last(&new_list, "test3");
  char* last_str = get_last(new_list);
  assert(!strcmp(last_str, "test3"));

  // TEST REVERSE
  // empty list
  reverse(&empty_list);
  // three element list
  // new list would look like: test3 -> test2 -> test1
  reverse(&new_list);
  char* new_first_element = get_first(new_list);
  assert(!strcmp(new_first_element, "test3"));
  char* new_last_element = get_last(new_list);
  assert(!strcmp(new_last_element, "test1"));

  remove_element(&new_list, "test1");
  remove_element(&new_list, "test2");
  remove_element(&new_list, "test3");
}

int main(int argc, char** argv) {
  if (argc == 2) {
    if (!strcmp(argv[1], "all")) {
      printf("===Running all linked list tests===\n");
      test_linked_list();
      test_student_implementation();
      printf("\033[32mALL TESTS PASSED!\033[0m\n");
    } else if (!strcmp(argv[1], "existing")) {
      printf("===Running only existing implementation tests===\n");
      test_linked_list();
      printf("\033[32mALL EXISTING TESTS PASSED!\033[0m\n");
    } else if (!strcmp(argv[1], "student")) {
      printf("===Running only student implementation tests===\n");
      test_student_implementation();
      printf("\033[32mALL STUDENT TESTS PASSED!\033[0m\n");
    } else {
      printf("usage: <all | existing | student>\n");
    }
  } else {
    printf("usage: <all | existing | student>\n");
  }
}
