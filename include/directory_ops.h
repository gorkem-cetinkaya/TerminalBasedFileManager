#ifndef DIRECTORY_OPS_H
#define DIRECTORY_OPS_H

// Folder Listing
void list_files(const char *path);

// File and Folder Creation
void create_file(const char *path);
void create_folder(const char *path);

// File and Folder Deletion
void delete_file(const char *path);
void delete_folder(const char *path);

#endif