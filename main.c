#include "main.h"

int no;             // No of packets to be captured.

void usage () {

    printf("This is PF_RING based packet " 
            "Capture/analyzer/modifier/generator.\n");
    printf("Note : Make sure to insert"
            "pf_ring driver before using this utility.\n");
    printf("Usage :\n\t-a -\taction to perform i.e., 0 means ARREST | non-0 means RELEASE \n"
                   "\t-d -\tdevice to listen on\n"
                   "\t-h -\tprint this help\n"
                   "\t-n -\tnumber of packets to capture\n"
                   "\t--PLEASE NOTE THAT ACTION RELEASE IS NOT YET IMPLEMENTED--\n");
}

void main (int argc, char *argv[]) {

    int opt;
    enum act action=ARREST; 
    char *device = NULL;

    while ((opt = getopt (argc, argv, OPTIONS)) != -1) {
    
        switch (opt) {
            case 'a' :
                action = atoi(optarg);
                break;
            case 'd' :
                device = strdup(optarg);
                break;
            case 'n' :
                no = atoi(optarg);
                break;
            case 'h' :
                usage ();
                exit (EXIT_FAILURE);
            default :
                usage ();
                exit (EXIT_FAILURE);
        }
    }
    
    if (device) {
        if (action) {                       // RELEASE CASE 
            printf ("Releasing the packets.\n");
            release ( device, no);
        } else {                            // ARREST CASE
            printf ("Arresting the packets.\n");
            arrest ( device, no);
        }
    } else {
        printf ("NO device provided to capture packets.\nEXITING...\n\n");
        usage ();
        exit (EXIT_SUCCESS);
    } 

    exit (EXIT_SUCCESS);
}
