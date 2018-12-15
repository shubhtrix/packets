#include "main.h"

int no;             // No of packets to be captured.

void usage () {

    printf("This is PF_RING based packet" 
            "Capture/analyzer/modifier/generator.\n");
    printf("Note : Make sure to insert"
            "pf_ring driver before using this utility.\n");
    printf("Usage :\n\t-d -\tevice to listen from\n"
                   "\t-h -\tprint this help\n"
                   "\t-n -\tnumber of packets to capture\n");
}

void main (int argc, char *argv[]) {

    int opt;
    char *device = NULL;

    printf("No of arguments recieved : %d\n", argc);

    while ((opt = getopt (argc, argv, OPTIONS)) != -1) {
    
        switch (opt) {
            case 'd' :
                device = strdup(optarg);
                break;
            case 'n' :
                no = atoi(optarg);
                printf ("No. of packets : %d\n", no);
                break;
            case 'h' :
                usage ();
                exit (EXIT_FAILURE);
            default :
                usage ();
                exit (EXIT_FAILURE);
        }
    }

    capture (device);
    exit (EXIT_SUCCESS);
}
