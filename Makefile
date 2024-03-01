CFLAGS := -g -Iinclude
LDFLAGS := -Llib -Wl,-rpath='$$ORIGIN'/../lib
LDLIBS := -llog -lmosquitto

SHARED_EXE := src/publisher src/subscriber
STATIC_EXE := src/publisher_static src/subscriber_static
SHARED_LIBS := lib/liblog.so lib/libmosquitto.so
STATIC_LIBS := lib/liblog.a lib/libmosquitto.a
DEPS := include/common.h include/log.h include/mosquitto.h
SOVERSION := 1

.PHONY: default clean static shared
default: shared

static: $(STATIC_EXE)

shared: $(SHARED_EXE)

%_static: %.c src/argparse.c $(STATIC_LIBS) $(DEPS)
	$(CC) -static -static-libgcc $(CFLAGS) $< src/argparse.c $(LDFLAGS) $(LDLIBS) \
	-lssl -lcrypto -lrt -ldl -lpthread -o $@

%: %.c src/argparse.c $(SHARED_LIBS) $(DEPS)
	$(CC) $(CFLAGS) $< src/argparse.c $(LDFLAGS) $(LDLIBS) -o $@ 

lib/libmosquitto.a:
	$(MAKE) -C src/mosquitto/lib WITH_STATIC_LIBRARIES=yes WITH_SHARED_LIBRARIES=no; \
	cp src/mosquitto/lib/libmosquitto.a lib/libmosquitto.a

lib/libmosquitto.so:
	$(MAKE) -C src/mosquitto/lib; \
	cp src/mosquitto/lib/libmosquitto.so.1 lib/libmosquitto.so.1; \
	ln -sf libmosquitto.so.1 lib/libmosquitto.so

lib/liblog.a: src/log/log.o
	$(AR) cr $@ $^

lib/liblog.so: src/log/log.o
	$(CC) -shared -DLOG_USE_COLOR $^ -o lib/liblog.so.$(SOVERSION); \
	ln -sf liblog.so.$(SOVERSION) lib/liblog.so

src/log/log.o: src/log/log.c src/log/log.h
	$(CC) -fPIC -DLOG_USE_COLOR -c $< -o $@

clean:
	-rm -f src/publisher \
           src/publisher_static \
           src/subscriber \
           src/subscriber_static \
           src/log/log.o \
           lib/*
	$(MAKE) -C src/mosquitto/lib clean
