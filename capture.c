#include "main.h"

void capture (char *device) {

    int ret;
    char print_out[10000] = {'\0'};
    u_char buffer[9000]; 
    u_char *buffer_p = buffer;
    pfring *handle;
    pfring_stat *stats;
    u_int32_t length = DEFAULT, flags = 0;
    struct pfring_pkthdr hdr;

    printf("Listening on device %s\n", device);
    printf("No of packets to be captured : %d\n", no);

    handle = pfring_open (device, length, flags);
    if (handle == NULL) {
        printf("pfring_open failed...\n");
        exit (EXIT_FAILURE);
    }

    // MTU SIZE of the device.
    ret = pfring_get_mtu_size ( handle);
    printf("PFRING MTU SIZE : %d\n", ret);

    // No of rx queues of the device.
    printf("RX QUEUES of the device : %u\n", pfring_get_num_rx_channels(handle));

    memset (&hdr, 0, sizeof(hdr));
    if (pfring_recv (handle, &buffer_p, 9000, &hdr, 1)) {
        printf("Inside pfring_recv >>>>>>>>>>>\n");
        pfring_print_pkt (print_out, sizeof (print_out), buffer_p, 9000, 9000);
        printf("RAW PACKET :: %s\n", print_out);
    } 
    stats = (pfring_stat *)malloc (sizeof(pfring_stat));
    if ((ret = pfring_stats (handle, stats)) == -1) {
        printf ("No stats!!! \n");
        exit (EXIT_FAILURE);
    } else {
        printf("Packets ::\n\t Received : %ld, Dropped : %ld, Shunt : %ld\n",
                stats->recv, stats->drop, stats->shunt);
    }

    free (stats);
    pfring_close (handle);
    exit (EXIT_SUCCESS);

}
