#include "ping.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <WinSock2.h>
#include <ipmib.h>
#include <string.h>
#include "header.h"

#pragma comment(lib, "ws2_32.lib")

ping_info_t g_ping_info = { 0, 0, 0, 0, 0, 0, 0 };

static SOCKET s_icmp_sock = INVALID_SOCKET;


int init_ping(unsigned pingcnt, const char *dstip)
{
    WSADATA data;
    u_long nonblockflag = 1;
    
    if (!dstip || !pingcnt) {
        return -1;
    }

    g_ping_info.pint_total_cnt = pingcnt;
    memcpy_s(g_ping_info.dstip, 15, dstip, 15);

    if (0 != WSAStartup(MAKEWORD(2, 2), &data)) {
        return -2;
    }

    if (INVALID_SOCKET == 
        (s_icmp_sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP))) {
        unit_ping();
        return -3;
    }

    if (0 != ioctlsocket(s_icmp_sock, FIONBIO, &nonblockflag)) {
        unit_ping();
        return -4;
    }

    return 0;
}

int start_ping()
{
    struct sockaddr_in dstaddr;
    struct timeval timeout = { 1, 0 };
    fd_set fdset;
    int ret = 0, sendno = 0, err = 0;

    dstaddr.sin_family = AF_INET;
    dstaddr.sin_addr.s_addr = inet_addr(g_ping_info.dstip);
    dstaddr.sin_port = htons(0);

    icmp_hdr_t icmp;
    icmp.type = ICMP4_ECHO_REQUEST;
    icmp.code = 0;   
    icmp.id = GetCurrentProcessId();
    icmp.check_sum = 0;   /*need to checksum*/
    icmp.seqno = sendno;
    icmp.data = GetTickCount();


    while (1) {
        FD_ZERO(&fdset);
        FD_SET(s_icmp_sock, &fdset);

        
        ret = sendto(s_icmp_sock, (char *)&icmp, sizeof(icmp_hdr_t), 0,
            (struct sockaddr *)&dstaddr, sizeof(struct sockaddr_in));

        if (ret < 0) {
            break;
        }

        ret = select(s_icmp_sock + 1, &fdset, NULL, NULL, &timeout);

        if (ret < 0) {
            err = WSAGetLastError();
            if (WSAEINTR == err || WSAEWOULDBLOCK == err) {
                continue;
            }
            break;
        }


        


    }

    return 0;
}

int unit_ping()
{
    if (INVALID_SOCKET != s_icmp_sock) {
        closesocket(s_icmp_sock);
        s_icmp_sock = INVALID_SOCKET;
    }

    WSACleanup();
    return 0;
}