#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef DynamicListIntegers_H
#define DynamicintListIntegers_H




typedef struct{
	int *array;//array size
	size_t size;//not the physical size but the max length it can be before needing to realloc()
	size_t length;//the current length of the array
}List;

List new_List(int *array, int init_length) {
	/*
	*create a new list object of size, init_size and with values in "array"
	*also converts an array into a list, use NULL to create a list with no value
	*/
	
	List list;//create list
	
	list.array = (int*)malloc(sizeof(int)*(init_length+5));//malloc the initial size
	
	list.size = ((sizeof(int)*init_length)/sizeof(int))+5;// set the max size
	list.length = init_length;//set the length
	
	for (int i = 0; i<list.length; i++) {
		list.array[i] = array[i];//set the array items
	}
	return list;//return the list
}





int get(List obj, size_t index) {
	/*
	*return the value at index in obj
	*/

	
	if (index < obj.length) {//check if index is within bounds
		return obj.array[index];//return the value
	} else {
		//print err if it is out of bounds
		fprintf(stderr, "index out of bounds error\nindex: %zu is not less than length: %zu\nUsage: get(List, size_t)", index, obj.length);
		exit(1);
	}
}

int *getr(List *obj, size_t index) {
	/*
	*get a refrence to the value at index in obj
	*can be used instead of set by doing *getr(obj, index) = value;
	*/

	
	if (index < obj->length) {//also check if its in bounds
		return &obj->array[index];//return a refrence to the value in memory
	} else {
		//print stderr
		fprintf(stderr, "index out of bounds error\nindex: %zu is not less than length: %zu\nUsage: getr(List*, size_t)", index, obj->length);
		exit(1);
	}
}








void push(List *obj, int a) {
	/*
	*append a value to the end of obj
	*/
	
	if (obj->length == obj->size) {//check if we need to realloc our list

		//temp variable for storing the list
		int *temp = (int*)malloc(sizeof(int)*obj->size);

		//copy the items to temp
		memcpy(temp, obj->array, sizeof(int)*obj->size);

		//realloc the array; increases the size by a total of 5
		obj->array = realloc(obj->array, (sizeof(int)*(obj->size + 5)));
		//cpy the items in temp back to the array
		memcpy(obj->array, temp, obj->size-5);
		//increase size variable for size tracking
		obj->size += 5;

		//free temp variable
		free(temp);
	}
	obj->array[obj->length] = a;//set the last index to a
	//increase the length by 1
	obj->length++;
}







void printl(List obj) {
	/*
	*print the list with a newline at the end (use nprintl for without a new line)
	*/

	if (obj.length == 0) {//check if the list is of length 0
		printf("\n");
		return;
	}
	
	
	for (int i = 0; i < obj.length-1; i++) {
		printf("%d, ", get(obj, i));
		/* for each item in array except the last one print "i, " */
		
	}
	printf("%d\n", get(obj, obj.length-1));
	//print the last item
}

void nprintl(List obj) {
	/*
	*print the list (use printl to add a new line at the end)
	*/

	if (obj.length == 0) {//check if the list is of length 0
		printf("\n");
		return;
	}


	for (int i = 0; i < obj.length-1; i++) {
		printf("%d, ", get(obj, i));
		/*
		*for each item in array except the last one print "i, " 
		*/

	}
	printf("%d", get(obj, obj.length-1));
	//print the last item
}





void del_List(List *obj) {
	/*
	*free the memory used by the list (list is now unusable)
	*/
	free(obj->array);//free the array
	obj->length = 0;
	obj->size = 0;
}





void insert(List *obj, size_t index, int a) {
	/*
	*insert a value at index, moves the previous value and all values after it to the right
	*/

	if (obj->length == obj->size) {//check if we need to realloc the array
		//temp variable for storing the list
		int *temp = (int*)malloc(sizeof(int)*obj->size);

		//copy the items to temp
		memcpy(temp, obj->array, sizeof(int)*obj->size);

		//realloc the array; increases the size by a total of 5
		obj->array = realloc(obj->array, (sizeof(int)*(obj->size + 5)));
		//cpy the items in temp back to the array
		memcpy(obj->array, temp, obj->size-5);
		//increase size variable for size tracking
		obj->size += 5;

		//free temp variable
		free(temp);
	}
	for (int i = obj->length; i > index; i--) {
			obj->array[i] = obj->array[i-1];//move the previous items to the right
	}
	obj->array[index] = a;//set the index to a
	obj->length ++;//increase the length variable
}





void set(List *obj, size_t index, int value) {
	*getr(obj, index) = value;
}





void set_size(List *obj, size_t size) {
	/*
	*set the size of the list
	*setting the size to be lower than the length may cause some values to be lost
	*/
	//temp variable for storing the list
	int *temp = (int*)malloc(sizeof(int)*obj->size);

	//copy the items to temp
	memcpy(temp, obj->array, sizeof(int)*obj->size);

	//realloc the array; set the size
	obj->array = realloc(obj->array, (sizeof(int)*size));
	//cpy the items in temp back to the array
	memcpy(obj->array, temp, obj->size-5);
	//increase size variable for size tracking
	obj->size = size;
	if (obj->size < obj->length) {
		obj->length = obj->size;
	}

	//free temp variable
	free(temp);
}





void copyList(List src, List *dest) {
	/*
	*copy the items from one list to another
	*/
	del_List(dest);
	*dest = new_List(src.array, src.length);
}

void copyArray(List src, int *dest) {
	/*
	*copy all the items from src to dest
	*dest must be malloced before copying
	*also can be used to convert a list into an array
	*/

	for (int i = 0; i < src.length; i++) {
		dest[i] = get(src, i);
	}
}

List getCopy(List src, size_t start, size_t stop) {
	if (start >= 0 && stop <= src.length) {
		List ret = new_List(NULL, 0);
		for (int i = start; i < stop; i++) {
			push(&ret, get(src, i));
		}
		return ret;
	} else {
		fprintf(stderr, "Error: range %zu-%zu is not within bounds 0-%zu", start, stop, src.length);
		exit(1);
	}
}


#endif
