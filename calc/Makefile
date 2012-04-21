all: earth_info

CFLAGS=-Wall -g -O2
SPICE_DIR=$(HOME)/lib/cspice
INC=-I$(SPICE_DIR)/include
LIB=$(SPICE_DIR)/lib/cspice.a -lm

OBJS=main.o my_location.o

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INC)

earth_info: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIB)

clean:
	$(RM) $(OBJS) earth_info
