LDLIBS := -lmosquitto -llog
LDFLAGS := -L../lib -Wl,-rpath='$$ORIGIN'/..lib
CFLAGS := -g -I../include
TARGET := publisher subscriber
DEPS := ../lib/liblog.so ../lib/libmosquitto.so
all: $(TARGET)

$(TARGET): $(DEPS)