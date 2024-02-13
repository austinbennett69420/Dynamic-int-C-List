#include <dynamicListIntegers.h>//if installed right you can include it like so
#include <stdio.h>


int main() {
    int temp[] = {0, 1, 2, 3, 4, 5};//create a regular array

    //usage: List mylist = new_List(int *array, initial_length)
    List list = new_List(temp, 6);//make a list with preset values with temp array

    //usage: List mylist = new_list(NULL, 0)
    List list2 = new_List(NULL, 0);//make an empty list

    //usage: printl(List obj)
    printl(list);//print a list using printl

    for (int i = 0; i < list.length; i++) {
        //usage: get(List obj, size_t index)
        //get(list, i)
        printf("Index[%d]: %d\n", i, get(list, i));//get and print every item in list
    }

    //usage: push(List *obj, int value)
    push(&list2, 15);//append something to a list by using push

    //usage: insert(List *obj, size_t index, int value)
    //insert a value at a index
    insert(&list, 1, -1);

    //usage getr(List *obj, size_t index)
    *getr(&list2, 0) = 16;//you can use this to set a value
    //getr returns a refrence to the value in a list

    //sets a value at an index
    //usage: set(List *obj, index, value)
    set(&list2, 0, 17);

    //copies values from one list to the other
    //usage: copylist(List src, List *dest)
    copyList(list, &list2);


    //copy arr converts a list back into a array
    int *arr = (int*)malloc(sizeof(int)*list.length);//appropriate mallocation

    //usage: copyArray(List src, int *dest)
    copyArray(list, arr);

    //getCopy returns a List with values between index a and b
    //usage: getCopy(List src, size_t start, size_t stop)
    List list3 = getCopy(list, 2, 4);

    //no format function instead you can use nprintl
    //nprintl prints the list without a new line
    //example:
    printf("list3: ");
    nprintl(list3);
    printf("; is values 2-3 in list");
    //usage: nprintl(List obj)

    //del_list frees the dynamic lists from memory
    //usage: del_list(List *obj)
    del_List(&list);
    del_List(&list2);
    del_List(&list3);

    free(arr);//memory management yay
}