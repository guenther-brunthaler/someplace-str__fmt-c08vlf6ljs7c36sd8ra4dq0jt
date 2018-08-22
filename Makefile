# Default to maximum POSIX-supported C compiler flags for optimized builds.
# Override those from the "make" command line with MACRO=value as desired.
CPPFLAGS = -D NDEBUG
CFLAGS = -O
LDFLAGS = -s

# Enable POSIX-compliant Makefile processing. Must be the very first rule.
.POSIX:

.PHONY: all clean

include autodetected-targets.mk

all: $(TARGETS)

clean:
	-rm $(TARGETS) $(OBJECTS)

.c.o:
	$(CC) $(CPPFLAGS) -I . $(CFLAGS) -c $<

.o:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $?

include autodetected-rules.mk
