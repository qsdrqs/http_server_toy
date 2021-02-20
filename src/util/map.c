/*
 * src/util/map.c: provide scalable key-value string data struct support
 *
 * Copyright (C) 2021 qsdrqs
 *
 * Author: qsdrqs <qsdrqs@gmail.com>
 * All Right Reserved
 *
 */

#include "util/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"

//private:
void expand_map(Map* map)
{
    map->_capacity *= 2;
    char** keys = (char**)malloc(map->_capacity * sizeof(char*));
    char** values = (char**)malloc(map->_capacity * sizeof(char*));

    for (int i = 0; i < map->_size; ++i) {
        keys[i] = map->keys[i];
        values[i] = map->values[i];
    }
    free(map->keys);
    free(map->values);
    map->keys = keys;
    map->values = values;
}

//public:
Map* init_map()
{
    Map* map = (Map*)malloc(sizeof(Map));
    char** keys = (char**)malloc(INIT_SIZE * sizeof(char*));
    char** values = (char**)malloc(INIT_SIZE * sizeof(char*));
    memset(keys, 0, INIT_SIZE);
    map->keys = keys;
    map->values = values;
    map->_size = 0;
    map->_capacity = INIT_SIZE;
    return map;
}

int add_key_value(char* key, char* value, Map* map)
{
    if (strlen(key) >= MAXLENGTH || strlen(value) >= MAXLENGTH) {
        puts("key or value too long!");
        return -1;
    }
    if (map->_size > map->_capacity * SCALE_FACTOR ) {
        expand_map(map);
    }
    char buffer[MAXLENGTH];
    int pos;
    if ((pos = find(key, map, buffer)) >= 0) {
        // replace old one
        map->values[pos] = value;
    } else {
        map->_size++;
        map->keys[map->_size - 1] = key;
        map->values[map->_size - 1] = value;
    }

    return 0;
}

int find(char* key, Map* map, char* result)
{
    for (int i = 0; i < map->_size; ++i) {
        if (strcmp(key, map->keys[i]) == 0) {
            strcpy(result, map->values[i]);
            return i;
        }
    }
    return -1;
}

void free_map(Map *map)
{
    free(map->keys);
    free(map->values);
    free(map);
}
