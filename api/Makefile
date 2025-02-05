OBJECTS=gpio.o systick.o timer.o uart.o utils.o rcc.o err.o
INCLUDE=-I ../include/api

all: $(OBJECTS)

%.o: %.c
	$(CC) $(INCLUDE) $(CFLAGS) $^ -o $@
clean:
	rm -fr *.o
