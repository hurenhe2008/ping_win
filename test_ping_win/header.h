#ifndef _COMMDEF_H_
#define _COMMDEF_H_


#pragma pack(1)


//MAC header and tail
typedef struct mac_hdr_s{
    unsigned char  dst_mac_addr[6];    //destination mac address
    unsigned char  src_mac_addr[6];    //source mac address
    unsigned short type;               //the upper protocal type: 0x0800-->IP 0x0806-->arp
} mac_hdr_t;

typedef struct mac_tail_s{
    unsigned int   check_sum;          //check sum 
} mac_tail_t;


//IP header
typedef struct ip_hdr_s{
    unsigned char  version  : 4;   //ip version
    unsigned char  head_len : 4;   //ip header len
    unsigned char  tos;            //type of service
    unsigned short total_len;      //ip package total length
    unsigned short id;             //identify
    unsigned short flag_slice;     //flag and slice info
    unsigned char  ttl;            //ttl
    unsigned char  proto;          //the upper protocal type:  ICMP(1) IGMP(2) TCP(6) UDP(17)
    unsigned short check_sum;      //check sum
    unsigned int   src_ip;         //source ip address
    unsigned int   dst_ip;         //destination ip address
    //option field
} ip_hdr_t;


//ICMP header
typedef struct icmp_hdr_s{
    unsigned char  type;          //type: ECHO¡¢ECHO_REPLY
    unsigned char  code;          //code: 0 
    unsigned short check_sum;     //check sum 
    unsigned short id;            //id: identify 
    unsigned short seqno;         //seqno: sequence number 
    unsigned long  data;          //data 
}icmp_hdr_t;

//IGMP header
typedef struct igmp_hdr_s{
    unsigned char  version : 4;   //version
    unsigned char  type    : 4;   //type: 1-2   (1-->route send query datagram, 2-->host send report datagram)
    unsigned char  reverse;       //reverse field
    unsigned short check_sum;     //check sum
    unsigned int   group_addr;    //group address (D class ip)
}igmp_hdr_t;


//TCP header
typedef struct tcp_hdr_s{
    unsigned short src_port;       //source port
    unsigned short dst_port;       //destination port
    unsigned int   seqno;          //sequence number
    unsigned int   ackno;          //ack number
    unsigned short headlen_flag;   //header length(4 bit) -- middle reserve(6 bit) -- flags(6 bit)
    unsigned short win_size;       //window size
    unsigned short check_sum;      //check sum
    unsigned short urgency_pt;     //urgency pointer
    //option field
}tcp_hdr_t;


//UDP header
typedef struct udp_hdr_s{
    unsigned short src_port;       //source port
    unsigned short dst_port;       //destination port
    unsigned short pack_len;       //data package length
    unsigned short check_sum;      //check sum
}udp_hdr_t;


#pragma pack()


#endif //_COMMDEF_H_


/*
--------------------- ISO (7 level layer) ---------------------
[application layer]
                HTTP - SIP                                    

---------------------------------------------------------------
[session layer]
                SSL

---------------------------------------------------------------
[transport layer]
                TCP - UDP

---------------------------------------------------------------
[ip layer]
                ICMP - IGMP

                     IP

---------------------------------------------------------------
[data link layer]
                ARP - RARP

---------------------------------------------------------------
[physical layer]


---------------------------------------------------------------
*/


