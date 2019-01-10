# packets
Packets is a repo for learning and analyzing network packets thorough PF_RING library. 
The aim of the repo is to capture and analyze the packets and also to create hard-coded 
packets and send (Kinda packet generator).

How it works?

1. To run this utility, insmod pf_ring.ko first and use following command after that : 
   (Please note that wlp6s0 is device for operation.) 
   #
   #./packets -d wlp6s0 -a 0 -n 30 
   #
   #
