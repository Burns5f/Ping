/* ICMP Packet Structure */
#define Nicmp 10
#define ECHOREPLY 0
#define ECHO      8 
#define ICMP_PAYLOAD_LENGTH 18
#define ICMP_HEADER_LENGTH 4


struct icmpgram
{
	uchar type;
	uchar code;
	ushort checksum;
	ushort identifier;
	ushort seqnum;
	uchar data[1];
}; 

int echoRequest(int dev, uchar *ipaddr);

int echoReply(int dev, uchar *buf);

int echoResolve(uchar *ipaddr);

void echoReceive(int dev, uchar *packet);