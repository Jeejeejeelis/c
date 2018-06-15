#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

char **init_string_array(void)
{
    char** arr = malloc(sizeof(NULL));
    *arr = NULL;
    return arr;
}

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

void print_string_array(char **arr)
{
    if (!arr)
        return;
    while (*arr) {
        printf("%s", *arr);
        arr++;
    }
    printf("\n");
}

int main(void)
{
    printf("------------------------------\n");
    printf("Käytettävissä olevat komennot:\n\n");
    printf("[Lisää koe-eläin]:A nimi paino\n");
    printf("[Tulosta eläimet]:L\n");
    printf("[Poistu ohjelmasta]:Q\n");
    printf("------------------------------\n");


    char **string_array = init_string_array();

    int i = 0;
    while(1){
        i = 0;
        char *str, c = '\0';
        int i = 0, j = 1;

        str = (char*)malloc(sizeof(char));

        printf("Anna komento : ");

        while (c != '\n') {
            c = getc(stdin);

            str = (char*)realloc(str, j * sizeof(char));

            str[i] = c;

            i++;
            j++;
        }

        str[i] = '\0'; 

        char *b = NULL;
        b = &str[2];
        
        switch(str[0]) {
            case 'A' :
                if (isspace(b[0])){
                    printf("Virheellinen syöte!");
                    break;
                } else{
                    string_array = insert_string(string_array, b);
                    printf("Eläin lisätty!\n");
                }
                break;
            case 'B' :
            printf("Bcase\n");
            /*
            Ei toimi vielä....
                
                i = 0;
                j = 1;
                while(!isspace(b[i])){
                    animal = (char*)realloc(animal, j * sizeof(char));
                    animal[i] = b[i];
                    i++;
                    j++;
                }
                while(*string_array!=NULL){
                    printf("TESTI%s", *string_array);
                    if(strstr(*string_array, animal) != NULL) {
                        printf("Eläin Löytyi!\n");
                        //free(animal);
                        
                    } 
                    string_array++;
                }
                free(animal);
                */

                                               
                break;

            case 'D' :
                printf("Dcase\n");
                break;
            case 'E' :
                printf("Ecase\n");
                break;
            case 'L' :
                printf("Olemassa olevat eläimet:\n");
                print_string_array(string_array);
                break;
            case 'W' :
                printf("Wcase\n");
                break;
            case 'O' :
                printf("Ocase\n");
                break;
            case 'Q' :
                printf("Ohjelma päättyi!\n");
                break;
            default:
                printf("Virheellinen syöte!\n");
                break;
                       
        }
       
        if (str[0]=='Q'){
            free(str);
            release_string_array(string_array);
            break;
        }
        free(str);
    }
}