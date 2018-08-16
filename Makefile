TARGETS = fmt

.PHONY: all clean

all: $(TARGETS)

clean:
	-rm $(TARGETS)

BUILD_CMD_PREFIX = $(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS)

.c:
	$(BUILD_CMD_PREFIX) -o $@ $<
