#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "logger.h"

void write_log(const char *operation, const char *details, int success) {
    int log_fd = open("logs/operations.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (log_fd < 0) {
        perror("Error opening log file");
        return;
    }

    time_t now = time(NULL);
    char timestamp[64];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));

    char log_entry[512];
    snprintf(log_entry, sizeof(log_entry), "[%s] %s: %s - %s\n",
             timestamp, operation, details, success ? "SUCCESS" : "FAILURE");

    if (write(log_fd, log_entry, strlen(log_entry)) < 0) {
        perror("Error writing to log file");
    }

    close(log_fd);
}