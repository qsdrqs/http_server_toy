/*
 * include/global.h: define constants and global vars
 *
 * Copyright (C) 2021 qsdrqs
 *
 * Author: qsdrqs <qsdrqs@gmail.com>
 * All Right Reserved
 *
 */
#ifndef GLOBAL_H
#define GLOBAL_H

/* bool vars */
#define true 1
#define false 0

/*
 * Method define
 */
enum Method {
    GET,
    POST,
    PUT
};

extern char METHOD[5][10];

/*
 * log mod
 */
enum LOG_MOD {
    CONSOLE_ONLY,
    FILE_ONLY,
    ALL
};

/* static vars */

#endif
