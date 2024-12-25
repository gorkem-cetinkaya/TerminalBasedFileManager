#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include "directory_ops.h"
#include "logger.h"

// Folder Listing
void list_files(const char *path) {
    struct dirent *entry;
    DIR *dp = opendir(path);

    if (dp == NULL) {
        perror("opendir");
        write_log("List Files", path, 0);
        return;
    }

    while ((entry = readdir(dp))) {
        printf("%s\n", entry->d_name);
    }

    closedir(dp);
    write_log("List Files", path, 1); 
}

// File and Folder Creation
void create_file(const char *path) {
    int fd = creat(path, 0644);
    if (fd < 0) {
        perror("Error creating file");
        write_log("Create File", path, 0);
    } else {
        printf("File '%s' created successfully.\n", path);
        write_log("Create File", path, 1);
        close(fd);
    }
}

void create_folder(const char *path) {
    if (mkdir(path, 0755) == 0) { // Klasörü 0755 izinleriyle oluştur
        printf("Folder '%s' created successfully.\n", path);
        write_log("Create Folder", path, 1);
    } else {
        perror("Error creating folder");
        write_log("Create Folder", path, 0);
    }
}

// File and Folder Deletion
void delete_file(const char *path) {
    if (unlink(path) == 0) {
        printf("File '%s' deleted successfully.\n", path);
        write_log("Delete File", path, 1);
    } else {
        perror("Error deleting file");
        write_log("Delete File", path, 0);
    }
}

void delete_folder(const char *path) {
    DIR *dir = opendir(path);
    struct dirent *entry;

    if (!dir) {
        perror("Failed to open directory");
        write_log("Delete Folder", path, 0);
        return;
    }

    int is_empty = 1;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            is_empty = 0;
            break;
        }
    }
    closedir(dir);

    if (is_empty) {
        if (rmdir(path) == 0) {
            printf("Folder '%s' deleted successfully.\n", path);
            write_log("Delete Folder", path, 1);
        } else {
            perror("Failed to delete folder");
            write_log("Delete Folder", path, 0);
        }
    } else {
        printf("Folder '%s' is not empty. Cannot delete.\n", path);
        write_log("Delete Folder", path, 0);
    }
}