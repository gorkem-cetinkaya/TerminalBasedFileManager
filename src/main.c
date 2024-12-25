#include <stdio.h>
#include <stdlib.h>
#include "directory_ops.h"
#include "file_operations.h"
#include "logger.h"
#include "permissions.h"

void show_menu() {
    printf("\nTerminal Based File Manager\n");
    printf("1. List files in a directory\n");
    printf("2. Create a file\n");
    printf("3. Create a folder\n");
    printf("4. Delete a file\n");
    printf("5. Delete a folder\n");
    printf("6. Copy a file\n");
    printf("7. Move a file\n");
    printf("8. Display a file\n");
    printf("9. Search for a file\n");
    printf("10. Change file or folder permissions\n");
    printf("11. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    char path[256];

    while (1) {
        show_menu();
        scanf("%d", &choice);

        switch (choice) {
            // 1. Folder Listing
            case 1:
                printf("Enter directory path: ");
                scanf("%s", path);
                list_files(path);
                break;

            // 2. File and Folder Creation
            case 2:
                {
                    printf("Enter file path to create: ");
                    scanf("%s", path);
                    create_file(path);
                }
                break;

            case 3:
                {
                    printf("Enter folder path to create: ");
                    scanf("%s", path);
                    create_folder(path);
                }
                break;

            // 3. File and Folder Deletion
            case 4:
                {
                    printf("Enter file path to delete: ");
                    scanf("%s", path);
                    delete_file(path);
                }
                break;
            case 5:
                {
                    printf("Enter folder path to delete: ");
                    scanf("%s", path);
                    delete_folder(path);
                }
                break;

            // 4. File Copying and Moving
            case 6:
                {
                    char source[256], destination[256];
                    printf("Enter source file path: ");
                    scanf("%s", source);
                    printf("Enter destination file path: ");
                    scanf("%s", destination);
                    copy_file(source, destination);
                }
                break;

            case 7:
                {
                    char source[256], destination[256];
                    printf("Enter source file path: ");
                    scanf("%s", source);
                    printf("Enter destination file path: ");
                    scanf("%s", destination);
                    move_file(source, destination);
                }
                break;

            // 5. File Display
            case 8:
                {
                    printf("Enter file path to display: ");
                    scanf("%s", path);
                    display_file(path);
                }
                break;

            // 6. File Search
            case 9:
                {
                    char directory[256], filename[256];
                    printf("Enter directory to search: ");
                    scanf("%s", directory);
                    printf("Enter filename to search for: ");
                    scanf("%s", filename);
                    search_file(directory, filename);
                }
                break;

            // 7. Change File and Folder Permissions
            case 10:
                {
                    int permissions;
                    printf("Enter file or folder path: ");
                    scanf("%s", path);
                    printf("Enter new permissions (e.g., 0644): ");
                    scanf("%o", &permissions);
                    change_permissions(path, permissions);
                }
                break;

            case 11:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}