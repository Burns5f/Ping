
#include <xinu.h>
#include <icmp.h>

/**
 * Swap and complete an arp request.
 *
 * @param *buf pointer to the ether pkt
 */
int echoReply(int dev, uchar *buf)
{

	struct ethergram *ether = (struct ethergram *)buf;
	struct ipgram *dgram = (struct ipgram*)ether->data; 
	struct icmpgram   *icmp = (struct icmpgram *)dgram->opts;
    uchar enet[ETH_ADDR_LEN];
    uchar ip[IP_ADDR_LEN];

    if (SYSERR == getmac(dev, enet))
    {
		buffree(buf);
        return SYSERR;
    }

    if (SYSERR == getip(dev, ip))
    {
		buffree(buf);
        return SYSERR;
    }

	// Check if request is for me.
    if (0 == memcmp(ip, dgram->dst, IP_ADDR_LEN))
    {
		memcpy(ether->dst, ether->src, ETH_ADDR_LEN);
		memcpy(ether->src, enet, ETH_ADDR_LEN);

        icmp->code = htons(ECHOREPLY);

        memcpy(dgram->dst, dgram->src, IP_ADDR_LEN);
        memcpy(dgram->src, ip, IP_ADDR_LEN);

		write(dev, (uchar *)buf, 
		  sizeof(struct ethergram) + sizeof(struct ipgram) + sizeof(struct icmpgram));
    }
    else
    {
		buffree(buf);
        return SYSERR;
    }
	buffree(buf);	
    return OK;
}
