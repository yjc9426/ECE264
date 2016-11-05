#include "answer06.h"
#include <stdio.h>
#include <stdlib.h>


SparseNode * MergeCopy(SparseNode * new_array, SparseNode * array);
SparseNode * MergeInsert( SparseNode * array, int index, int value );



SparseNode *SparseNode_create(int index, int value)
{
  SparseNode * node = malloc(sizeof(SparseNode));
  
  node -> index = index;
  node -> value = value;
  
  node -> left = NULL;
  node -> right = NULL;
  
  return node;
}


SparseNode * SparseArray_insert ( SparseNode * array, int index, int value )
{
  if(value == 0)
    return array;
  
  if(array == NULL) 
    return SparseNode_create(index, value); 
  
  if((array -> index) == index)
    {
      (array -> value) = value;  
      return array;
    }
  
  if((array -> index) > index)
    {
      (array -> left) = SparseArray_insert(array -> left, index, value); 
      return array;
    }
  else
       (array -> right) = SparseArray_insert(array -> right, index, value); 
  
  return array;
}


SparseNode *SparseArray_build(int * indicies, int * values, int length)
{
  SparseNode * array = NULL;  
  int i;
  
  for(i = 0; i < length; i++)
    {
      array = SparseArray_insert(array, indicies[i], values[i]); 
    }
  
  return array;
}


void SparseArray_destroy ( SparseNode * array )
{
  if(array == NULL)  // If empty, free pointer
    {
      free(array);
      return;
    }
  SparseArray_destroy(array -> left);  
  SparseArray_destroy(array -> right);
  free(array);
}


int SparseArray_getMin ( SparseNode * array )
{
	if( array == NULL){
		fprintf(stderr,"%s","arrary is null");
		return array->index;
	}
	if(array -> left == NULL)
		return array->index;
	return SparseArray_getMin( array -> left);
}


int SparseArray_getMax ( SparseNode * array )
{
	if( array == NULL){
		fprintf(stderr,"%s","arrary is null");
		return array->index;
	}
	if(array -> right == NULL)
		return array->index;
	return SparseArray_getMax( array -> right);
}


SparseNode * SparseArray_getNode(SparseNode * array, int index )
{
  if(array == NULL)  // End of array
    return NULL;
  
  if((array -> index) == index) 
    {
      return array;
    }
      
  if((array -> index) > index) 
    return SparseArray_getNode(array -> left, index);
  else
    return SparseArray_getNode(array -> right, index);  
}


SparseNode * SparseArray_remove ( SparseNode * array, int index )
{
  if(array == NULL)
    return array;
  
  else if ((array -> index) > index)
    {
      array -> left = SparseArray_remove(array->left, index);
      return array;
    }

  else if ((array -> index) < index)
    {
      array -> right = SparseArray_remove(array->right, index);
      return array;
    }
  

  else{
    if((array -> left) == NULL && array -> right == NULL)
      {
          free(array);
          return NULL;
        }
      else if( array -> left == NULL)        {
          SparseNode * temp = array -> right;
          free(array);
          return temp;
        }
      else if((array -> right) == NULL) 
    {
      SparseNode * temp = array -> left;  
      free(array);
      return temp;
    }
  
  else
  {
  SparseNode * temp = (array -> right);  // Look within right half from target node
  
  while((temp -> left) != NULL)  // Find left-most node in that right half ^^
    temp = (temp -> left);
  
  int value = (array -> value);
  (array -> index) = (temp -> index);
  (array -> value) = (temp -> value);
  (temp -> index) = index;
  (temp -> value) = value;
  (array -> right) = SparseArray_remove(array -> right, index); 
  }
  }
  return array;
}


SparseNode * SparseArray_copy(SparseNode * array)
{
  if(array == NULL)
    return NULL;
  SparseNode * copy = NULL;
  copy = SparseArray_insert(copy, array -> index, array -> value);
  (copy -> left) = SparseArray_copy(array -> left);
  (copy -> right) = SparseArray_copy(array -> right);
  
  return copy;
}


SparseNode * SparseArray_merge(SparseNode * array_1, SparseNode * array_2)
{
  int index;
  int min;
  int max;
  
  if(array_1 == NULL)
    return array_2;
  
  if(array_2 == NULL)
    return array_1;
  
  SparseNode * new_array = SparseArray_copy(array_1);  // Make copy of array_1
  new_array = MergeCopy(new_array, array_2);  // Merge array_2 values into copy
  
  min = SparseArray_getMin(new_array);
  max = SparseArray_getMax(new_array);
  
  for(index = min; index <= max; index++)
    {
      if (SparseArray_getNode(new_array, index) && (SparseArray_getNode(new_array, index) -> value == 0))
	new_array = SparseArray_remove(new_array, index);
    }
  
  return new_array;
}


SparseNode * MergeCopy(SparseNode * new_array, SparseNode * array)
{
  if(array == NULL)
    return new_array;
  
  new_array = MergeInsert(new_array, array -> index, array -> value);
  new_array = MergeCopy(new_array, array -> left);
  new_array = MergeCopy(new_array, array -> right);
  return new_array;
}

SparseNode * MergeInsert( SparseNode * array, int index, int value )
{
  if(value == 0) 
    return array;
  
  if(array == NULL)  
   // free(array);
    return SparseNode_create(index, value);  
  
  if((array -> index) == index)
    {
      (array -> value) += value; 
      return array;
    }
  
  if((array -> index) > index)
    {
      (array -> left) = MergeInsert(array -> left, index, value);  // Move to left side
      return array;
    }
  
  (array -> right) = MergeInsert(array -> right, index, value);  // Move to right side
  
  return array;
}


