/*
 * include/util/map.h

 * Copyright (C) 2021 qsdrqs
 *
 * Author: qsdrqs <qsdrqs@gmail.com>
 * All Right Reserved
 *
 */
#ifndef MAP_H
#define MAP_H

#define INIT_SIZE 10
#define SCALE_FACTOR 0.75

typedef struct Map {
    char** keys;
    char** values;
    int _capacity;
    int _size;
} Map;

Map* init_map();

int add_key_value(char* key, char* value, Map* map);
int find(char* key, Map* map, char* result);

#endif
