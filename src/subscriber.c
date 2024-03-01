#include "common.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

char *feedback_file = "../data/response.json";

void on_publish(struct mosquitto *mosq, void *obj, int mid){
    log_info("Published message successfully");

    int status;
    status = mosquitto_disconnect(mosq);
    if(status != 0){
        log_error("Failed to disconnect from the broker");
        return;
    }
    log_info("Disconnect from the broker");
}

void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg){
    log_info("Received message with length %d on the topic \"%s\" successfully", msg->payloadlen, msg->topic);
    printf("%s\n", (char *)msg->payload);
    log_info("Start to response to the publisher");

    FILE *file = fopen(feedback_file, "r");
    if(file == NULL){
       log_error("Failed to open message file %s: %s", feedback_file, strerror(errno));
       return;
    }

    int status;
    char message[BUF_SIZE] = {'\0'};
    int len = fread(message, sizeof(char), BUF_SIZE, file);
    fclose(file);

    status = mosquitto_publish(mosq, NULL, feedback_topic, len, message, qos, retain);
    if(status != 0){
        log_error("Failed to publish a message");
        return;
    }
    log_info("Publishing message with length %d on the topic \"%s\" successfully", len, feedback_topic);
    printf("%s\n", message);
}

int main(){
    int status;
    struct mosquitto *mosq;

    log_set_quiet(DISABLE_LOG);
    log_set_level(LOG_LEVEL);
    mosquitto_lib_init();

    mosq = mosquitto_new(NULL, true, NULL);
    if(mosq == NULL){
        log_error("Failed to create a new mosquitto client instance");
        return 1;
    }

    mosquitto_message_callback_set(mosq, on_message);
    mosquitto_publish_callback_set(mosq, on_publish);

    status = mosquitto_connect(mosq, host, port, keepalive_sec);
    if(status != 0){
        log_error("Failed to connect to a broker");
        return 1;
    }
    log_info("Connected the broker %s:%d successfully", host, port);

    status = mosquitto_subscribe(mosq, NULL, report_topic, qos);
    if(status != 0){
        log_error("Failed to subscribe to topic %s", report_topic);
        return 1;
    }
    log_info("Subscribe the topic \"%s\" successfully", report_topic);

    status = mosquitto_loop_forever(mosq, timeout, 1);
    if(status != 0){
        log_error("Failed to continue event loop");
        return 1;
    }
    log_info("End event loop");
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
}