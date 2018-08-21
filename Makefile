# POSIX-compliant Makefile.

# Maximum POSIX-defined C compiler flags for optimized builds. Override those
# from the "make" command line with MACRO=value as required.
CPPFLAGS = -D NDEBUG
CFLAGS = -O
LDFLAGS = -s

TARGETS = fmt

.PHONY: all clean

all: $(TARGETS)

clean:
	-rm $(TARGETS)

CC_CMD_PREFIX = $(CC) $(CPPFLAGS) -I . $(CFLAGS) $(LDFLAGS)

fmt_SOURCES = sfmt.c fmt.c
fmt_HEADERS = \
	decimal_buffer-j3skwtqur4kjdfmse06g3jjk5.h \
	sfmt-8fhsyuxltzwiucx68ikkgkxzm.h

fmt: $(sfmt_SOURCES) $(fmt_HEADERS)
	$(CC_CMD_PREFIX) -o $@ $(fmt_SOURCES)
