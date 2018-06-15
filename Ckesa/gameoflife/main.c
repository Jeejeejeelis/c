#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "gameoflife.h"


Field *createField(unsigned int xsize, unsigned int ysize)
{
    (void) xsize; 
    (void) ysize;
    Field *create = malloc(sizeof( Field));
    create->xsize=xsize;
    create->ysize=ysize;
    create->cells = malloc (ysize*sizeof(State*));
    for(unsigned int j=0;j<ysize;j++)
    {
        create->cells[j] = malloc(xsize*sizeof(State));
        for(unsigned int i=0;i<xsize;i++){
            create->cells[j][i] = DEAD;
        }   
    }
    return create;   
}

void releaseField(Field *f)
{
    (void) f;
    for(unsigned int i=0;i<f->ysize;i++)
        free(f->cells[i]);
    free(f->cells);
    free (f);
}

void initField(Field *f, unsigned int n){

    (void) f;
    int xsize = f->xsize;
    int ysize = f->ysize;
    printf("%d %d\n",xsize, ysize);
    
    unsigned int i = 0;
    

    while (i<n){
        int randx = rand()%xsize;
        int randy = rand()%ysize;
        if (f->cells[randy][randx]== DEAD){
            f->cells[randy][randx]= ALIVE;
            i++;
        }
    }
    /*
    f->cells[0][0]=ALIVE;
    f->cells[0][2]=ALIVE;
    f->cells[0][3]=ALIVE;
    f->cells[0][4]=ALIVE;
    f->cells[1][1]=ALIVE;
    f->cells[1][2]=ALIVE;
    f->cells[1][6]=ALIVE;
    f->cells[3][1]=ALIVE;
    f->cells[3][3]=ALIVE;
    f->cells[3][5]=ALIVE;
    f->cells[3][6]=ALIVE;
    f->cells[4][5]=ALIVE;
    */
    
}
void printField(const Field *f){
    (void) f;
    int xsize = f->xsize;
    int ysize = f->ysize;

    for (int row=0; row<ysize; row++){
        for(int columns=0; columns<xsize; columns++)
            if (f->cells[row][columns] == DEAD){
                printf(".");
            } else {
                printf("*");
            }
            
        printf("\n");
    }
        

}

void tick(Field *f){

    (void) f;
    int xsize = f->xsize;
    int ysize = f->ysize;
    
    Field *new = createField(xsize, ysize);

    int neighbours = 0;

    //Keskusta
    for (int row=1; row<ysize-1; row++){

        for(int columns=1; columns<xsize-1; columns++){
            neighbours = 0;
            if(f->cells[row-1][columns-1]==ALIVE){
                neighbours++;
            } 
            if (f->cells[row-1][columns]==ALIVE){
                neighbours++;
            }
            if(f->cells[row-1][columns+1]==ALIVE){
                neighbours++;
            }
            if(f->cells[row][columns-1]==ALIVE){
                neighbours++;
            }
            if(f->cells[row][columns+1]==ALIVE){
                neighbours++;
            }
            if (f->cells[row+1][columns-1]==ALIVE){
                neighbours++;
            }
            if(f->cells[row+1][columns]==ALIVE){
                neighbours++;
            }
            if(f->cells[row+1][columns+1]==ALIVE){
                neighbours++;
            }
            //MITKÄ HENKIIN
            if(f->cells[row][columns]==DEAD){
                if(neighbours==3){
                    new->cells[row][columns]=ALIVE;
                }
            }
            if(f->cells[row][columns]==ALIVE){
                if(neighbours<2){
                    f->cells[row][columns]=DEAD;
                } else if (neighbours>3){
                    f->cells[row][columns]=DEAD;
                } else if (neighbours>2){
                    f->cells[row][columns]=ALIVE;
                }
            }                                   
        }
    }
    //katto ja pohja
    for (int columns = 1; columns<xsize-1; columns++){
        int neighbours = 0;
        if (f->cells[0][columns-1]== ALIVE){
            neighbours++;
        } else if (f->cells[1][columns-1]==ALIVE){
            neighbours++;
        } else if (f->cells[1][columns]==ALIVE){
            neighbours++;
        } else if (f->cells[1][columns+1]==ALIVE){
            neighbours++;
        } else if (f->cells[0][columns+1]==ALIVE){
            neighbours++;
        }

        //MITKÄ HENKIIN
        if(f->cells[0][columns]==DEAD){
            if(neighbours==3){
                new->cells[0][columns]=ALIVE;
            }
        }
        if(f->cells[0][columns]==ALIVE){
            if(neighbours<2){
                f->cells[0][columns]=DEAD;
            } else if (neighbours>3){
                f->cells[0][columns]=DEAD;
            } else if (neighbours>2){
                f->cells[0][columns]=ALIVE;
            }
        }      
    }
    for (int columns = 1; columns<xsize-1; columns++){
        int neighbours = 0;
        if (f->cells[ysize][columns-1]== ALIVE){
            neighbours++;
        } else if (f->cells[ysize-1][columns-1]==ALIVE){
            neighbours++;
        } else if (f->cells[ysize-1][columns]==ALIVE){
            neighbours++;
        } else if (f->cells[ysize-1][columns+1]==ALIVE){
            neighbours++;
        } else if (f->cells[ysize][columns+1]==ALIVE){
            neighbours++;
        }

        //MITKÄ HENKIIN
        if(f->cells[ysize][columns]==DEAD){
            if(neighbours==3){
                new->cells[ysize][columns]=ALIVE;
            }
        }
        if(f->cells[ysize][columns]==ALIVE){
            if(neighbours<2){
                f->cells[ysize][columns]=DEAD;
            } else if (neighbours>3){
                f->cells[ysize][columns]=DEAD;
            } else if (neighbours>2){
                f->cells[ysize][columns]=ALIVE;
            }
        }      

    }

    //Sivut
    for (int row = 1; row<ysize-1; row++){
        int neighbours = 0;
        if (f->cells[row-1][0]== ALIVE){
            neighbours++;
        } else if (f->cells[row-1][1]==ALIVE){
            neighbours++;
        } else if (f->cells[row][1]==ALIVE){
            neighbours++;
        } else if (f->cells[row+1][1]==ALIVE){
            neighbours++;
        } else if (f->cells[row+1][0]==ALIVE){
            neighbours++;
        }

        //MITKÄ HENKIIN
        if(f->cells[row][0]==DEAD){
            if(neighbours==3){
                new->cells[row][0]=ALIVE;
            }
        }
        if(f->cells[row][0]==ALIVE){
            if(neighbours<2){
                f->cells[row][0]=DEAD;
            } else if (neighbours>3){
                f->cells[row][0]=DEAD;
            } else if (neighbours>2){
                f->cells[row][0]=ALIVE;
            }
        }      

    }
    for (int row = 1; row<ysize-1; row++){
        int neighbours = 0;
        if (f->cells[row-1][xsize]== ALIVE){
            neighbours++;
        } else if (f->cells[row-1][xsize-1]==ALIVE){
            neighbours++;
        } else if (f->cells[row][xsize-1]==ALIVE){
            neighbours++;
        } else if (f->cells[row+1][xsize-1]==ALIVE){
            neighbours++;
        } else if (f->cells[row+1][xsize]==ALIVE){
            neighbours++;
        }

        //MITKÄ HENKIIN
        if(f->cells[row][xsize]==DEAD){
            if(neighbours==3){
                new->cells[row][xsize]=ALIVE;
            }
        }
        if(f->cells[row][xsize]==ALIVE){
            if(neighbours<2){
                f->cells[row][xsize]=DEAD;
            } else if (neighbours>3){
                f->cells[row][xsize]=DEAD;
            } else if (neighbours>2){
                f->cells[row][xsize]=ALIVE;
            }
        }      
        
    }
    

    //Kulmat
    //vasen ylä
    
    neighbours = 0;
    if (f->cells[0][1]==ALIVE){
        neighbours++;
    }
    if(f->cells[1][0]==ALIVE){
        neighbours++;
    }
    if (f->cells[1][1]==ALIVE){
        neighbours++;
    }
    
    //MITKÄ HENKIIN
    if(f->cells[0][0]==DEAD){
        if(neighbours==3){
            new->cells[0][0]=ALIVE;
        }
    }
    if(f->cells[0][0]==ALIVE){
        if(neighbours<2){
            f->cells[0][0]=DEAD;
        } else if (neighbours>3){
            f->cells[0][0]=DEAD;
        } else if (neighbours>2){
            f->cells[0][0]=ALIVE;
        }
    }
    //vasen ala
    

    neighbours = 0;
    if (f->cells[ysize][1]==ALIVE){
        neighbours++;
    }
    if(f->cells[ysize-1][0]==ALIVE){
        neighbours++;
    }
    if (f->cells[ysize-1][1]==ALIVE){
        neighbours++;
    }
       
    //MITKÄ HENKIIN
    if(f->cells[ysize][0]==DEAD){
        if(neighbours==3){
            new->cells[ysize][0]=ALIVE;
        }
    }
    if(f->cells[ysize][0]==ALIVE){
        if(neighbours<2){
            f->cells[ysize][0]=DEAD;
        } else if (neighbours>3){
            f->cells[ysize][0]=DEAD;
        } else if (neighbours>2){
            f->cells[ysize][0]=ALIVE;
        }
    }

    //oikea ylä

    
    neighbours = 0;
    if (f->cells[0][ysize-1]==ALIVE){
        neighbours++;
    }
    if(f->cells[1][ysize-1]==ALIVE){
        neighbours++;
    }
    if (f->cells[1][ysize]==ALIVE){
        neighbours++;
            }
    
    //MITKÄ HENKIIN
    if(f->cells[0][xsize]==DEAD){
        if(neighbours==3){
            new->cells[0][xsize]=ALIVE;
        }
    }
    if(f->cells[0][xsize]==ALIVE){
        if(neighbours<2){
            f->cells[0][xsize]=DEAD;
        } else if (neighbours>3){
            f->cells[0][xsize]=DEAD;
        } else if (neighbours>2){
            f->cells[0][xsize]=ALIVE;
        }
    }

    //oikea ala

    neighbours = 0;
    if (f->cells[ysize][xsize-1]==ALIVE){
        neighbours++;
    }
    if(f->cells[ysize-1][xsize-1]==ALIVE){
        neighbours++;
    }
    if (f->cells[ysize-1][xsize]==ALIVE){
        neighbours++;
    }
    
    //MITKÄ HENKIIN
    if(f->cells[ysize][xsize]==DEAD){
        if(neighbours==3){
            new->cells[ysize][xsize]=ALIVE;
        }
    }
    if(f->cells[ysize][xsize]==ALIVE){
        if(neighbours<2){
            f->cells[ysize][xsize]=DEAD;
        } else if (neighbours>3){
            f->cells[ysize][xsize]=DEAD;
        } else if (neighbours>2){
            f->cells[ysize][xsize]=ALIVE;
        }
    }
   
    
    for(int j=0;j<ysize;j++)
    {
        for(int i=0;i<xsize;i++){
            f->cells[j][i] = new->cells[j][i];
        }   
    }
    releaseField(new);
}

int main(void)
{
    /* Feel free to modify this function to test different things */

    // re-seed random number generator
    srand((unsigned)time(NULL));

    Field *f = createField(7,5);
    initField(f, 11);

    // how many iterations we want
    int rounds = 10;

    // loop iterations, cancel with ctrl-c
    for(int i=0; i<rounds; i++) {
        printf("\nGeneration: %d\n", i+1);
        printField(f);
        // slow down iterations
        usleep(500000);
        tick(f);
    }
    releaseField(f);
}
