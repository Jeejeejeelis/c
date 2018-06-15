#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "../src/dungeon.h"

int readMap(const char *filename, Game *game) {
    Map *map = &game->map;
    //Options *opt = &game->opts;
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        return 0;
    }
    int count = 0;
    map->tile = NULL;
    char buffer[100];
    char *ret = NULL;

    do {
        map->tile = realloc(map->tile, sizeof (Tile *) * (count + 1));
        ret = fgets(buffer, sizeof (buffer), fp);
        if (ret && strlen(buffer) > 1) {
            map->tile[count] = malloc(sizeof (Tile) * strlen(buffer));
            for (unsigned int i = 0; i < strlen(buffer); i++) {
                switch (buffer[i]) {
                    case '.':
                        map->tile[count][i] = TILE_OPEN;
                        break;
                    case '#':
                    default:
                        map->tile[count][i] = TILE_WALL;
                        break;
                }
            }
            game->opts.mapWidth = strlen(buffer) - 1; // newline in the end
            count++;
        }
    } while (ret);
    game->opts.mapHeight = count;
    return 1;
}

void addMonster(Game *game, int x, int y) {
    game->monsters = realloc(game->monsters, sizeof (Creature) * (game->numMonsters + 1));
    Creature *m = &game->monsters[game->numMonsters];
    memset(m, 0, sizeof(Creature));
    m->pos.x = x;
    m->pos.y = y;
    m->hp = 12;
    m->maxhp = 12;
    strcpy(m->name, "test");
    m->sign = 'T';
    game->numMonsters++;
}

START_TEST(test_isBlocked) {
    Game game;
    memset(&game, 0, sizeof (game));
    if (!readMap("testmap", &game)) {
        if (!readMap("test/testmap", &game)) {
            freeAll(&game);
            fail("[Task 6.1.a] Failed to read the test map");
        }
    }

    //printMap(&game);

    // test wall
    int ret = isBlocked(&game, 2, 2);
    if (!ret) {
        freeAll(&game);
        fail("[Task 6.1.a] Testing isBlocked on wall (testmap:2,2). isBlocked returned %d, should have returned non-zero",
                ret);
    }

    // test open space
    ret = isBlocked(&game, 1, 1);
    if (ret) {
        freeAll(&game);
        fail("[Task 6.1.a] Testing isBlocked on open space (testmap:1,1). isBlocked returned %d, should have returned 0",
                ret);
    }

    // test out of bounds
    ret = isBlocked(&game, -1, -1);
    if (!ret) {
        freeAll(&game);
        fail("[Task 6.1.a] Testing isBlocked on out-of-bounds location -1,-1. isBlocked returned %d, should have returned non-zero",
                ret);
    }

    // test monster
    addMonster(&game, 1, 1);
    ret = isBlocked(&game, 1, 1);
    if (!ret) {
        freeAll(&game);
        fail("[Task 6.1.a] Testing isBlocked on location with monster. isBlocked returned %d, should have returned non-zero",
                ret);
    }

    freeAll(&game);
}
END_TEST

START_TEST(test_createMonsters) {
    Game game;
    memset(&game, 0, sizeof (game));
    if (!readMap("testmap", &game)) {
        if (!readMap("test/testmap", &game)) {
            freeAll(&game);
            fail("[Task 6.1.b] Failed to read the test map");
        }
    }
    game.opts.numMonsters = 10;
    createMonsters(&game);

    // test number of monsters
    if (game.numMonsters != game.opts.numMonsters) {
        freeAll(&game);
        fail("[Task 6.1.b] game.numMonsters is incorrect. Was %d, should be %d",
                game.numMonsters, game.opts.numMonsters);
    }

    char buf[160];
    for (unsigned int i = 0; i < game.opts.numMonsters; i++) {
        Creature *m = &game.monsters[i];
        // monster out of bounds
        if (m->pos.x < 0 || m->pos.y < 0 ||
                m->pos.x >= (int) game.opts.mapWidth ||
                m->pos.y >= (int) game.opts.mapHeight) {
            sprintf(buf, "[Task 6.1.b] Monster %d location is out of bounds: (%d,%d). Map dimensions: (%d,%d)",
                    i, m->pos.x, m->pos.y, game.opts.mapWidth, game.opts.mapHeight);
            freeAll(&game);
            fail(buf);
        }

        // monster location on wall
        if (game.map.tile[m->pos.y][m->pos.x] != TILE_OPEN &&
                game.map.tile[m->pos.y][m->pos.x] != TILE_ROOM) {
            char buf2[16];
            if (game.map.tile[m->pos.y][m->pos.x] == TILE_WALL)
                strcpy(buf2, "TILE_WALL");
            else
                strcpy(buf2, "unknown");
            sprintf(buf, "[Task 6.1.b] Monster %d location (%d,%d) is on %s. Should be on open space",
                    i, m->pos.x, m->pos.y, buf2);
            freeAll(&game);
            fail(buf);
        }

        // two monsters on the same spot
        for (unsigned int j = 0; j < i; j++) {
            Creature *m2 = &game.monsters[j];
            if (m->pos.x == m2->pos.x && m->pos.y == m2->pos.y) {
                sprintf(buf, "[Task 6.1.b] Monster %d is on same location as monster %d: (%d,%d)",
                        i, j, m->pos.x, m->pos.y);
                freeAll(&game);
                fail(buf);
            }
        }

        // valid hp and maxhp
        if (m->maxhp == 0) {
            freeAll(&game);
            fail("[Task 6.1.b] Monster %d has invalid max HP, should be > 0", i);
        }
        if (m->hp != m->maxhp) {
            sprintf(buf, "[Task 6.1.b] Monster %d: HP should be initially same as max HP. HP: %d, max HP: %d",
                    i, (int) m->hp, m->maxhp);
            freeAll(&game);
            fail(buf);
        }

        // valid name and character
        if (strlen(m->name) == 0 || strlen(m->name) > 19) {
            sprintf(buf, "[Task 6.1.b] Monster %d should have name that has at most 19 characters. Name length: %lu",
                    i, strlen(m->name));
            freeAll(&game);
            fail(buf);
        }
        if (!isalpha(m->sign)) {
            sprintf(buf, "[Task 6.1.b] Monster %d map sign should be alphabetic character. You have: '%c'",
                    i, m->sign);
            freeAll(&game);
            fail(buf);
        }
    }
    freeAll(&game);
}
END_TEST

float distance2(Point p1, Point p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

float moveDelta(Game *game, Point me, Point crea, void (*move)(struct game_st *, struct creature_st *)) {
    game->position = me;
    game->monsters[0].pos = crea;
    float origD = distance2(game->position, game->monsters[0].pos);

    move(game, &game->monsters[0]);

    float newD = distance2(game->position, game->monsters[0].pos);
    return newD - origD;
}

int moveTests(char *buf, Game *game, Point oldpos, float moveDelta) {
    if (abs(moveDelta) > 1.5) {
        sprintf(buf, "[Task 6.1.c] Monster at (%d,%d) moved more than one square. New location: (%d,%d)",
                oldpos.x, oldpos.y,
                game->monsters[0].pos.x, game->monsters[0].pos.y);
        return 0;
    }
    if (game->map.tile[game->monsters[0].pos.y][game->monsters[0].pos.x] == TILE_WALL) {
        sprintf(buf, "[Task 6.1.c] Monster at (%d,%d) moved to position with wall. New location: (%d,%d)",
                oldpos.x, oldpos.y,
                game->monsters[0].pos.x, game->monsters[0].pos.y);
        return 0;
    }
    if (game->numMonsters > 1) {
        if (game->monsters[0].pos.x == game->monsters[1].pos.x &&
                game->monsters[0].pos.y == game->monsters[1].pos.y) {
            sprintf(buf, "[Task 6.1.c] Monster at (%d,%d) moved to same square with other monster. New location: (%d,%d)",
                    oldpos.x, oldpos.y,
                    game->monsters[0].pos.x, game->monsters[0].pos.y);
            return 0;
        }
    }
    if (game->monsters[0].pos.x == game->position.x &&
            game->monsters[0].pos.y == game->position.y) {
        sprintf(buf, "[Task 6.1.c] Monster at (%d,%d) moved to same square with player. New location: (%d,%d)",
                oldpos.x, oldpos.y,
                game->monsters[0].pos.x, game->monsters[0].pos.y);
        return 0;
    }
    return 1;
}

START_TEST(test_moveTowards) {
    Game game;
    memset(&game, 0, sizeof (game));
    if (!readMap("testmap", &game)) {
        if (!readMap("test/testmap", &game)) {
            freeAll(&game);
            fail("[Task 6.1.c] Failed to read the test map");
        }
    }

    addMonster(&game, 1, 1);

    char buf[160];

    // test on open space
    Point myloc[] = {
        {1, 1},
        {1, 1},
        {5, 5}
    };
    Point crloc[] = {
        {5, 5},
        {1, 5},
        {1, 1}
    };
    float d;
    for (unsigned int i = 0; i < (sizeof (myloc) / sizeof (Point)); i++) {
        d = moveDelta(&game, myloc[i], crloc[i], moveTowards);
        if (d >= 0) {
            sprintf(buf, "[Task 6.1.c] Character at (%d,%d), monster at (%d,%d) did not move closer, even if it could. New location: (%d,%d)",
                    myloc[i].x, myloc[i].y, crloc[i].x, crloc[i].y,
                    game.monsters[0].pos.x, game.monsters[0].pos.y);
            freeAll(&game);
            fail(buf);
        }

        if (!moveTests(buf, &game, crloc[i], d)) {
            freeAll(&game);
            fail(buf);
        }
    }

    // test against wall
    Point p2 = {7, 2};
    d = moveDelta(&game, myloc[0], p2, moveTowards);
    if (!moveTests(buf, &game, p2, d)) {
        freeAll(&game);
        fail(buf);
    }

    // test against monster
    addMonster(&game, 1, 4);
    d = moveDelta(&game, myloc[1], crloc[1], moveTowards);
    if (!moveTests(buf, &game, p2, d)) {
        freeAll(&game);
        fail(buf);
    }
    
    // test against player
    Point p3 = {1,2};
    d = moveDelta(&game, myloc[1], p3, moveTowards);
    if (!moveTests(buf, &game, p3, d)) {
        freeAll(&game);
        fail(buf);
    }
    freeAll(&game);
}
END_TEST

START_TEST(test_moveAway) {
    Game game;
    memset(&game, 0, sizeof (game));
    if (!readMap("testmap", &game)) {
        if (!readMap("test/testmap", &game)) {
            freeAll(&game);
            fail("[Task 6.1.c] Failed to read the test map");
        }
    }

    addMonster(&game, 1, 1);

    char buf[160];

    // test on open space
    Point myloc[] = {
        {1, 1},
        {1, 1},
        {5, 5}
    };
    Point crloc[] = {
        {3, 3},
        {1, 3},
        {3, 3}
    };
    float d;
    for (unsigned int i = 0; i < (sizeof (myloc) / sizeof (Point)); i++) {
        d = moveDelta(&game, myloc[i], crloc[i], moveAway);
        if (d <= 0) {
            sprintf(buf, "[Task 6.1.c] Character at (%d,%d), monster at (%d,%d) did not move further, even if it could. New location: (%d,%d)",
                    myloc[i].x, myloc[i].y, crloc[i].x, crloc[i].y,
                    game.monsters[0].pos.x, game.monsters[0].pos.y);
            freeAll(&game);
            fail(buf);
        }

        if (!moveTests(buf, &game, crloc[i], d)) {
            freeAll(&game);
            fail(buf);
        }
    }

    // test against wall
    Point p2 = {7, 2};
    d = moveDelta(&game, myloc[2], p2, moveAway);
    if (!moveTests(buf, &game, p2, d)) {
        freeAll(&game);
        fail(buf);
    }

    // test against monster
    addMonster(&game, 1, 4);
    d = moveDelta(&game, myloc[1], crloc[1], moveAway);
    if (!moveTests(buf, &game, p2, d)) {
        freeAll(&game);
        fail(buf);
    }
    
    // test against player
    Point p3 = {1,2};
    d = moveDelta(&game, myloc[1], p3, moveAway);
    if (!moveTests(buf, &game, p3, d)) {
        freeAll(&game);
        fail(buf);
    }
    freeAll(&game);
}
END_TEST

void moveUp(Game *game, Creature *monst) {
    if (!game) return;  // never happens
    monst->pos.y--;
}

void moveDown(Game *game, Creature *monst) {
    if (!game) return;  // never happens
    monst->pos.y++;
}

void attackTest(Game *game, Creature *monst) {
    if (!monst) return;  // never happens
    game->hp = game->hp - 1;
}

START_TEST(test_monsterAction) {
    Game game;
    memset(&game, 0, sizeof (game));
    if (!readMap("testmap", &game)) {
        if (!readMap("test/testmap", &game)) {
            freeAll(&game);
            fail("[Task 6.1.e] Failed to read the test map");
        }
    }
    game.position.x = 1; game.position.y = 1;
    game.hp = 10;
    
    addMonster(&game, 1, 3);
    Creature *m = &game.monsters[0];
    m->move = moveUp;
    m->attack = attackTest;
    
    addMonster(&game, 1, 4);
    m = &game.monsters[1];
    m->move = moveDown;
    m->attack = NULL;
    
    game.opts.numMonsters = 2;
    
    // test movement
    monsterAction(&game);
    
    if (game.monsters[0].pos.y != 2) {
        freeAll(&game);
        fail("[Task 6.1.e] Monsters did not move as expected");
        /*fail("[Task 6.1.e] Monster 0 did not move as expected: %d,%d",
                game.monsters[0].pos.x, game.monsters[0].pos.y);*/
    }
    
    if (game.monsters[1].pos.y != 5) {
        freeAll(&game);
        fail("[Task 6.1.e] Monsters did not move as expected");
        /*fail("[Task 6.1.e] Monster 1 did not move as expected: %d,%d",
                game.monsters[1].pos.x, game.monsters[1].pos.y);*/
    }
    
    if (game.hp != 10) {
        freeAll(&game);
        fail("[Task 6.1.e] Monster attacked while not in adjacent square");
    }
    
    // test attack
    addMonster(&game, 2, 1);
    m = &game.monsters[2];
    m->move = NULL;
    m->attack = attackTest;
    
    game.opts.numMonsters = 3;
    
    monsterAction(&game);
    
    if (game.hp != 8) {
        freeAll(&game);
        fail("[Task 6.1.e] Monsters did not attack as expected, when player is nearby");
    }
    freeAll(&game);
}
END_TEST

void randomMap(Game *game)
{
    game->map.tile = malloc(game->opts.mapHeight * sizeof(Tile*));
    for (unsigned int i = 0; i < game->opts.mapHeight; i++) {
        game->map.tile[i] = malloc(game->opts.mapWidth * sizeof(Tile));
        for (unsigned int j = 0; j < game->opts.mapWidth; j++) {
            if (rand() % 3) {
                game->map.tile[i][j] = TILE_OPEN;
            } else {
                game->map.tile[i][j] = TILE_WALL;
            }
        }
    }
}

int compareMap(Game *orig, Game *loaded, char *buf)
{
    int diff = 0;
    char buf2[16];
    sprintf(buf, "Loaded map differs from original (lines marked with >)\n");
    for (unsigned int i = 0; i < orig->opts.mapHeight; i++) {
        memset(buf2, 0, 16);
        if (memcmp(orig->map.tile[i], loaded->map.tile[i],
                orig->opts.mapWidth*sizeof(Tile))) {
            diff = 1;
            buf2[0] = '>';
        } else {
            buf2[0] = ' ';
        }
        
        unsigned int j;
        for (j = 0; j < orig->opts.mapWidth; j++) {
            if (loaded->map.tile[i][j] == TILE_WALL)
                buf2[j+1] = '#';
            else if (loaded->map.tile[i][j] == TILE_OPEN || loaded->map.tile[i][j] == TILE_ROOM)
                buf2[j+1] = '.';
            else
                buf2[j+1] = '?';
        }
        strcat(buf2, "   ");
        strcat(buf, buf2);
        memset(buf2, 0, 16);
        
        for (j = 0; j < orig->opts.mapWidth; j++) {
            if (orig->map.tile[i][j] == TILE_WALL)
                buf2[j] = '#';
            else if (orig->map.tile[i][j] == TILE_OPEN || orig->map.tile[i][j] == TILE_ROOM)
                buf2[j] = '.';
            else
                buf2[j] = '?';
        }
        strcat(buf2, "\n");
        strcat(buf, buf2);
    }
    return diff;
}


#if 0
START_TEST(test_load_save) {
    Game orig;
    memset(&orig, 0, sizeof(orig));
    orig.opts.mapWidth = 7;
    orig.opts.mapHeight = 7;
    randomMap(&orig);
    orig.hp = 10;
    orig.position.x = 2; orig.position.y = 2;
    orig.maxhp = 10;
    int ret = save_game(&orig, "testsave-1");
    if (ret != 0) {
        freeAll(&orig);
        fail("[Task 6.3.f] save_game did not return 0, but it returned %d", ret);
    }
    
    // load_game, compare results
    Game loaded;
    memset(&loaded, 0, sizeof(loaded));
    ret = load_game(&loaded, "testsave-1");
       if (ret != 0) {
        freeAll(&orig);
        fail("[Task 6.3.f] load_game did not return 0, but it returned %d", ret);
    }
    if (orig.opts.mapWidth != loaded.opts.mapWidth ||
            orig.opts.mapHeight != loaded.opts.mapHeight) {
        freeAll(&orig);
        freeAll(&loaded);
        fail("[Task 6.3.f] After loading, map dimensions are (%d,%d), but should be (%d,%d)",
                loaded.opts.mapWidth, loaded.opts.mapHeight,
                orig.opts.mapWidth, orig.opts.mapHeight);
    }
    if (memcmp(&loaded.position, &orig.position, sizeof(Point))) {
        freeAll(&orig);
        freeAll(&loaded);
        fail("[Task 6.3.f] After loading, player position is (%d,%d), but should be (%d,%d)",
                loaded.position.x, loaded.position.y, orig.position.x, orig.position.y);
    }
    if (orig.hp != loaded.hp) {
        freeAll(&orig);
        freeAll(&loaded);
        fail("[Task 6.3.f] After loading, player HP is %d, but should be %d",
                loaded.hp, orig.hp);
    }
    char buf[300];
    buf[0] = 0;
    if (compareMap(&orig, &loaded, buf)) {
        freeAll(&orig);
        freeAll(&loaded);
        fail("[Task 6.3.f] %s", buf);
    }
    freeAll(&orig);
    freeAll(&loaded);
}
END_TEST

START_TEST(test_load_save2) {
    Game orig;
    memset(&orig, 0, sizeof(orig));
    orig.opts.mapWidth = 7;
    orig.opts.mapHeight = 7;
    randomMap(&orig);
    orig.hp = 10;
    orig.position.x = 2; orig.position.y = 2;
    orig.maxhp = 10;
    
    // add monsters
    orig.numMonsters = 4;
    orig.monsters = malloc(orig.numMonsters * sizeof(Creature));
    memset(orig.monsters, 0, orig.numMonsters * sizeof(Creature));
    for (unsigned int i = 0; i < orig.numMonsters; i++) {
        sprintf(orig.monsters[i].name, "Monster-%d", i);
        orig.monsters[i].sign = 'A' + i;
        orig.monsters[i].hp = 10;
        orig.monsters[i].maxhp = 10;
        orig.monsters[i].pos.x = i + 1;
        orig.monsters[i].pos.y = 3;
        if (i % 2)
            orig.monsters[i].move = moveTowards;
        else
            orig.monsters[i].move = moveAway;
        orig.monsters[i].attack = attackPunch;
    }
    
    int ret = save_game(&orig, "testsave-1");
    if (ret != 0) {
        freeAll(&orig);
        fail("[Task 6.3.f] save_game did not return 0, but it returned %d", ret);
    }
    
    Game loaded;
    memset(&loaded, 0, sizeof(loaded));
    ret = load_game(&loaded, "testsave-1");
       if (ret != 0) {
        freeAll(&orig);
        fail("[Task 6.3.f] load_game did not return 0, but it returned %d", ret);
    }
    
    if (loaded.numMonsters != orig.numMonsters) {
        freeAll(&orig);
        freeAll(&loaded);
        fail("[Task 6.3.f] Invalid number of monsters (numMonsters), was %d, should have been %d",
                loaded.numMonsters, orig.numMonsters);
    }
    
    char buf[160];
    for (unsigned int i = 0; i < loaded.numMonsters; i++) {
        if (strcmp(orig.monsters[i].name, loaded.monsters[i].name)) {
            if (strlen(loaded.monsters[i].name) < 20) {
                sprintf(buf, "[Task 6.3.f] Loading monster %d, name was '%s', should have been '%s'",
                        i, loaded.monsters[i].name, orig.monsters[i].name);
            } else {
                sprintf(buf, "[Task 6.3.f] Loading monster %d, invalid name (size too long)",
                        i);
            }
            freeAll(&orig);
            freeAll(&loaded);
            fail(buf);
        }
        if (orig.monsters[i].sign != loaded.monsters[i].sign) {
            sprintf(buf, "[Task 6.3.f] Loading monster %d, sign was '%c', should have been '%c'",
                    i, loaded.monsters[i].sign, orig.monsters[i].sign);
            freeAll(&orig);
            freeAll(&loaded);
            fail(buf);
        }
        if (orig.monsters[i].hp != loaded.monsters[i].hp) {
            sprintf(buf, "[Task 6.3.f] Loading monster %d, hp was %.1f, should have been %.1f",
                    i, loaded.monsters[i].hp, orig.monsters[i].hp);
            freeAll(&orig);
            freeAll(&loaded);
            fail(buf);
        }
        if (memcmp(&orig.monsters[i].pos, &loaded.monsters[i].pos, sizeof(Point))) {
            sprintf(buf, "[Task 6.3.f] Loading monster %d, position was (%d,%d), should have been (%d,%d)",
                    i, loaded.monsters[i].pos.x, loaded.monsters[i].pos.y,
                    orig.monsters[i].pos.x, orig.monsters[i].pos.x);
            freeAll(&orig);
            freeAll(&loaded);
            fail(buf);
        }
        if (orig.monsters[i].move != loaded.monsters[i].move) {
            sprintf(buf, "[Task 6.3.f] Loading monster %d, move algorithm differs from original",
                    i);
            freeAll(&orig);
            freeAll(&loaded);
            fail(buf);
        }
    }
    freeAll(&orig);
    freeAll(&loaded);
}
END_TEST
#endif

int main(int argc, const char *argv[]) {
    Suite *s = suite_create("Test-6.3");

    tmc_register_test(s, test_isBlocked, "6.3.a");
    tmc_register_test(s, test_createMonsters, "6.3.b");
    tmc_register_test(s, test_moveTowards, "6.3.c");
    tmc_register_test(s, test_moveAway, "6.3.d");
    tmc_register_test(s, test_monsterAction, "6.3.e");
    //tmc_register_test(s, test_load_save, "6.3.f");
    //tmc_register_test(s, test_load_save2, "6.3.g");

    return tmc_run_tests(argc, argv, s);
}
