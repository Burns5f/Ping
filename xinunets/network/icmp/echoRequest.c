#include <xinu.h>
#include <icmp.h>
#include <stdlib.h>
#include <network.h>

	/**
 * Generate a Echo request.
 *
 * @param *ipaddr pointer to the IP address
 */
int echoRequest(int dev, uchar *ipaddr)
{
	uchar buffer[PKTSZ];
	struct ethergram *ether = (struct ethergram *)buffer;
	struct ipgram *dgram = (struct ipgram*)ether->data; 
	struct icmpgram   *icmp = (struct icmpgram *)dgram->opts;
	int i;

	// Construct an echo request.
	for (i = 0; i < ETH_ADDR_LEN; i++)
	{ ether->dst[i] = 0xFF; }
	getmac(dev, ether->src);
	ether->type = htons(ETYPE_IPv4);

	dgram->ver_ihl = (IPv4_VERSION << 4) | (IPv4_HDR_LEN >> 2);
	dgram->tos = IPv4_TOS_ROUTINE;
	dgram->len = htons((dgram->opts - (uchar *)dgram));
	dgram->id  = htons(currpid);
	dgram->flags_froff = 0;
	dgram->ttl = 63;
	dgram->proto = IPv4_PROTO_ICMP;
	dgram->chksum = 0;
	getip(dev, dgram->src);
	dgram->dst = ipaddr;
	//getip and then the ip address passed in. 
	icmp->type = ECHO;
	icmp->code  = 0;
	icmp->checksum  = 0;
	icmp->identifier  = 0; //need fixing 
	icmp->seqnum = 0; //need fixing
	//icmp->data = 0; array size 18 to fill rest of space in buffer
	//getmac(dev, arp->sha);
	//getip(dev, arp->spa);
    //bzero(arp->tha, ETH_ADDR_LEN);
    //memcpy(arp->tpa, ipaddr, IP_ADDR_LEN);

	//fill in data portion with data
	for (i = 0; i++; i < ICMP_PAYLOAD_LENGTH)
	{}
	dgram->chksum = checksum((uchar *)dgram, 
							 (4 * (dgram->ver_ihl & IPv4_IHL)));
	icmp->checksum  = checksum((uchar*)icmp,sizeof(struct icmpgram) + ICMP_PAYLOAD_LENGTH); //8 size of struct + 18 payload size to fill out buffer

	
	write(dev, (uchar *)buffer, 
		  sizeof(struct ethergram) + sizeof(struct ipgram) + sizeof(struct icmpgram));

	// sleep(1000);

	// if (ARPPENDING != arptab[arpindex].state) { return OK; }

	// write(dev, (uchar *)buffer, 
	// 	  sizeof(struct ethergram) + sizeof(struct arpgram));
	
	// sleep(1000);	
	
	// if (ARPPENDING != arptab[arpindex].state) { return OK; }

	// write(dev, (uchar *)buffer, 
	// 	  sizeof(struct ethergram) + sizeof(struct arpgram));
	
	// sleep(1000);	
	
	// if (ARPPENDING != arptab[arpindex].state) { return OK; }

	// send(arptab[arpindex].waitingpid, TIMEOUT);
		
    return OK;
}

		

