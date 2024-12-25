#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

// File Copying and Moving
void copy_file(const char *source, const char *destination);
void move_file(const char *source, const char *destination);

// File Display
void display_file(const char *path);

// File Search
void search_file(const char *directory, const char *filename);

#endif