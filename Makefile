# This Makefile was originally a copy of Makefile.tpl as provided by
# Makefile-autogenerator version 2018.234.2.

INCDIRS = $(AUTODETECTED_INCDIRS)
LIBS = $(AUTODETECTED_LIBS)

# Enable POSIX-compliant Makefile processing. Must be the very first rule.
.POSIX:

.PHONY: all clean

include autodetected-macros.mk

all: $(TARGETS)

clean:
	-rm $(TARGETS) $(OBJECTS)

.c.o:
	$(CC) $(CPPFLAGS) $(INCDIRS) $(CFLAGS) -c $<

.o:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(LIBS) $?

include autodetected-rules.mk
