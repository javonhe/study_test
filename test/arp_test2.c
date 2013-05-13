
/* vi: set sw=4 ts=4: */  
/* 
 * arpping.c 
 * 
 * Mostly stolen from: dhcpcd - DHCP client daemon 
 * by Yoichi Hariguchi <yoichi@fore.com> 
 */  
  
#include <netinet/if_ether.h>  
#include <net/if_arp.h>  
  
#include "common.h"  
#include "dhcpd.h"	
  
//这里是arp包的格式,其中的数据格式都是宏了，比如uint_8_t为无符char.  
struct arpMsg {  
	/* Ethernet header */  
	uint8_t  h_dest[6]; 	/* 00 destination ether addr */  
	uint8_t  h_source[6];	/* 06 source ether addr */	
	uint16_t h_proto;		/* 0c packet type ID field */  
  
	/* ARP packet */  
	uint16_t htype; 		/* 0e hardware type (must be ARPHRD_ETHER) */  
	uint16_t ptype; 		/* 10 protocol type (must be ETH_P_IP) */  
	uint8_t  hlen;			/* 12 hardware address length (must be 6) */  
	uint8_t  plen;			/* 13 protocol address length (must be 4) */  
	uint16_t operation; 	/* 14 ARP opcode */  
	uint8_t  sHaddr[6]; 	/* 16 sender's hardware address */	
	uint8_t  sInaddr[4];	/* 1c sender's IP address */  
	uint8_t  tHaddr[6]; 	/* 20 target's hardware address */	
	uint8_t  tInaddr[4];	/* 26 target's IP address */  
	uint8_t  pad[18];		/* 2a pad for min. ethernet payload (60 bytes) */  
} PACKED;  
  
enum {	
	ARP_MSG_SIZE = 0x2a  
};	
  
  
/* Returns 1 if no reply received */  
  
//主程序，如果返回1说明此ip可用  
int arpping(uint32_t test_ip, uint32_t from_ip, uint8_t *from_mac, const char *interface)  
{  
  
	int timeout_ms;  
//这里使用poll来检测句柄。	
	struct pollfd pfd[1];  
#define s (pfd[0].fd)			/* socket */  
	int rv = 1; 			/* "no reply received" yet */  
	struct sockaddr addr;	/* for interface name */  
	struct arpMsg arp;	
  
//建立scoket.由于我们是要直接访问访问链路层并自己组arp包.因此我们使用PF_PACKET协议簇.socket类型为SOCK_PACKET.  
  
	s = socket(PF_PACKET, SOCK_PACKET, htons(ETH_P_ARP));  
	if (s == -1) {	
		bb_perror_msg(bb_msg_can_not_create_raw_socket);  
		return -1;	
	}  
  
	if (setsockopt_broadcast(s) == -1) {  
		bb_perror_msg("cannot enable bcast on raw socket");  
		goto ret;  
	}  
//进行组包，由于是要广播，因此目的mac地址为全0.  
	/* send arp request */	
	memset(&arp, 0, sizeof(arp));  
	memset(arp.h_dest, 0xff, 6);					/* MAC DA */  
	memcpy(arp.h_source, from_mac, 6);				/* MAC SA */  
	arp.h_proto = htons(ETH_P_ARP); 				/* protocol type (Ethernet) */	
	arp.htype = htons(ARPHRD_ETHER);				/* hardware type */  
	arp.ptype = htons(ETH_P_IP);					/* protocol type (ARP message) */  
	arp.hlen = 6;									/* hardware address length */  
	arp.plen = 4;									/* protocol address length */  
	arp.operation = htons(ARPOP_REQUEST);			/* ARP op code */  
	memcpy(arp.sHaddr, from_mac, 6);				/* source hardware address */  
	memcpy(arp.sInaddr, &from_ip, sizeof(from_ip)); /* source IP address */  
	/* tHaddr is zero-fiiled */ 					/* target hardware address */  
	memcpy(arp.tInaddr, &test_ip, sizeof(test_ip)); /* target IP address */  
  
	memset(&addr, 0, sizeof(addr));  
	safe_strncpy(addr.sa_data, interface, sizeof(addr.sa_data));  
//广播arp包.  
	if (sendto(s, &arp, sizeof(arp), 0, &addr, sizeof(addr)) < 0) {  
		// TODO: error message? caller didn't expect us to fail,  
		// just returning 1 "no reply received" misleads it.  
		goto ret;  
	}  
  
	/* wait for arp reply, and check it */	
//等待时间，超时则认为此ip地址可用	
	timeout_ms = 2000;	
	do {  
		int r;	
		unsigned prevTime = monotonic_us();  
  
		pfd[0].events = POLLIN;  
//这边他是害怕poll被信号打断，因此加了层循环，其实这边我们还可以使用ppoll的，就可以了。  
		r = safe_poll(pfd, 1, timeout_ms);	
		if (r < 0)	
			break;	
		if (r) {  
//读取返回数据.  
			r = read(s, &arp, sizeof(arp));  
			if (r < 0)	
				break;	
//检测是否为应打包，发送ip是否为我们所请求的ip,这里是为了防止其他的数据包干扰我们检测。  
			if (r >= ARP_MSG_SIZE  
			 && arp.operation == htons(ARPOP_REPLY)  
			 /* don't check it: Linux doesn't return proper tHaddr (fixed in 2.6.24?) */  
			 /* && memcmp(arp.tHaddr, from_mac, 6) == 0 */	
			 && *((uint32_t *) arp.sInaddr) == test_ip	
			) {  
//说明ip地址已被使用  
				rv = 0;  
				break;	
			}  
		}  
		timeout_ms -= ((unsigned)monotonic_us() - prevTime) / 1000;  
	} while (timeout_ms > 0);  
  
 ret:  
	close(s);  
	DEBUG("%srp reply received for this address", rv ? "No a" : "A");  
	return rv;	
} 


int main(int argc, char **argv)
{
	
}

