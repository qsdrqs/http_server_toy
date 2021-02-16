/*
 * include/log/log_output.h
 *
 * Copyright (C) 2021 qsdrqs
 *
 * Author: qsdrqs <qsdrqs@gmail.com>
 * All Right Reserved
 *
 */
#ifndef LOG_OUTPUT_H
#define LOG_OUTPUT_H
#include <stdio.h>
#include <sys/types.h>

extern FILE* log_file;
// open a log file
int init_log_file(char* log_root_path);
// main method
void logging(u_int8_t is_access, char* resource_path, u_int16_t return_code, u_int8_t method, u_int8_t log_mode);
// close log file
int end_log_file();

#endif
