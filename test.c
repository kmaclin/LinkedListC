#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Here we are going to write some functions to support a linked list that stores
 * Person data (name, age)
 */
typedef struct person_t
{
    char* name;
    int age;
} Person;

/* Example functions given to you. If you want to truly grasp these concepts, try
 * writing your own structs and functions as well!
 */

// Create a new Person
Person* create_person(const char* name, int age)
{
    Person* p = (Person*) malloc(sizeof(Person));
    p->name = strdup(name);
    p->age = age;
    return p;
}

// Make a deep copy of a Person
void* copy_person(const void* data)
{
    Person *p = (Person*) data;
    return create_person(p->name, p->age);
}

// Print a Person
void print_person(void* data)
{
    Person *p = (Person*) data;
    printf("%s, %d\n", p->name, p->age);
}

// Free a Person
void free_person(void* data)
{
    Person *p = (Person*) data;
    // free any malloc'd pointers contained in the Person struct
    free(p->name);
    free(p);
}

// Return 1 if the person's name is 8+ characters long
int long_name(const void *data)
{
	Person *p = (Person*) data;
	return strlen(p->name) > 7;
}

/* This main function does a little testing
   Like all good CS Majors you should test
   your code here. There is no substitute for testing
   and you should be sure to test for all edge cases
   e.g., calling remove_front on an empty list.
*/
int main(void)
{
	/* Now to make use of all of this stuff */
	list* llist = create_list();

  	/* What does an empty list contain?  Lets use our handy traversal function */
  	printf("TEST CASE 1\nAn Empty list should print nothing here:\n");
  	traverse(llist, print_person);
	printf("\n");

 	/* Lets add a person and then print */
 	push_front(llist, create_person("Andrew", 24));
 	printf("TEST CASE 2\nA List with one person should print that person:\n");
 	traverse(llist, print_person);
 	printf("\n");

 	/* Lets remove that person and then print */
 	remove_front(llist, free_person);
 	printf("TEST CASE 3\nAnother Empty list should print nothing here:\n");
 	traverse(llist, print_person);
 	printf("\n");

 	/* Lets add two people and then print */
 	push_front(llist, create_person("Nick", 22));
 	push_front(llist, create_person("Randal", 21));
 	printf("TEST CASE 4\nA List with two people should print those two people:\n");
 	traverse(llist, print_person);
 	printf("\n");

	/* Lets copy this list */
	list* llist2 = copy_list(llist, copy_person);
	printf("TEST CASE 5\nA copied list should print out the same two people:\n");
 	traverse(llist2, print_person);
 	printf("\n");

  	/* Lets kill the list */
  	empty_list(llist, free_person);
 	printf("TEST CASE 6\nAfter freeing all nodes the list should be empty:\n");
 	traverse(llist, print_person);
	printf("\n");

	/* Let's make a list of people, and remove certain ones! */
	/* Should remove anyone whose name is 8+ characters long */
	push_front(llist, create_person("Josephine", 27));
	push_front(llist, create_person("Dave", 34));
	push_front(llist, create_person("Benjamin", 23));
	push_front(llist, create_person("Lisa", 41));
	push_front(llist, create_person("Maximilian", 24));
	remove_if(llist, long_name, free_person);
	printf("TEST CASE 7\nShould only print 2 people with short names:\n");
	traverse(llist, print_person);

 	/* YOU ARE REQUIRED TO MAKE MORE TEST CASES THAN THE ONES PROVIDED HERE */
 	/* You will get points off if you do not you should at least test each function here */
  /*test*/

  //tests push_back
  empty_list(llist, free_person);
  push_back(llist, create_person("Josephine", 27));
  push_back(llist, create_person("Dave", 34));
  printf("\nTEST CASE 9\nShould print 2 people\n");
  traverse(llist, print_person);

  //tests is_empty on an empty list and a list with items
  empty_list(llist, free_person);
  printf("\nTEST CASE 10a\nShould print 1 for this empty list\n");
  int empty = is_empty(llist);
  printf("%d\n\n", empty);

  push_back(llist, create_person("Josephine", 27));
  printf("\nTEST CASE 10b\nShould print 0 for this list of 1 person\n");
  empty = is_empty(llist);
  printf("%d\n\n", empty);

  //tests size function
  empty_list(llist, free_person);
  push_front(llist, create_person("Benjamin", 23));
  push_front(llist, create_person("Lisa", 41));
  push_front(llist, create_person("Maximilian", 24));
  printf("\nTEST CASE 11a\nShould print 3 for this list\n");
  int s = size(llist);
  printf("%d\n\n", s);

  empty_list(llist, free_person);
  printf("\nTEST CASE 11b\nShould print 0 for this list\n");
  s = size(llist);
  printf("%d\n\n", s);

  //tests front, back, remove_front, remove_back
  push_front(llist, create_person("Lisa", 41));
  push_front(llist, create_person("Maximilian", 24));
  printf("\nTEST CASE 12\nShould print the list\n");
  traverse(llist, print_person);
  printf("\nTEST CASE 12a\nShould print the front\n");
  print_person(front(llist));
  printf("\nTEST CASE 12b\nShould print the back\n");
  print_person(back(llist));
  printf("\nTEST CASE 12c\nEmpties list. Adds a person. Checks front/back with 1 person - front and back should be equal.\n");
  empty_list(llist, free_person);
  push_front(llist, create_person("Lisa", 41));
  printf("front: ");
  print_person(front(llist));
  printf("back: ");
  print_person(back(llist));
  printf("\nTEST CASE 12d\nEmpties list and checks front/back.\n");
  empty_list(llist, free_person);
  s = size(llist);
  printf("size: %d\n", s);
  if (front(llist) == NULL)
  {
      printf("\nfront is NULL. Passed.\n");
  }
  else
  {
      printf("\nfront is not NULL. Failed.\n");
  }
  if (back(llist) == NULL)
  {
      printf("\nback is NULL. Passed.\n");
  }
  else
  {
      printf("\nback is not NULL. Failed.\n");
  }
  printf("\n");

  //test remove_front and remove_back
  empty_list(llist, free_person);
  push_front(llist, create_person("Josephine", 27));
  push_front(llist, create_person("Dave", 34));
  push_front(llist, create_person("Benjamin", 23));
  push_front(llist, create_person("Lisa", 41));
  push_front(llist, create_person("Maximilian", 24));
  printf("\nTEST CASE 13\nShould print the list with the top and bottom people\n");
  printf("complete list:\n\n");
  traverse(llist, print_person);
  int success = remove_front(llist, free_person);
  printf("\nremove front and back should return 0 if successful");
  printf("\nremove_front: %d\n", success);
  success = remove_back(llist, free_person);
  printf("remove_back: %d\n", success);
  traverse(llist, print_person);
  printf("\nTEST CASE 13\nShould both print -1 for an empty list and an error message\n");
  empty_list(llist, free_person);
  success = remove_front(llist, free_person);
  printf("\nremove_front: %d\n", success);
  success = remove_back(llist, free_person);
  printf("\nremove_back: %d\n\n", success);

  //test remove_if
  empty_list(llist, free_person);
  push_front(llist, create_person("Dave", 34));
  push_front(llist, create_person("Lisa", 41));
  int count = remove_if(llist, long_name, free_person);
  printf("\nTEST CASE 14a\nShould remove no one and print 2 people\n");
  traverse(llist, print_person);
  printf("number removed: %d\n", count);
  printf("\nTEST CASE 14b\nShould remove one person and print the other\n");
  empty_list(llist, free_person);
  push_front(llist, create_person("Dave", 34));
  push_front(llist, create_person("Maximilian", 24));
  count = remove_if(llist, long_name, free_person);
  printf("number removed: %d\n", count);
  traverse(llist, print_person);
  printf("front: ");
  print_person(front(llist));
  printf("back: ");
  print_person(back(llist));
  printf("\nadds someone to back just to check head and tail pointers.\n");
  push_back(llist, create_person("Maximilian", 24));
  traverse(llist, print_person);
  printf("front: ");
  print_person(front(llist));
  printf("back: ");
  print_person(back(llist));
  printf("\nTEST CASE 14c\nShould return 0 due to emptiness\n");
  empty_list(llist, free_person);
  count = remove_if(llist, long_name, free_person);
  printf("number removed: %d\n", count);
  
  //test copy_list
  empty_list(llist, free_person);
  printf("\nTEST CASE 15a\nShould print error message: empty list.");
  copy_list(llist, copy_person);
  printf("\n");

  push_front(llist, create_person("Dave", 34));
  printf("\nTEST CASE 15b\nTest copy_list with 1 person and add another to new list as well as create_list.\n");
  printf("\nOriginal list: \n");
  traverse(llist, print_person);
  list* l = copy_list(llist, copy_person);
  if (l == NULL)
  {
      printf("error in create_list.");
  }
  printf("\nNew list: \n");
  traverse(l, print_person);
  push_front(l, create_person("Benjamin", 23));
  printf("\nnew list after copying and adding a person: \n");
  traverse(l, print_person);
  printf("\nold list: \n");
  traverse(llist, print_person);


 	/* Testing over clean up*/
	empty_list(llist, free_person);
 	free(llist);
	empty_list(llist2, free_person);
	free(llist2);

  return 0;
}

