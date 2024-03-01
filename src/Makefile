LDLIBS := -lmosquitto -llog
LDFLAGS := -L../lib -Wl,-rpath='$$ORIGIN'/..lib
CFLAGS := -g -I../include
all: publisher subscriber ../lib/liblog.so

../lib/liblog.so.1: log/src/log.c log/src/log.h
	$(CC) -fPIC -shared -DLOG_USE_COLOR -c $< -o $@; \
	cd ../lib; \
	ln -sf liblog.so.1 liblog.so