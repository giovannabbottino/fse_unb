#ifndef CSV_H_
#define CSV_H_

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define LOG_FILE "log_file.csv"

typedef struct data{
    float temp_int;
    float temp_ext;
    float temp_ref;
    float cooler_speed;
    float resistor_power;
} Data;

void csv_append_data(Data data);

#endif
