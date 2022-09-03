#include "csv.h"

void csv_append_data(Data data){
    FILE *fd = fopen(LOG_FILE, "a");

    time_t time_now;
    struct tm *info;
    time(&time_now);
    info = localtime(&time_now);

    fprintf(fd, "%02d,%02d,%02d,", info->tm_mday, info->tm_mon, info->tm_year%100 + 2000);
    fprintf(fd, "%02d:%02d:%02d,", info->tm_hour, info->tm_min, info->tm_sec);
    fprintf(fd, "%02.2lf,%02.2lf,%02.2lf,", data.temp_int, data.temp_ext, data.temp_ref);
    fprintf(fd, "%02.2lf,%02.2lf\n", data.cooler_speed, data.resistor_power);
    fclose(fd);
}
