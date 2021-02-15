/*
 * src/log/log_output.c: provide unified log output through command line and file
 *
 * log format: ACCESS/DENY [XXXX-XX-XX XX:XX:XX] METHOD RESOURCE RETURN_CODE
 *
 * Copyright (C) 2021 qsdrqs
 *
 * Author: qsdrqs <qsdrqs@gmail.com>
 * All Right Reserved
 *
 */

#include "log/log_output.h"
#include "global.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

FILE* log_file;

// TODO :use struct to decouple

int InitLogFile(char* log_root_path)
{
    int len = strlen(log_root_path);
    // check length
    if (len > 245) {
        puts("log directory path is too long!");
        return -1;
    }
    // check last '/'
    if (log_root_path[len - 1] != '/') {
        strcat(log_root_path, "/");
        len++;
    }
    /* create dir if not exist */
    char dir_path[256];
    memset(dir_path, 0, 256);
    strncpy(dir_path, log_root_path, strlen(log_root_path) - 1); // copy except last '/'
    char* dirstack[256];
    struct stat st = { 0 };
    int i = 0;
    // push stack
    while (strcmp(dir_path, "") != 0) {
        if (stat(dir_path, &st) == -1) {
            char* index = strrchr(dir_path, '/');
            if (index == 0) { // relative path
                dirstack[i] = index;
                break;
            }
            *index = '\0';
            dirstack[i] = index + 1;
            i++;
        } else {
            break;
        }
    }
    // pop stack
    char buf[256];
    for (int j = i - 1; j >= 0; --j) {
        if (mkdir(strcat(buf, dirstack[j]), 0755)) {
            puts("fail making log directorys!");
            return -1;
        }
        strcat(buf, "/");
    }

    log_file = fopen(strcat(log_root_path, "http.log"), "a");
    if (log_file == 0) {
        puts("Error opening log file!");
        return -1;
    }
    return 0;
}

char* get_time()
{
    time_t raw_time = time(0);
    static int time_len = 30;
    char* format_time = (char*)malloc(time_len);
    strftime(format_time, time_len, "[%Y-%m-%d %H:%M:%S]", localtime(&raw_time));
    return format_time;
}

void LogIntoFile(u_int8_t is_access, char* resource_path, u_int16_t return_code, u_int8_t method, char* time)
{
    if (is_access) {
        fprintf(log_file, "ACCESS");
    } else {
        fprintf(log_file, "DENY");
    }
    fprintf(log_file, " ");
    fprintf(log_file, "%s", time);
    fprintf(log_file, " ");
    fprintf(log_file, "\"%s", METHOD[method]);
    fprintf(log_file, " ");
    fprintf(log_file, "%s\"", resource_path);
    fprintf(log_file, " ");
    fprintf(log_file, "%d\n", return_code);
}

void LogOnConsole(u_int8_t is_access, char* resource_path, u_int16_t return_code, u_int8_t method, char* time)
{
    if (is_access) {
        printf("ACCESS");
    } else {
        printf("DENY");
    }
    printf(" ");
    printf("%s", time);
    printf(" ");
    printf("\"%s", METHOD[method]);
    printf(" ");
    printf("%s\"", resource_path);
    printf(" ");
    printf("%d\n", return_code);
}

void Logging(u_int8_t is_access, char* resource_path, u_int16_t return_code, u_int8_t method, u_int8_t log_mode)
{
    char* time = get_time();
    if (log_mode == CONSOLE_ONLY) {
        LogOnConsole(is_access, resource_path, return_code, method, time);
    } else if (log_mode == FILE_ONLY) {
        LogIntoFile(is_access, resource_path, return_code, method, time);
    } else {
        LogOnConsole(is_access, resource_path, return_code, method, time);
        LogIntoFile(is_access, resource_path, return_code, method, time);
    }
    free(time);
}

int EndLogFile()
{
    return fclose(log_file);
}
