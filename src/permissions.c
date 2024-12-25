#include <stdio.h>
#include <sys/stat.h>
#include "permissions.h"
#include "logger.h"

// Change File and Folder Permissions
void change_permissions(const char *path, int permissions) {
    if (chmod(path, permissions) == 0) {
        printf("Permissions of '%s' changed successfully to %o.\n", path, permissions);
        write_log("Change Permissions", path, 1);
    } else {
        perror("Error changing permissions");
        write_log("Change Permissions", path, 0);
    }
}