#include "mosquitto.h"
#include "log.h"

#define DISABLE_LOG false
#define LOG_LEVEL LOG_TRACE
#define BUF_SIZE 1024

const char *host = "127.0.0.1";
const int port = 1883;
const int keepalive_sec = 60;
const char *report_topic = "report";
const char *feedback_topic = "feedback";
const bool retain = false;
const int qos = 0;
const int timeout = 600;