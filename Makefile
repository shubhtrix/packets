all: packets

#install :
#	cp ./diff_eng ${TARGET_DIR}/bin/

BUILD_DIR = build 

CC=gcc
CC_FLAGS =  -I.
LD_FLAGS = -lpfring -lpcap
EXEC = packets 
SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.c=.o)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(LD_FLAGS) -o $(EXEC)

# To obtain object files
%.o: %.c $(HEADERS)
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -rf build $(EXEC) $(OBJECTS)

