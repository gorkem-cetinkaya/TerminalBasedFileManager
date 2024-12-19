#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "file_operations.h"
#include "logger.h"

// 1. Folder Listing
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

// 2. File and Folder Creation
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

// 3. File and Folder Deletion
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

// 4. File Copying and Moving
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

// 5. File Display
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

// 6. File Search
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

// 7. Change File and Folder Permissions
void change_permissions(const char *path, int permissions) {
    if (chmod(path, permissions) == 0) {
        printf("Permissions of '%s' changed successfully to %o.\n", path, permissions);
        write_log("Change Permissions", path, 1);
    } else {
        perror("Error changing permissions");
        write_log("Change Permissions", path, 0);
    }
}
