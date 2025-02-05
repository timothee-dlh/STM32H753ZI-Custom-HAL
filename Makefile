export CC=arm-none-eabi-gcc
export MACH=cortex-m7
export CFLAGS= -Wextra -Werror -Wundef -Wshadow -Wdouble-promotion \
            -Wformat-truncation -fno-common -Wconversion \
            -g3 -Os -ffunction-sections -fdata-sections -c -mcpu=$(MACH) -mthumb -O0 -std=gnu17 -Wall -ggdb 

export LDFLAGS= -T link.ld -nostartfiles -nostdlib --specs nano.specs -lc -lgcc -Wl,--gc-sections -Wl,-Map=$@.map

INCLUDES=-I include/api -I include
DIRS=startup api
SUB_OBJECTS = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.o))

all: subdirs firmware.bin

.PHONY: subdirs $(DIRS)

subdirs: $(DIRS)
$(DIRS):
	$(MAKE) -C $@

main.o: main.c 
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

firmware.elf: main.o
	$(CC) $(LDFLAGS) $(SUB_OBJECTS) $^ -o $@

firmware.bin: firmware.elf
	arm-none-eabi-objcopy -O binary $< $@
	mkdir -p ../build
	mv firmware.??? ../build
	
flash: firmware.bin
	st-flash --reset write ../build/firmware.bin 0x08000000

load:
	openocd -f $(HOME)/st_nucleo_h743zi.cfg

load_gdb:
	arm-none-eabi-gdb final.elf

.PHONY: clean

htmldocs:
	sphinx-build -b html ../Documentation/source ../Documentation/build

clean:
	rm -rf *.o *.elf *.map
	for dirs in $(DIRS); do\
		$(MAKE) -C $$dirs -f Makefile $@;\
	done
minicom:
	sudo minicom --device /dev/ttyUSB0 --baudrate 9600 -con

comment:
	@echo "Changed -std=gnu11 to 17, no apparent effect, still to verify"
