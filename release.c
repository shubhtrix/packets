#include "main.h"

#define USR_PKT_SIZE (MIN_PKT_SIZE + 10)

unsigned char p[USR_PKT_SIZE] = {   0xb8, 0x27, 0xeb, 0x3d, 0x58, 0x46,
                                    0x20, 0x47, 0x47, 0x36, 0xab, 0xe2,
                                    0x08, 
                                    0x00, 0x45, 0x00, 0x00, 0x34, 0x00,
                                    0x00, 0x40, 0x00, 0x40, 0x06, 0x26,
                                    0xb0, 0x0a, 0x00, 0x00, 0x0a, 0x0a,
                                    0x00, 0x00, 0x0b,
                                    0xc3, 0x50, 0xc3, 0x50, 0xd7, 0xf2,
                                    0xdf, 0x4e, 0xe8, 0x3f, 0xef, 0x5e,
                                    0x80, 0x10, 0x00, 0xf1, 0x64, 0x7b,
                                    0x00, 0x00, 0x01, 0x01, 0x08, 0x0a, 
                                    0xda, 0x3f, 0x39, 0x72, 0xc7, 0xcc,
                                    0x75, 0x0e 
                                }; 

/*  JUST A RAW SAMPLE FIELDS FOR REFERENCE    
    pkt = "b827eb3d5846"
          "20474736abe2"
          "0800"            //UPTO ETHER
          "450000340000"
          "4000400626B0"
          "0a00000a0a00"
          "000b"            //UPTO IP
          "c350c350d7f2"
          "df4ee83fef5e"
          "801000f1647b"
          "00000101080a"
          "da3f3972c7cc"
          "750e";           //UPTO TCP
*/

void release (char *device, int no) {

    int ret, i=0;
    char print_out[10000] = {'\0'};
    u_char buffer[10000];
    u_char mac_addr[6] = {0}; 
    u_char *buffer_p = buffer;
    pfring *handle;
    pfring_stat *stats;
    u_int32_t length = DEFAULT, flags = 0;
    struct pfring_pkthdr hdr;
    struct pfring_pkthdr header;

    unsigned char *pkt = NULL;

    pkt = (unsigned char *)malloc(USR_PKT_SIZE); 
  
    memset ( pkt, '0', sizeof(pkt)/sizeof(unsigned char));

    // Now Fill pkt to provided packet information.
    memcpy ( pkt, p, USR_PKT_SIZE);

    printf("Using device %s\n", device);
    if (no)
        printf("No of packets to be released : %d\n", no);
    else
        no = 0x0fffffff;

    flags |= (1<<3);        //Promiscuous
    flags |= (1<<5);        //Hw Timestamp

    handle = pfring_open (device, length, flags);
    if (handle == NULL) {
        printf("pfring_open failed...\n");
        exit (EXIT_FAILURE);
    }

    pfring_set_application_name (handle, "packet");

    // Let's check whether the ring is bounded to correct MAC/Device
    ret = pfring_get_bound_device_address ( handle, mac_addr);
    printf("Device Mac is :: %2x:%2X:%2x:%2x:%2x:%2x\n", 
                    mac_addr[0],mac_addr[1],mac_addr[2],
                    mac_addr[3],mac_addr[4],mac_addr[5]);

    // MTU SIZE of the device.
    ret = pfring_get_mtu_size ( handle);
    printf("PFRING MTU SIZE : %d\n", ret);

    // Set the direction 0 means both rx and tx
    pfring_set_direction ( handle, 0);

    printf ("Pkt DST MAC :: %2x:%2x:%2x%2x:%2x:%2x\n\tSRC MAC :: %2x:%2x:%2x%2x:%2x:%2x\n",
                                                pkt[0],pkt[1],pkt[2],pkt[3],pkt[4],pkt[5],
                                                pkt[6],pkt[7],pkt[8],pkt[9],pkt[10],pkt[11]);

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
