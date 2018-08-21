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
	-rm $(TARGETS) *.o

CC_CMD_PREFIX = $(CC) $(CPPFLAGS) -I . $(CFLAGS) $(LDFLAGS)

sfmt_HEADERS = \
	decimal_buffer-j3skwtqur4kjdfmse06g3jjk5.h \
	sfmt-8fhsyuxltzwiucx68ikkgkxzm.h

sfmt.o: sfmt.c $(sfmt_HEADERS)
	$(CC_CMD_PREFIX) -c sfmt.c

fmt.o: fmt.c $(sfmt_HEADERS)
	$(CC_CMD_PREFIX) -c fmt.c

fmt: sfmt.o fmt.o
	$(CC_CMD_PREFIX) -o $@ sfmt.o fmt.o
