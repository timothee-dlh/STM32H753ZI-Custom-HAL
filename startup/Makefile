OBJECTS=startup.o

INCLUDE=-I ../include/api -I ../include

all: $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) $^ -o $@
clean:
	rm -fr *.o
