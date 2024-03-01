#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>

char host[128] = "localhost";
int port = 1883;
int keepalive = 60;
int qos = 0;
char report_topic[128] = "report";
char feedback_topic[128] = "feedback";

void usage(char* argv0)
{
    printf("Usage: %s [-h host] [-p port] [-t topic] [-q qos] [-k keepalive]\n", argv0);
    printf("       %s --help\n", argv0);
    printf("\n");
    printf("Options:\n");
    printf("  -h : mqtt host to connect to. Defaults to localhost.\n");
    printf("  -p : mqtt port to connect to. Defaults to 1883\n");
    printf("  -t : mqtt topic to subscribe to. Defaults to report:feedback\n");
    printf("  -q : quality of service level to use for the subscription. Defaults to 0.\n");
    printf("  -k : keep alive in seconds for this client. Defaults to 60.\n");
    printf("  --help : display this help and exit\n");
    printf("\n");
    printf("Examples:\n");
    printf("  %s -h localhost -p 1883 -t report:feedback\n", argv0);
}

void argparse(int argc, char* argv[])
{
    int opt;
    static int help_flag = 0;

    const char* optstr = "h:p:t:q:k:";
    static struct option long_options[] = {
        {"help", no_argument, &help_flag, 1},
        {NULL, 0, NULL, 0}
    };
    
    while ((opt = getopt_long(argc, argv, optstr, long_options, NULL)) != -1) {
        switch (opt)
        {
        case 'h':
            strncpy(host, optarg, strlen(optarg));
            break;
        case 'p':
            sscanf(optarg, "%d", &port);
            break;
        case 't':
        {
            char *separator = strchr(optarg, ':');
            strncpy(report_topic, optarg, separator - optarg);
            strncpy(feedback_topic, separator + 1, strlen(optarg) - 1 - (separator - optarg));
            printf("%s %s\n", report_topic, feedback_topic);
            break;
        }
        case 'q':
            sscanf(optarg, "%d", &qos);
            break;
        case 'k':
            sscanf(optarg, "%d", &keepalive);
            break;
        case 0:
            if (help_flag) {
                usage(argv[0]);
                exit(0);
        }
        default:
            printf("%s: invalid option -- '%c'\n", argv[0], opt);
            printf("Try '%s --help' for more information.\n", argv[0]);
            break;
        }
    }
}