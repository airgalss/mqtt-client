SHELL := bash
LDFLAGS := -Wl,-rpath='$$ORIGIN'/..lib
CFLAGS := -g -Iinclude
TARGET := src/publisher src/subscriber
DEPS := lib/liblog.so lib/libmosquitto.so
.PHONY: clean

all: $(TARGET)

$(TARGET): $(DEPS)

lib/libmosquitto.so:
	$(MAKE) -C src/mosquitto/lib; \
	cp src/mosquitto/lib/libmosquitto.so.1 lib/libmosquitto.so.1; \
	ln -sf libmosquitto.so.1 lib/libmosquitto.so

lib/liblog.so: src/log/src/log.c src/log/src/log.h
	$(CC) -fPIC -shared -DLOG_USE_COLOR -c $< -o lib/liblog.so.1; \
	ln -sf liblog.so.1 lib/liblog.so

clean:
	rm -f src/{publisher,subscriber} lib/*
	$(MAKE) -C src/mosquitto/lib clean