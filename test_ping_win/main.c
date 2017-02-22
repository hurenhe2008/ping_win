#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "ping.h"

static void signal_intr(int signo);

static void print_help();

static void print_ping_result();

extern ping_info_t g_ping_info;


int main(int argc, char *argv[])
{
    /*capture "Ctrl + C" signal*/
    signal(SIGBREAK, &signal_intr);

    if (argc != 2) {
        printf("");
        exit(0);
    }

    if (0 == strcmp(argv[1], "-h") ||
        0 == strcmp(argv[1], "/?") ||
        0 == strcmp(argv[1], "help")) {
        print_help();
        exit(0);
    }

    if (0 != init_ping(argv[1], 10)) {
        printf("init ping failed!");
        getchar();
        exit(-1);
    }

    if (0 != start_ping()) {
        printf("start ping failed!");
    }
    else {
        print_ping_result();
    }

    if (0 != unit_ping()) {
        printf("unit ping failed!");
        getchar();
        exit(-1);
    }

    return 0;
}

void print_help()
{
    printf("================= help ==================\n");
    printf("command line input format:               \n");
    printf("    pint [-h][/?][help][ip]              \n");
    printf("                                         \n");
    printf("parameter:                               \n");
    printf("    -h     --> help                      \n");
    printf("    /?     --> help                      \n");
    printf("    help   --> help                      \n");
    printf("    ip     --> ping dest ip addr         \n");
    printf("=========================================\n");
}

void signal_intr(int signo)
{
    print_ping_result();

    printf("Control-C\n");
    printf("^C\n");
}

void print_ping_result()
{
    unsigned send = g_ping_info.ping_cur_send_cnt;
    unsigned recv = g_ping_info.ping_cur_recv_cnt;
    unsigned lose = send - recv;
    float loserate = (0 == send) ? 0 : lose / send;
    unsigned mintime = g_ping_info.ping_min_time;
    unsigned maxtime = g_ping_info.ping_max_time;
    unsigned averagetime = g_ping_info.ping_cur_total_time / recv;

    printf("\n%s 's ping statistics information: \n", g_ping_info.dstip);
    printf("    package: send = %d, recv=%d, lose = %d (lose rate:%f)",
        send, recv, lose, loserate);
    printf("estimated spend time on roundtrip (ms): \n");
    printf("    min-time: %d ms, max-time:%d ms, average-time:%d ms\n",
        mintime, maxtime, averagetime);
}