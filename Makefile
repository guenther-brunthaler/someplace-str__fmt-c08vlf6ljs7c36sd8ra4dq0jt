TARGETS = fmt

.PHONY: all clean

all: $(TARGETS)

clean:
	-rm $(TARGETS)

CC_CMD_PREFIX = $(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS)

.c:
	$(CC_CMD_PREFIX) -o $@ $<
