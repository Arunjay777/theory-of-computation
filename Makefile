# Makefile for Theory of Computation (CSA13) Lab Experiments
# Saveetha School of Engineering

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2

SRCS = $(wildcard [0-9][0-9]_*.c)
BINS = $(SRCS:.c=)

.PHONY: all clean test

all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(BINS)

test: all
	@echo "All 17 Theory of Computation programs compiled successfully!"
