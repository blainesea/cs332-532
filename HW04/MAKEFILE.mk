# Makefile for compiling the job scheduler program

CC = gcc
CFLAGS = -Wall -g
PTHREADS = -pthread

# Name of the executable
TARGET = job_scheduler

# Source and object files
SRCS = main.c
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(PTHREADS)

# To obtain object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< $(PTHREADS)

# To remove generated files
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
