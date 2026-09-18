CROSS_COMPILE ?=
CC := ${CROSS_COMPILE}gcc
CFLAGS  := -Wall -Wextra -g
TARGET  := writer
SRCS    := writer.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^


clean:
	rm -f $(TARGET)
