CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = 18_mywc
SRCS = 18_mywc.c mywc.c
OBJS := $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(TARGET)

# TODO: 在这里添加你的代码
$(TARGET): $(OBJS)
	$(CC) $^ -o $@

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
