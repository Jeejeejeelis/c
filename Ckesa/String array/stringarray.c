#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stringarray.h"

/* Exercise a: Initializes the string array to contain the initial
 * NULL pointer, but nothing else.
 * Returns: pointer to the array of strings that has one element
 *      (that contains NULL)
 */
char **init_string_array(void)
{
	char** arr = malloc(sizeof(NULL));
	*arr = NULL;
	return arr;
}

/* Releases the memory used by the strings.
 */
void release_string_array(char **arr)
{
	char* string = arr[0];
	size_t i;
	i = 0;
	while(string != NULL){
		i++;
		free(string);
		string = arr[i];
	}
	free(arr);
}

/* Exercise b: Add <string> to the end of array <array>.
 * Returns: pointer to the array after the string has been added.
 */
char **insert_string(char **arr, const char *str)
{
	size_t i;
	for(i = 0; arr[i] !=NULL; i++);

	char **array = realloc(arr, (i+2) * sizeof(char*));

	array[i]=malloc((strlen(str) + 1) * sizeof(char));
	strcpy(array[i], str);

	array[i + 1] = NULL;

	return array;
}


/* Exercise c: reorder strings in <array> to lexicographical order */
void sort_string_array(char **arr)
{
	size_t max;

	for(max = 0; arr[max] != NULL; max++);

	for (size_t i = 0; i<max; i++){
		if (strcmp(arr[0],arr[i])>0) {
			char* uusi = arr[i];
			arr[i] = arr[0];
			arr[0] = uusi;
		}
	}

	if (max > 1){
		sort_string_array(arr + 1);
	}
}

/* You can use this function to check what your array looks like.
 */
void print_string_array(char **arr)
{
    if (!arr)
        return;
    while (*arr) {
        printf("%s  ", *arr);
        arr++;
    }
    printf("\n");
}

int main(void)
{
    char **string_array = init_string_array();
    
    string_array = insert_string(string_array, "oNe");
    string_array = insert_string(string_array, "TWO");
    string_array = insert_string(string_array, "three");
    string_array = insert_string(string_array, "Four");
    
    print_string_array(string_array);
    
    //make_lower(string_array);
    sort_string_array(string_array);
    
    print_string_array(string_array);
    release_string_array(string_array);
    
    return EXIT_SUCCESS;
}

