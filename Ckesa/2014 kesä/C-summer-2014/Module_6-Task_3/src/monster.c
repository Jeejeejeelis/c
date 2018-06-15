/* monster.c -- Implementation of monster actions
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dungeon.h"

// for defining some monster types below that can be used in the game
typedef struct {
    char name[20];  // Name of monster
    char sign;  // character to show it on map
    unsigned int hplow;  // lowest possible initial maxhp
    unsigned int hphigh;  // highest possible initial maxhp
} MonstType;

// Specifying three monster types to start with.
// Feel free to add more, or change the below
// Note that it is up to you to decide whether to use this array from createMonsters
// you may or may not use it
const MonstType types[] = {
    { "Goblin", 'G', 6, 10},
    { "Rat", 'R', 3, 5},
    { "Dragon", 'D', 15, 20}
};


/* One kind of attack done by monster.
 * The attack function pointer can refer to this.
 * 
 * Parameters:
 * game: the game state
 * monst: The monster performing attack
 */
void attackPunch(Game *game, Creature *monst) {
    printf("%s punches you! ", monst->name);
    int hitprob = 50;
    int maxdam = 4;
    if (rand() % 100 < hitprob) {
        printf("Hit! ");
        int dam = rand() % maxdam + 1;
        printf("Damage: %d ", dam);
        game->hp = game->hp - dam;
        if (game->hp <= 0)
            printf("You died!");
        printf("\n");
    } else {
        printf("Miss!\n");
    }
}


/* Exercise 6.3.c

 * 
 * Move monster 'monst' towards the player character.
 * See exercise description for more detailed rules.
 */
int square(int a)
{
    return a * a;
}

float dist(Game* game, int x, int y)
{
    return sqrt(square(game->position.x - x) + square(game->position.y - y));
}

void moveTowards(Game *game, Creature *mon) {
    int x = mon->pos.x;
    int y = mon->pos.y;
    float d = dist(game, x, y);
    int nx,ny;
    if(0 < dist(game, x + 1, y) && dist(game, x + 1, y) < d && !isBlocked(game, x + 1, y))
    {
        nx = x + 1;
        ny = y;
    }
    else if(0 < dist(game, x, y + 1) && dist(game, x, y + 1) < d && !isBlocked(game, x, y + 1))
    {
        nx = x;
        ny = y + 1;
    }
    else if(0 < dist(game, x - 1, y) && dist(game, x - 1, y) < d && !isBlocked(game, x - 1, y))
    {
        nx = x - 1;
        ny = y;
    }
    else if(0 < dist(game, x, y - 1) && dist(game, x, y - 1) < d && !isBlocked(game, x, y - 1))
    {
        nx = x;
        ny = y - 1;
    }
    else 
    {
        nx = x;
        ny = y;
    }
    mon->pos.x = nx;
    mon->pos.y = ny;
}

/* Exercise 6.3.d
 *
 * Move monster 'monst' away from the player character.
 * See exercise description for more detailed rules.
 */
void moveAway(Game *game, Creature *mon) {
    int x = mon->pos.x;
    int y = mon->pos.y;
    float d = dist(game, x, y);
    int nx,ny;
    if(0 < dist(game, x + 1, y) && dist(game, x + 1, y) > d && !isBlocked(game, x + 1, y))
    {
        nx = x + 1;
        ny = y;
    }
    else if(0 < dist(game, x, y + 1) && dist(game, x, y + 1) > d && !isBlocked(game, x, y + 1))
    {
        nx = x;
        ny = y + 1;
    }
    else if(0 < dist(game, x - 1, y) && dist(game, x - 1, y) > d && !isBlocked(game, x - 1, y))
    {
        nx = x - 1;
        ny = y;
    }
    else if(0 < dist(game, x, y - 1) && dist(game, x, y - 1) > d && !isBlocked(game, x, y - 1))
    {
        nx = x;
        ny = y - 1;
    }
    else 
    {
        nx = x;
        ny = y;
    }
    mon->pos.x = nx;
    mon->pos.y = ny;
}


/* Exercise 6.3.e
 *
 * Take action on each monster (that is alive) in 'monsters' array.
 * Each monster either attacks or moves (or does nothing if no action is specified)
 */
void monsterAction(Game *game) {
    for(size_t i = 0; i < game->numMonsters; i++)
    {
        Creature* mon = game->monsters + i;
        if(mon->hp == 0)
            continue;
        if(dist(game, mon->pos.x, mon->pos.y) < 1.1 && mon->attack != NULL)
            mon->attack(game, mon);
        else
            mon->move(game, mon);
    }
}


/* Exercise 6.3.b
 *
 * Create opts.numMonsters monsters and position them on valid position
 * in the the game map. The monster data (hitpoints, name, map sign) should be
 * set appropriately (see exercise instructions) 
 */
void createMonsters(Game *game) 
{
    size_t x,y;
    size_t numMonsters = game->opts.numMonsters;
    game->numMonsters = 0;
    game->monsters = malloc(numMonsters * sizeof(Creature));
    for(size_t i = 0; i < numMonsters; i++)
    {
        x = rand() % game->opts.mapWidth;
        y = rand() % game->opts.mapHeight;
        while(isBlocked(game, x, y))
        {
            x = rand() % game->opts.mapWidth;
            y = rand() % game->opts.mapHeight;
        }
        Creature* mon = game->monsters + i;
        strcpy(mon->name, "Goblin");
        mon->sign = 'G';
        mon->maxhp = 10;
        mon->hp = (float) mon->maxhp;
        mon->pos.x = x;
        mon->pos.y = y;
        mon->move = moveTowards;
        mon->attack = attackPunch;
        game->numMonsters++;
    }
}

/* Determine whether monster moves towards or away from player character.
 */
void checkIntent(Game *game)
{
    for (unsigned int i = 0; i < game->numMonsters; i++) {
        Creature *m = &game->monsters[i];
        if (m->hp <= 2) {
            m->move = moveAway;
        } else {
            m->move = moveTowards;
        }
        if (m->hp < m->maxhp)
            m->hp = m->hp + 0.1;  // heals a bit every turn
    }
}
