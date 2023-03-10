CC?=gcc
CFLAGS?=-O2
LDFLAGS?=-O2 -w -static
LIBS?=libfreetype.a libjpeg.a libpng16.a libz.a

CFLAGS += -I. -I./include -I/usr/include -I/usr/include/freetype2 -I/usr/include/freetype2/freetype
CFLAGS += -Wno-int-conversion -Wno-incompatible-pointer-types -Wno-pointer-to-int-cast -Wno-write-strings

OBJS:= \
	objs/image_bmp.o objs/image_jpg.o objs/image_png.o objs/images.o \
	objs/buffer.o objs/shapes.o objs/text.o \
	objs/utils.o objs/usage.o objs/splash.o

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
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBS) -o $@;

clean:
	rm -f $(OBJS) splash
