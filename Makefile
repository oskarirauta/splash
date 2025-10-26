CC?=gcc
CFLAGS?=-O2
LDFLAGS?=-O2 -w -static
EXTRA_LDFLAGS?=

WITH_JPEG?=0
WITH_BMP?=0

LIBFREETYPE?=libfreetype.a
LIBJPEG?=libjpeg.a
LIBPNG?=libpng16.a
LIBZ?=libz.a
EXTRA_LIBS?=

LIBS:=$(LIBFREETYPE) $(LIBPNG) $(LIBZ)

CFLAGS += -I. -I./include -I/usr/include -I/usr/include/freetype2 -I/usr/include/freetype2/freetype
CFLAGS += -Wno-int-conversion -Wno-incompatible-pointer-types -Wno-pointer-to-int-cast -Wno-write-strings

OBJS:= \
	objs/image_png.o objs/images.o objs/buffer.o \
	objs/shapes.o objs/text.o objs/utils.o \
	objs/usage.o objs/splash.o

ifeq ($(WITH_JPEG),1)
	LIBS += $(LIBJPEG)
	CFLAGS += -DWITH_JPEG=1
	OBJS += objs/image_jpg.o
endif

ifeq ($(WITH_BMP),1)
	CFLAGS += -DWITH_BMP=1
	OBJS += objs/image_bmp.o
endif

all: splash

objs/image_bmp.o: src/image_bmp.c
	$(CC) $(CFLAGS) -c -o $@ $<;

objs/image_jpg.o: src/image_jpg.c
	$(CC) $(CFLAGS) -c -o $@ $<;

objs/image_png.o: src/image_png.c
	$(CC) $(CFLAGS) -c -o $@ $<;

objs/images.o: src/images.c
	$(CC) $(CFLAGS) -c -o $@ $<;

objs/buffer.o: src/buffer.c
	$(CC) $(CFLAGS) -c -o $@ $<;

objs/shapes.o: src/shapes.c
	$(CC) $(CFLAGS) -c -o $@ $<;

objs/text.o: src/text.c
	$(CC) $(CFLAGS) -c -o $@ $<;

objs/utils.o: src/utils.c
	$(CC) $(CFLAGS) -c -o $@ $<;

objs/usage.o: src/usage.c
	$(CC) $(CFLAGS) -c -o $@ $<;

objs/splash.o: src/splash.c
	$(CC) $(CFLAGS) -c -o $@ $<;

splash: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(EXTRA_LDFLAGS) $(OBJS) $(LIBS) $(EXTRA_LIBS) -o $@;

clean:
	rm -f $(OBJS) splash
