#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

static double SMALLEST_TIME_UNIT_MS = 100.0;
static double NOTE_1_FREQ_HZ = 800.0; // 523.25 for C

static int positive_mod( int value, int m ) {
    int mod = value % (int)m;
    if (mod < 0) {
        mod += m;
    }
    return mod;
}

static void note_and_octave( int note, int* pnote, int* poctave ) {
    int base = positive_mod( note, 7 );
    int fac = note / 7;
    if (note < 0 && base != 0) fac--;
    *pnote = base;
    *poctave = fac;
}

static const int step_size[] = {
    0,
    2,
    4,
    5,
    7,
    9,
    11,
};

static double get_frequency( int _note, int increment ) {
    int note, octave;
    note_and_octave( _note, &note, &octave );
    int number_of_half_tones = octave * 12 + step_size[note];
    number_of_half_tones += increment;
    return NOTE_1_FREQ_HZ * pow(1.059463,number_of_half_tones);
}

static double get_time( int nrep ) {
    return SMALLEST_TIME_UNIT_MS * nrep;
}

static void dump_arg( int note, int increment, int nrep, char** out ) {
    double f = get_frequency( note, increment );
    double t = get_time( nrep );
    sprintf(*out, "-f %.5f -l %.5f \\\n", f, t);
    *out += strlen(*out);
}

static void dump_next( char** out ) {
    sprintf(*out, "-n \\\n" );
    *out += strlen(*out);
}

static void dump_pause( int nrep, char** out ) {
    double t = get_time( nrep );
    sprintf(*out, "-D %.5f \\\n", t );
    *out += strlen(*out);
}

static void dump_header( char** out ) {
    sprintf(*out, "#!/bin/bash\nbeep ");
    *out += strlen(*out);
}

static void dump_end( char** out ) {
    sprintf(*out, "\n");
    *out += strlen(*out);
}

char* parse_score_file( FILE* f ) {

    char* beepscript_start = calloc(1024ul*1024ul*16,1);
    char* beepscript = beepscript_start;
    dump_header( &beepscript );

    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    int nrep = 0;
    int note = 0;
    int pause = 0;
    int increment = 0;

    bool has_first_note = false;
    while ((nread = getline(&line, &len, f)) != -1) {

        // ignore comments
        if (nread > 1)
            if (line[0] == '#')
                goto nextline;

        if (!strcmp(line,"\n")) {
            if (pause)
                dump_pause( nrep, &beepscript );
            else {
                if (!has_first_note)
                    has_first_note = true;
                else
                    dump_next( &beepscript );
                dump_arg( note-1, increment, nrep, &beepscript );
            }
            // reset
            nrep = 0;
            pause = 0;
            note = 0;
            increment = 0;
        } else {
            if (!strcmp(line,"P\n")) {
                pause = 1;
            } else {
                char increment_string[10] = "";
                sscanf(line, "%d%9s\n", &note, increment_string);
                increment_string[9] = '\0';
                int n_inc = strlen(increment_string);
                if (n_inc) {
                    if (increment_string[0] == 'p')
                        increment = n_inc;
                    else if (increment_string[0] == 'm')
                        increment = -n_inc;
                }
                else
                    increment = 0;
            }
            nrep++;
        }

        // ignore comments
        nextline: {}
    }
    free(line);
    dump_end( &beepscript );

    return beepscript_start;

}

void set_start_freq( double freq ) {
    NOTE_1_FREQ_HZ = freq;
}

void set_time_unit_ms( double msec ) {
    SMALLEST_TIME_UNIT_MS = msec;
}

double get_start_freq() {
    return NOTE_1_FREQ_HZ;
}

double get_time_unit_ms() {
    return SMALLEST_TIME_UNIT_MS;
}
