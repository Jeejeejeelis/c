struct tcpHeader {
    unsigned short sport;
    unsigned short dport;
    unsigned int seq;
    unsigned int acknowledgment;
    unsigned int offset;  // in bytes
    char ns;
    char cwr;
    char ece;
    char urg;
    char ack;
    char psh;
    char rst;
    char syn;
    char fin;
    unsigned int window;
    unsigned int checksum;
    unsigned int urgptr;
};

int getSourcePort(const unsigned char *tcphdr);
int getDestinationPort(const unsigned char *tcphdr);
void setSourcePort(unsigned char *tcphdr, int port);
void setDestinationPort(unsigned char *tcphdr, int port);
int getAckFlag(const unsigned char *tcphdr);
void setAckFlag(unsigned char *tcphdr, int flag);
int getDataOffset(const unsigned char *tcphdr);
void setDataOffset(unsigned char *tcphdr, int offset);
