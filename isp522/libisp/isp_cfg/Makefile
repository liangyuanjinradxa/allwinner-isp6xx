TARGET := libisp_ini.so
LIBS := -liniparser
SUBLIB_DIR = ./..

commonSources:= \
	isp_ini_parse.c

local_CFLAGS := -I./SENSOR_H

OBJS = $(patsubst %.c, %.c.o, $(commonSources))

$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) $(local_CFLAGS) -o $@ $^  -fPIC -shared


$(OBJS):%.c.o:%.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(local_CFLAGS) -c $< -o $@  -fPIC -shared

install:$(TARGET)
	mkdir -p $(INSTALL_PREFIX)/usr/lib
	install -m0755 $(TARGET) $(INSTALL_PREFIX)/usr/lib
	cp  $(TARGET) $(SUBLIB_DIR)

all: install

clean:
	-rm $(OBJS) $(TARGET)
