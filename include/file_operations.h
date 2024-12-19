#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

// 1. Folder Listing
void list_files(const char *path);

// 2. File and Folder Creation
void create_file(const char *path);
void create_folder(const char *path);

// 3. File and Folder Deletion
void delete_file(const char *path);
void delete_folder(const char *path);

// 4. File Copying and Moving
void copy_file(const char *source, const char *destination);
void move_file(const char *source, const char *destination);

// 5. File Display
void display_file(const char *path);

// 6. File Search
void search_file(const char *directory, const char *filename);

// 7. Change File and Folder Permissions
void change_permissions(const char *path, int permissions);

// 8. Application Log (Logging)
// (Not declared here but assumed to be in logger.h)

#endif
