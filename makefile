INC_DIR=include
OTHER_DIR=src
VPATH=$(OTHER_DIR)

CC=gcc
CFLAGS=-W -Wall -ansi -pedantic -I$(INC_DIR) -std=gnu99 -pthread
LDFLAGS=-pthread
EXEC=delivery

all: $(EXEC)

delivery: Client.o Drone.o MotherShip.o Package.o TrafficLanes.o  Weather.o main.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
