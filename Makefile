TARGETS = fmt

.PHONY: all clean

all: $(TARGETS)

clean:
	-rm $(TARGETS)

CC_CMD_PREFIX = $(CC) $(CPPFLAGS) -I . $(CFLAGS) $(LDFLAGS)

.c:
	$(CC_CMD_PREFIX) -o $@ $<

fmt_SOURCES = sfmt.c fmt.c
fmt_HEADERS = sfmt-8fhsyuxltzwiucx68ikkgkxzm.h

fmt: $(sfmt_SOURCES) $(fmt_HEADERS)
	$(CC_CMD_PREFIX) -o $@ $(fmt_SOURCES)
