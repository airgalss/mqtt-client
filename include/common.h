#include "mosquitto.h"
#include "log.h"

#define DISABLE_LOG false
#define LOG_LEVEL LOG_TRACE
#define BUF_SIZE 1024

extern void argparse(int, char*[]);

extern char host[128];
extern int port;
extern int keepalive;
extern char report_topic[128];
extern char feedback_topic[128];
extern int qos;