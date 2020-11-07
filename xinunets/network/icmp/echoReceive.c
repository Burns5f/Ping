/* echoReceive.c - echoReceive */

#include <xinu.h>
#include "icmp.h"

/*------------------------------------------------------------------------
 * echoReceive - Demultiplex incoming icmp packets
 *------------------------------------------------------------------------
 */
void echoReceive(int dev, uchar *packet)
{
	struct ethergram *ether = (struct ethergram *)packet;
	struct ipgram *dgram = (struct ipgram*)ether->data; 
	struct icmpgram   *icmp = (struct icmpgram *)dgram->opts;
	int i;
	
	switch (ntohs(icmp->type))
	{
	case ECHO:
		echoReply(dev, packet);
		break;
	case ECHOREPLY:
		printf("EchoReply recieved");
		// fprintf(stderr, "Gratuitous ARP reply.\n");
		buffree(packet);
		break;
	default:
		fprintf(stderr, "Unknown icmpgram!\n");
		buffree(packet);
	}

}