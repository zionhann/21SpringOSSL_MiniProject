CC = gcc
CCFLAGS = -W -Wall
OBJ = main.c product.o manager.o
TARGET = shop
DTARGET = shop_debug

all : $(TARGET) $(DTARGET)

$(TARGET) : $(OBJ)
	$(CC) $(CCFLAGS) $^ -o $@

$(DTARGET) : $(OBJ)
	$(CC) $(CCFLAGS) -DDEBUG $^ -o $@
clean :
	rm -f *.o $(TARGET) $(DTARGET)
