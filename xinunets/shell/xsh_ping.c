 /**
 * @file     xsh_ping.c
 * @provides xsh_ping
 *
 */
/* Embedded XINU, Copyright (C) 2009.  All rights reserved. */
 
#include <xinu.h>
#include "../network/icmp/icmp.h"

/**
 * Shell command (netstat) displays status of net interface status
 * @param nargs count of arguments in args
 * @param args array of arguments
 * @return OK for success, SYSERR for syntax error
 */
command xsh_ping(int nargs, char *args[])
{
    uchar ipaddr[IP_ADDR_LEN];

    if (nargs > 1)
    {
        fprintf(stderr, "ping: too many arguments\n");
        fprintf(stderr, "Try 'kill --help' for more information\n");
        return 1;
    }

	if (OK != dot2ip(args[1], ipaddr))
	{
		fprintf(stderr, "Could not parse IP address \"%s\"\n", args[1]);
		return 1;
	}

    if (OK != echoResolve(ipaddr))
	{
		fprintf(stdout, "Could not resolve %s\n", args[1]);
		return 1;
	}
	

	return OK;
}