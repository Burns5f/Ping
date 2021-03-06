#
#  Makefile for MIPS(EL) XINU.
#

include makeVars

BOOTIMAGE = xinu.boot

LIB       = ../lib

LDFLAGS   = -static --gc-sections -no-warn-mismatch -T ld.script

$(VERBOSE).SILENT:

#-----------------------------------------------------------------------
# source files
#-----------------------------------------------------------------------

# SHELL
SHLL = xsh_test.c shell-commands.c xsh_dhcpsnoop.c xsh_arp.c xsh_netstat.c xsh_ping.c
NET  = netInit.c netDaemon.c netUtils.c \
		dhcp/client.c dhcp/sendDiscover.c dhcp/recvOffer.c \
		arp/arpInit.c arp/arpReceive.c arp/arpReply.c arp/arpResolve.c \
		icmp/echoRequest.c icmp/echoReply.c icmp/echoReceive.c

SRC =	${SHLL:%.c=../shell/%.c} \
		${NET:%.c=../network/%.c}

KRNOBJ = ${SRC:%.c=%.o}

#-----------------------------------------------------------------------
# make targets
#-----------------------------------------------------------------------
all: ${BOOTIMAGE} 

${BOOTIMAGE}: ${LIB}/xinu-os.a ${KRNOBJ} ld.script ${LIB}/libxc.a 
	@echo -e "\tLinking" $@
	${LD} -o $@ ${LDFLAGS} --whole-archive ${LIB}/xinu-os.a ${KRNOBJ} --whole-archive ${LIB}/libxc.a

%.o: %.c
	@echo -e "\tCompiling" $@
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.S
	@echo -e "\tAssembling" $@
	$(CC) $(CFLAGS) -o $@ $<

clean:
	@echo -e "\tCleaning all objects"
	rm -f *.o ${KRNOBJ} ${BOOTIMAGE}

depclean:
	@echo -e "\tCleaning dependencies"
	rm -f .deps
	touch .deps

realclean: clean depclean
	@echo -e "\tCleaning EVERYTHING"
	rm -f vn version
	rm -f Makefile.bak
	rm -f xinu-disk

depend:
	@echo -e "\tBuilding dependencies"
	${MAKEDEP} -I../include $(LDRASM) $(SYSASM) $(SRC) > .deps

#-----------------------------------------------------------------------
# targets for files outside of this directory
#-----------------------------------------------------------------------

include .deps
