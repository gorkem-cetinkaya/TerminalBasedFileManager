CC = clang
CFLAGS = -Wall -Wextra -Iinclude
SRCS = src/main.c src/file_operations.c src/directory_ops.c src/permissions.c src/logger.c
OBJS = $(SRCS:.c=.o)
TARGET = bin/file_manager

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)

