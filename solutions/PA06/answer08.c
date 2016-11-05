#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "answer08.h"

/**
 * Create a new list-node with the passed string. 
 * str should be copied (with strdup).
 */
List * List_createNode(const char * str)
{
  List * list = malloc(sizeof(List));
  if (list == NULL)
    {
      fprintf(stderr,"allocation failed\n");
    }
  list->str = strdup(str);
  list->next = NULL;
  return list;
}

/**
 * Free all memory associated with the linked list, including memory for
 * contained strings. Must safely handle NULL lists.
 */
void List_destroy(List * list)
{
  if (list == NULL) 
    return;
  free(list->str);
  List_destroy(list->next);
  free(list);
}

/**
 * Length of a linked list. 
 * The length of "NULL" is 0.
 */
int List_length(List * list)
{
  if (list == NULL) 
    return 0;
  return List_length(list->next) + 1;
}

/**
 * Merge two sorted lists to produce a final sorted list.
 * 
 * 'lhs' and 'rhs' are two sorted linked-list. Read 'left-hand-side' and 'right-
 * hand-side'. Note that either (or both) could be NULL, signifying the empty
 * list.
 * 'compar' is a function that is used to compare two nodes. This parameter is
 * similar to the parameter in qsort(...), except that it only compares two
 * strings. You can pass 'strcmp' to this function if you want to sort lists in
 * ascending order.
 *
 * When implementing this function, do not call List_createNode(...) or
 * malloc(...) Instead, think about how to build a new list by:
 * (1) Create a new (empty -- i.e., NULL) list where we build the result. You 
 *     will need to track the first and last node of this list.
 * (2) In a while-loop:
 * (2.a) Use compar to identify whether the front node of lhs or rhs is smaller.
 *       Remember that lhs or rhs could be NULL. 
 * (2.b) Move the front node of 'lhs/rhs' to the end of the result list. 
 *
 * You will need to consider what happens when 'lhs' or 'rhs' becomes NULL.
 *
 * Well-written code should be 20-30 lines long, including comments and spacing.
 * If your code is longer than this, then you may save time by rethinking your
 * approach.
 */
List * List_merge(List * lhs, List * rhs, int (*compar)(const char *, const char*))
{
	List * dummy = (List*)malloc(sizeof(List));
	dummy -> str = "dummy";
	dummy -> next = NULL;
	List * last = dummy;
	while(lhs != NULL && rhs != NULL)
	{
		if(compar(lhs -> str, rhs -> str) <= 0)
		{
			last -> next = lhs;
			lhs = lhs -> next;
		}
		else
		{
			last -> next = rhs;
			rhs = rhs -> next;
		}
		last = last -> next;
	}
	if(lhs == NULL)
	{
		last->next = rhs;
	}
	if(rhs == NULL)
	{
		last->next = lhs;
	}
	last = dummy->next;
	free(dummy);
	return last;
}

/** 
 * Sorts the list's elements using the merge-sort algorithm.
 * Merge-sort is a recursive algorithm. See the README for hints.
 * 
 * The brief instructions are as follows:
 *
 * (1) Base case: 
 * Lists of length 0 or 1 are already (defacto) sorted. In this case, return
 * 'list'.
 *
 * (2) Recursive case: 
 * (2.a) Split the linked-list into two approx. equal sized lists.
 * (2.b) Call List_sort(...) on each of these smaller lists.
 * (2.c) Call List_merge(...) to merge the now sorted smaller lists into a 
 *       single larger sorted list, which you return.
 *
 * Well-written code should be 20-30 lines long, including comments and spacing.
 * If your code is longer than this, then you may save time by rethinking your
 * approach.
 */
List * List_sort(List * list, int (*compar)(const char *, const char*))
{
  List * temp1 = NULL;
  List * temp2 = NULL;
  List * temp3 = NULL;
  List * newList = NULL;

  if ((List_length(list) == 0) || (List_length(list) == 1))
    return list;

  else
    {
      int track = 0;
      int i = 0;
      temp1 = list;
      temp2 = list;
      track = List_length(list) / 2;
      for (i = 1; i < track; i++)
	{
	  temp2 = temp2->next;
	}
      temp3 = temp2->next;
      temp2->next = NULL;
      temp1 = List_sort(temp1,compar);
      temp3 = List_sort(temp3,compar);
      newList = List_merge(temp1,temp3,compar);
    }
  return newList;
}