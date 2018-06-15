#include <stdio.h>
#include <stdlib.h>
#include "minesweeper.h"

/* Print the current state of the field */
void printField(const Field *f)
{
    unsigned int i, j;
    for (i = 0; i < f->ysize; i++) {
        for (j = 0; j < f->xsize; j++) {
            char c = '.';
            int d = 0;
            switch (f->places[i][j]) {
                case UNKNOWN_FREE:
                case UNKNOWN_MINE:
                    c = '?';
                    break;
                    
                case KNOWN_MINE:
                    c = '*'; break;
                    
                case KNOWN_FREE:
                    d = countNeighbours(f, j, i);
                    c = '.';
                    break;
            }
            if(d != 0)
                printf("%d ", d);
            else
                printf("%c ", c);
        }
        printf("\n");
    }
}


/* Deploy mines to random locations in the given field
 * 
 * Parameters:
 * f: Minefield that has been created earlier
 * mines: number of mines to be deployed */
void deployMines(Field *f, unsigned int mines)
{
    unsigned int i;
    for (i = 0; i < mines; i++) {
        int x, y;
        do {
            x = rand() % f->xsize;
            y = rand() % f->ysize;
        } while(f->places[y][x] != UNKNOWN_FREE);
        
        f->places[y][x] = UNKNOWN_MINE;
    }
}


/* Create new field with given dimensions
 * 
 * Parameters:
 * xsize: horizontal size of the field
 * ysize: vertical size of the field
 * 
 * Returns:
 * Pointer to the newly allocated minefield */
Field *createField(unsigned int xsize, unsigned int ysize)
{
    Field* field = malloc(sizeof(Field));
    field->xsize = xsize;
    field->ysize = ysize;
    
    field->places = malloc(ysize * sizeof(State*));
    size_t i,j;
    for(j = 0; j < ysize; j++)
    {
        field->places[j] = malloc(xsize * sizeof(State));
        for(i = 0; i < xsize; i++)
        {
            field->places[j][i] = UNKNOWN_FREE;
        }
    }
    return field;
}

/* Checks the status of given location. At the same time, change the
 * status from UNKNOWN_MINE to KNOWN_MINE, or UNKNOWN_FREE to KNOWN_FREE
 * 
 * Parameters:
 * f: Minefield that has been allocated earlier
 * x, y: the coordinates of the place to be checked
 * 
 * Returns:
 * 1 if there was a mine; 0 if the location was free; -1 if given
 * coordinates are out of bounds */
int checkPlace(const Field *f, unsigned int x, unsigned int y)
{
    if(f->xsize < x || f->ysize < y)
        return -1;
    State s = f->places[y][x];
    if(s == UNKNOWN_FREE || s == KNOWN_FREE)
    {
        f->places[y][x] = KNOWN_FREE;
        return 0;
    }
    if(s == UNKNOWN_MINE || s == KNOWN_MINE)
    {
        f->places[y][x] = KNOWN_MINE;
        return 1;
    }
    return -1;
}

/* Count how many of the neighboring locations have mines.
 * 
 * Parameters:
 * f: pointer to the field allocated earlier
 * x, y: coordinates of the place to be checked
 * 
 * Returns:
 * Number of mines in the neighborhood. At maximum there are 8 neighboring
 * locations. */
int countNeighbours(const Field *f, unsigned int x, unsigned int y)
{
    char count = 0;
    size_t xmax = f->xsize - 1;
    size_t ymax = f->ysize - 1;
    State** p = f->places;
    
    if(x > xmax || y > ymax)
        return -1;
    
    if(y != ymax && 
       x != 0 && 
       (p[y + 1][x - 1] == KNOWN_MINE || 
        p[y + 1][x - 1] == UNKNOWN_MINE)
      )
    {
        count += 1;  // ylävasen
    }
    
    if(y != ymax &&
       (p[y + 1][x] == KNOWN_MINE || 
        p[y + 1][x] == UNKNOWN_MINE)
      )
    {
        count += 1;  // yläkeskellä
    }
    
    if(y != ymax && 
       x != xmax && 
       (p[y + 1][x + 1] == KNOWN_MINE || 
        p[y + 1][x + 1] == UNKNOWN_MINE)
      )
    {
        count += 1;  // yläoikealla
    }
    
    if(x != xmax && 
       (p[y][x + 1] == KNOWN_MINE || 
        p[y][x + 1] == UNKNOWN_MINE)
      )
    {
        count += 1;  // keskioikealla
    }
    
    if(y != 0 && 
       x != xmax && 
       (p[y - 1][x + 1] == KNOWN_MINE || 
        p[y - 1][x + 1] == UNKNOWN_MINE)
      )
    {
        count += 1;  // alaoikealla
    }
    
    if(y != 0 && 
       (p[y - 1][x] == KNOWN_MINE || 
        p[y - 1][x] == UNKNOWN_MINE)
      )
    {
        count += 1;  // alakeskellä
    }
    
    if(y != 0 && 
       x != 0 && 
       (p[y - 1][x - 1] == KNOWN_MINE || 
        p[y - 1][x - 1] == UNKNOWN_MINE)
      )
    {
        count += 1;  // alavasemmalla
    }
    
    if(x != 0 && 
       (p[y][x - 1] == KNOWN_MINE || 
        p[y][x - 1] == UNKNOWN_MINE)
      )
    {
        count += 1;  // keskivasemmalla
    }
    
    return count;
}
