#ifndef _PING_H_
#define _PING_H_

typedef struct ping_info_s {
    char dstip[16];
    unsigned ping_cur_send_cnt;
    unsigned ping_cur_recv_cnt;
    unsigned ping_cur_total_time;
    unsigned ping_min_time;
    unsigned ping_max_time;
    unsigned pint_total_cnt;
} ping_info_t;

extern int init_ping(unsigned pingcnt, const char *dstip);

extern int start_ping();

extern int unit_ping();

#endif //_PING_H_