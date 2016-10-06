TITLE_ID = NLTK00001
TARGET   = pluginsmanager
OBJS     = src/main.o src/draw.o src/font_data.o

LIBS = -lc -lSceKernel_stub -lSceDisplay_stub -lSceGxm_stub	\
	-lSceCtrl_stub -lSceTouch_stub

PREFIX  = arm-vita-eabi
CC      = $(PREFIX)-gcc
CFLAGS  = -Wl,-q -Wall -O3
ASFLAGS = $(CFLAGS)

all: clean $(TARGET).vpk

%.vpk: eboot.bin
	vita-mksfoex -s TITLE_ID=$(TITLE_ID) "$(TARGET)" param.sfo
	vita-pack-vpk -s param.sfo -b eboot.bin $@

eboot.bin: $(TARGET).velf
	vita-make-fself $< $@

%.velf: %.elf
	vita-elf-create $< $@

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

clean:
	@rm -rf $(TARGET).vpks $(TARGET).velf $(TARGET).elf $(OBJS) \
		eboot.bin param.sfo
