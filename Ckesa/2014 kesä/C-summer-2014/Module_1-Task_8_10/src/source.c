#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "source.h"

/* Don't touch the definition of msgs array! Checker uses this. */
char *msgs[10] = {
    "'6=*w+~)._", "J65+~5+~=0/*69,~+9;,9*~19++=79"
};

/* Exercise 1.8 */
void ascii_chart(char min, char max)
{
    char laskuri = 1;
    char i;
    for(i = min; i <= max; i++)
    {
        char printattava;
        if(isprint(i))
            printattava = i;
        else
            printattava = '?';
        
        printf("%3d 0x%02x %c",i,i,printattava);
        
        if(laskuri % 4 != 0)
            printf("\t");
        else
            printf("\n");
        
        laskuri ++;
    }
}

char get_character(int msg, unsigned int cc) {
    if (msg >= 10 || !msgs[msg])
        return 0;

    if (strlen(msgs[msg]) <= cc)
        return 0;
    
    return msgs[msg][cc];
}

/* Exercise 1.9 */
void secret_msg(int msg)
{
    unsigned int cc;
    for(cc = 0; get_character(msg, cc) != 0; cc++)
    {
        char salattu = get_character(msg,cc);
        char avattu = 158 - salattu;
        printf("%c",avattu);
    }
}


float calculator(void)
{
    int luettuja;
    float eka, toka;
    char op;
    char sulkuko;
    
    luettuja = scanf("%f", &eka);
    if(luettuja == 0)
    {
        scanf("%c", &sulkuko);
        if(sulkuko == '(')
        {
            eka = calculator();
            scanf("%c", &sulkuko);
            if(sulkuko != ')')
                return 0.0 / 0.0;
        }
        else
            return 0.0 / 0.0;
        
    }
    
    scanf(" %c ", &op);
    
    luettuja = scanf("%f", &toka);
    if(luettuja == 0)
    {
        scanf("%c", &sulkuko);
        if(sulkuko == '(')
        {
            toka = calculator();
            scanf("%c", &sulkuko);
            if(sulkuko != ')')
                return 0.0 / 0.0;
        }
        else
            return 0.0 / 0.0;
        
    }
    
    if(op == '+')
        return eka + toka;
    else if(op == '-')
        return eka - toka;
    else if(op == '*')
        return eka * toka;
    else if(op == '/')
        return eka / toka;
    else
        return 0.0 / 0.0;
}
