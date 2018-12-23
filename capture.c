#include "main.h"

void capture (char *device) {

    int ret;
    char print_out[10000] = {'\0'};
    u_char buffer[10000];
    u_char mac_addr[6] = {0}; 
    u_char *buffer_p = buffer;
    u_char my_buffer[5000];
    pfring *handle;
    pfring_stat *stats;
    u_int32_t length = DEFAULT, flags = 0;
    struct pfring_pkthdr hdr;
    struct pfring_pkthdr header;

    printf("Listening on device %s\n", device);
    printf("No of packets to be captured : %d\n", no);

    flags |= (1<<3);        //Promiscuous
    flags |= (1<<5);        //Hw Timestamp

    handle = pfring_open (device, length, flags);
    if (handle == NULL) {
        printf("pfring_open failed...\n");
        exit (EXIT_FAILURE);
    }

    pfring_set_application_name (handle, "packet");

    // Let'd check whether the ring is bounded to correct MAC/Device
    ret = pfring_get_bound_device_address ( handle, mac_addr);
    printf("Mac Address is %2x:%2X:%2x:%2x:%2x:%2x\n", 
                mac_addr[0],mac_addr[1],mac_addr[2],
                    mac_addr[3],mac_addr[4],mac_addr[5]);

    // MTU SIZE of the device.
    ret = pfring_get_mtu_size ( handle);
    printf("PFRING MTU SIZE : %d\n", ret);

    // Set the direction 0 means both rx and tx
    pfring_set_direction (handle, 0);

    // No of rx queues of the device.
    printf("RX QUEUES of the device : %u\n", pfring_get_num_rx_channels(handle));

    // Set the mode of socket to receive or send 2 means receive only
    pfring_set_socket_mode (handle, 2);

    pfring_set_poll_duration (handle, 1000);

    pfring_enable_ring (handle);

    memset (&hdr, 0, sizeof(hdr));
    if (pfring_recv (handle, &buffer_p, 5000, &header, 0)) {
        printf("First recv call:  >>>>>>>>>>>\n");
        pfring_print_parsed_pkt (print_out, 10000, buffer_p, &header);
        printf("RAW PACKET :: %s\n", print_out);
        pfring_print_pkt (print_out, sizeof (print_out), buffer_p, 10000, 10000);
        printf("RAW PACKET :: %s\n", print_out);
    }
    if (pfring_recv (handle, &buffer_p, 1000, &hdr, 1)) {
        printf("Inside pfring_recv >>>>>>>>>>>\n");
        pfring_print_pkt (print_out, sizeof (print_out), buffer_p, 1000, 1000);
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
