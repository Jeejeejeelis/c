#include <stdio.h>
#include "source.h"

int main()
{
    /* Testing 2.5: Sort. Implement a function to print
     * the resulting array to see that it really works */ 
    int arr[] = {3, 4, 7, 2, 8};
    sort(arr, 5);
    printf("%d %d %d %d %d\n",arr[0],arr[1],arr[2],arr[3],arr[4]);

    /* Testing 2.6: Count alpha */
    char *str = "How many alpha in this string?";
    printf("count_alpha: %d\n", count_alpha(str));

    /* Testing 2.7: Count substr */
    char str2[] = "twoone two one twoonetwo three";
    printf("count_substr: %d\n", count_substr(str2, "two"));
    
    /* Testing 2.8: Remove substr */
    char str3[] = "a b a b b b c d";
    remove_substr(str2, "one");
    printf("remove_substr: %s\n", str2);
    remove_substr(str3, "b");
    printf("remove_substr: %s\n", str3);
    
    return 0;
}
