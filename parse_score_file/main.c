#include "parse_score_file.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_help( const char* pname ) {
    fprintf( stderr,

"usage: %s -i INPUT -o OUTPUT [-f FREQUENCY] [-t TIME] [-h]\n"
"-i INPUT:     file name of score input, defaults to /dev/stdin\n"
"              for format, consider example\n"
"-o OUTPUT:    file name of bash output, defaults to /dev/stdout\n"
"-f FREQUENCY: at what frequency to start with note '1', defaults to %.1f\n"
"-t TIME:      unit of time in milliseconds, defaults to %.1f\n"
"-h:           show this help\n",

    pname, get_start_freq(), get_time_unit_ms() );
}

int main( int argc, char** argv ) {

    int opt;
    char infile[1024] = "";
    char outfile[1024] = "/dev/stdout";
    while ((opt = getopt(argc, argv, ":hi:o:f:t:")) != -1) {
        switch (opt) {
            case 'h':
                print_help( argv[0] );
                return EXIT_SUCCESS;
            case 'i':
                strcpy( infile, optarg );
                break;
            case 'o':
                strcpy( outfile, optarg );
                break;
            case 'f':
                set_start_freq( atof(optarg) );
                break;
            case 't':
                set_time_unit_ms( atof(optarg) );
                break;
            case '?':
                fprintf(stderr, "unknown option '-%c'. print help with '-h'\n", optopt);
                break;
            default:
                break;
        }
    }

    if (!strcmp(infile,"")) {
        if (!isatty(fileno(stdin))) {
            strcpy(infile,"/dev/stdin");
        } else {
            fprintf(stderr, "need input file or pipe\n");
            return EXIT_FAILURE;
        }
    }

    FILE* input = fopen(infile,"r");
    if (!input) {
        fprintf(stderr, "cannot open file %s\n", infile);
        return EXIT_FAILURE;
    }
    char* beepscript_start = parse_score_file( input );

    FILE* output = fopen(outfile,"w");
    if (!output) {
        fprintf(stderr, "cannot open file %s\n", outfile);
        return EXIT_FAILURE;
    }
    fprintf(output, "%s\n", beepscript_start);

    fclose(input);
    fclose(output);
    free(beepscript_start);

    return EXIT_SUCCESS;
}
