CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -O2
LDFLAGS = -lm

SRCS = src/main.c src/frame.c src/render.c src/utils.c
OUT = bin/magnoquill

all:
	@mkdir -p bin
	$(CC) $(CFLAGS) $(SRCS) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OUT)

