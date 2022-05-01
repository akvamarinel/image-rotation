IDIR = ../include
TARGET_DIR = ../build
ODIR = $(TARGET_DIR)/obj
CC = clang
FLAGS = -g -O2 -Wextra -Wall -std=c17 -fsanitize=address,undefined,leak -I $(IDIR)

all: $(TARGET_DIR)/main

$(ODIR)/%.o: %.c $(IDIR)/%.h
	$(CC) -c -o $@ $< $(FLAGS)

$(ODIR)/main.o: main.c
	$(CC) -c -o $@ $< $(FLAGS)

$(TARGET_DIR)/main: $(ODIR)/main.o $(ODIR)/image.o $(ODIR)/bmp.o $(ODIR)/rotation.o  $(ODIR)/serialization.o $(ODIR)/find_error.o $(ODIR)/errors_types.o
	$(CC) -o $@ $^ $(FLAGS)

clean:
	rm -rf $(ODIR)/*.o $(TARGET_DIR)/main

.PHONY: clean

