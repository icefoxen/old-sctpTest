CC=gcc
CFLAGS=-O3 -Wall -lsctp

S_OBJ=server.o
S_OUTPUT=server

C_OBJ=client.o
C_OUTPUT=client

all: $(S_OUTPUT) $(C_OUTPUT)


.PHONY: clean nuke

clean:
	rm -f *.o
	rm -f *~

nuke: clean
	rm -f $(S_OUTPUT) $(C_OUTPUT)


$(S_OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $<

$(S_OUTPUT): $(S_OBJ)
	$(CC) $(CFLAGS) -o $(S_OUTPUT) $(S_OBJ)

$(C_OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $<

$(C_OUTPUT): $(C_OBJ)
	$(CC) $(CFLAGS) -o $(C_OUTPUT) $(C_OBJ)
