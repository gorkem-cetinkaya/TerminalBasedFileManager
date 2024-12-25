#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "file_operations.h"
#include "logger.h"

// File Copying and Moving
void copy_file(const char *source, const char *destination) {
    int src_fd, dest_fd;
    char buffer[1024];
    ssize_t bytes_read;

    src_fd = open(source, O_RDONLY);
    if (src_fd < 0) {
        perror("Error opening source file");
        write_log("Copy File", source, 0);
        return;
    }

    dest_fd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("Error creating destination file");
        close(src_fd);
        write_log("Copy File", destination, 0);
        return;
    }

    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
        if (write(dest_fd, buffer, bytes_read) != bytes_read) {
            perror("Error writing to destination file");
            write_log("Copy File", destination, 0); 
            break;
        }
    }

    if (bytes_read < 0) {
        perror("Error reading source file");
        write_log("Copy File", source, 0);
    } else {
        printf("File copied successfully from %s to %s\n", source, destination);
        write_log("Copy File", destination, 1);
    }

    close(src_fd);
    close(dest_fd);
}

void move_file(const char *source, const char *destination) {
    if (rename(source, destination) == 0) {
        printf("File moved successfully from '%s' to '%s'.\n", source, destination);
        write_log("Move File", source, 1);
    } else {
        perror("Error moving file");
        write_log("Move File", source, 0);
    }
}

// File Display
void display_file(const char *path) {
    int fd = open(path, O_RDONLY); 
    if (fd < 0) {
        perror("Error opening file");
        write_log("Display File", path, 0);
        return;
    }

    char buffer[1024];
    ssize_t bytes_read;

    printf("Contents of '%s':\n", path);

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read) {
            perror("Error displaying file content");
            write_log("Display File", path, 0);
            close(fd);
            return;
        }
    }

    if (bytes_read < 0) {
        perror("Error reading file");
        write_log("Display File", path, 0);
    } else {
        write_log("Display File", path, 1);
    }

    close(fd);
}

// File Search
void search_file(const char *directory, const char *filename) {
    struct dirent *entry;
    DIR *dp = opendir(directory);

    if (dp == NULL) {
        perror("Error opening directory");
        write_log("Search File", directory, 0);
        return;
    }

    int found = 0;
    while ((entry = readdir(dp))) {
        if (strcmp(entry->d_name, filename) == 0) {
            printf("File '%s' found in directory '%s'.\n", filename, directory);
            found = 1;
            break;
        }
    }

    closedir(dp);

    if (!found) {
        printf("File '%s' not found in directory '%s'.\n", filename, directory);
        write_log("Search File", filename, 0);
    } else {
        write_log("Search File", filename, 1);
    }
}
