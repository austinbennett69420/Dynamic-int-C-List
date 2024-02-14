#include <stdio.h>
#include <dynamicListIntegers.h>
/*
*solve a coding bat problem using my custom dynamic list library
*/
// the problem:
/*
*Return the sum of the numbers in the array, returning 0 for an empty array. 
*Except the number 13 is very unlucky, so it does not count and numbers that come 
*immediately after a 13 also do not count.
*/
//number after 13 and 13 does not count

int sum13(List nums) {
    if (nums.length == 0) {
        return 0;
    }
    int sum = 0;
    for (int i = 0; i < nums.length; i++) {
        if (get(nums, i) == 13) {
            i += 1;
            continue;
        }
        sum += get(nums, i);
    }
    return sum;
}

int main() {
    int test1[] = {1, 2, 2, 1, 13};
    int test2[] = {13, 1, 2, 13, 2, 1, 13};
    int test3[] = {5, 13, 2};
    int test4[] = {1, 2, 2, 1, 13, 5, 3, 6};
    List ltest1 = new_List(test1, 5);
    List ltest2 = new_List(test2, 7);
    List ltest3 = new_List(test3, 3);
    List ltest4 = new_List(test4, 5);

    printf("Awnser: %d\n", sum13(ltest1));
    printf("Awnser: %d\n", sum13(ltest2));
    printf("Awnser: %d\n", sum13(ltest3));
    printf("Awnser: %d\n", sum13(ltest4));
}