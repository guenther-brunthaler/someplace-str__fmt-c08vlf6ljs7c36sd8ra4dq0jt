# Enable POSIX-compliant Makefile processing.
.POSIX:

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

C = $(CC) $(CPPFLAGS) -I . $(CFLAGS) -c
L = $(CC) $(CFLAGS) $(LDFLAGS) -o $@

sfmt_H = \
	decimal_buffer-j3skwtqur4kjdfmse06g3jjk5.h \
	sfmt-8fhsyuxltzwiucx68ikkgkxzm.h

sfmt.o: sfmt.c $(sfmt_H)
	$C sfmt.c

fmt.o: fmt.c $(sfmt_H)
	$C fmt.c

fmt: sfmt.o fmt.o
	$L sfmt.o fmt.o
