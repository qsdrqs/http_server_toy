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

extern FILE* log_file;
// open a log file
int InitLogFile(char* log_root_path);
// main method
void Logging(unsigned short is_access, char* resource_path, unsigned short return_code, unsigned short method, unsigned short log_mode);
// close log file
int EndLogFile();

#endif
