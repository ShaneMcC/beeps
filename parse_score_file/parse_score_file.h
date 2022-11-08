#pragma once

#include <stdio.h>

char* parse_score_file( FILE* f );
void set_start_freq( double freq );
void set_time_unit_ms( double msec );
double get_start_freq();
double get_time_unit_ms();
