CROSS_COMPILE ?= 
CC = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -Wextra -pedantic
SRC = writer.c
TARGET = writer

all: $(TARGET)

$(TARGET):$(SRC)
	@echo "building using ($(CC))...."
	$(CC) -o $(TARGET) $(CFLAGS) $(SRC) 

clean:
	@echo "Removing writer application and .o files" 
	rm -rf $(TARGET)
	rm -rf *.o
