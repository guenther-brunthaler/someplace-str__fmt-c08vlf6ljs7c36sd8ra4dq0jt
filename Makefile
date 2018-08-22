# Default to maximum POSIX-supported C compiler flags for optimized builds.
# Override those from the "make" command line with MACRO=value as desired.
CPPFLAGS = -D NDEBUG
CFLAGS = -O
LDFLAGS = -s

TARGETS = fmt

# Enable POSIX-compliant Makefile processing. Must be the very first rule.
.POSIX:

.PHONY: all clean

all: $(TARGETS)

clean:
	-rm $(TARGETS) *.o

.c.o:
	$(CC) $(CPPFLAGS) -I . $(CFLAGS) -c $<

.o:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $?

sfmt.o fmt.o: \
	decimal_buffer-j3skwtqur4kjdfmse06g3jjk5.h \
	sfmt-8fhsyuxltzwiucx68ikkgkxzm.h

fmt: sfmt.o fmt.o
