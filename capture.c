#include "main.h"

void capture (char *device) {

    int ret;
    pfring *handle;
    pfring_stat *stats;
    u_int32_t length = DEFAULT, flags = 0;

    printf("Listening on device %s\n", device);
    printf("No of packets to be captured : %d\n", no);

    handle = pfring_open (device, length, flags);
    if (handle == NULL) {
        printf("pfring_open failed...\n");
        exit (EXIT_FAILURE);
    }

    stats = (pfring_stat *)malloc (sizeof(pfring_stat));
    if ((ret = pfring_stats (handle, stats)) == -1) {
        printf ("No stats!!! \n");
        exit (EXIT_FAILURE);
    } else {
        printf("Packets ::\n\t Received : %ld, Dropped : %ld, Shunt : %ld\n",
                stats->recv, stats->drop, stats->shunt);
    }

    pfring_close (handle);
    exit (EXIT_SUCCESS);

}
