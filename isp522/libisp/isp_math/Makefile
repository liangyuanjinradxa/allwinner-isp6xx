TARGET := libisp_math.a libisp_math.so
SUBLIB_DIR = ./..

SHARED_TARGET := libisp_math.so
STATIC_TARGET := libisp_math.a

commonSources:= \
	matrix.c \
    isp_math_util.c


OBJS = $(patsubst %.c, %.c.o, $(commonSources))

$(SHARED_TARGET):$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) $(local_CFLAGS) -o $@ $^ -fPIC -shared

$(STATIC_TARGET):$(OBJS)
	$(AR) rc $@ $^

$(OBJS):%.c.o:%.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(local_CFLAGS) -c $< -o $@ -fPIC


install: $(TARGET)
	mkdir -p $(INSTALL_PREFIX)/usr/lib
	install -m0755 $(TARGET) $(INSTALL_PREFIX)/usr/lib
	install -m0755 $(TARGET) $(SUBLIB_DIR)

all: install

clean:
	-rm $(OBJS) $(TARGET)
