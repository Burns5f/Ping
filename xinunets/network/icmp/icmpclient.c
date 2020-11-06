/**
 * @file icmpclient.c
 * @provides icmpclient.
 *
 */
/* Embedded Xinu, Copyright (C) 2008.  All rights reserved. */

#include <xinu.h>
#include <icmp.h>

enum icmp_state state = ICMP_INIT;

/**
 * icmp client daemon.
 */
void icmpclient(int dev, struct netif *nif)
{
	int mesg = 0;
	int missed  = 0;
	uchar *packet = NULL;

	nif->state = NETIF_STATE_BINDING;
	while (1)
	{
		switch (state)
		{
		case ICMP_INIT:
			// send icmpDISCOVER
			echoRequest(dev);
			state = icmp_SELECTING;
			break;

		case icmp_SELECTING:
			// Read an offer
			mesg = recvtime(SELECT_WAIT * (missed + 1));
			if (TIMEOUT == mesg)
			{
				missed++;
				sendDiscover(dev);
				break;
			}
			// Select an offer
			// send icmpREQUEST
			packet = (uchar *)mesg;
			if(recvOffer(dev, nif, packet))
			{
				state = icmp_REQUESTING;
			}
			buffree(packet);
			break;

		case icmp_REQUESTING:
			// Read a NACK or an ACK
			if (1)
			{
				state = icmp_BOUND;
				// set a timer
				sleep(10000);
			}
			// NACK
			state = icmp_INIT;
			continue;
			break;

		case icmp_BOUND:
			// Timer expired
			// send icmpREQUEST
			state = icmp_RENEWING;
			// sleep for a while
			break;

		case icmp_RENEWING:
			// Send icmpREQUEST
			// If ACK
			if (1)
			{
				state = icmp_BOUND;
				// set a timer
				continue;
			}
			// If NACK
			if (0)
			{
				state = icmp_INIT;
				continue;
			}
			// If 75% expired
			state = icmp_REBINDING;
			break;

		case icmp_REBINDING:
			// If ACK
			if (1)
			{
				state = icmp_BOUND;
				// set a timer
				continue;
			}
			// If expired
			state = icmp_INIT;
			break;

		default:
			break;
		}
	}

	return;
}