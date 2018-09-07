/* #include <getopt_nh7lll77vb62ycgwzwf30zlln.h>
 *
 * Option parsing support. Does not support exotic features of getopt(), but
 * has a small code footprint and should be sufficient in most cases.
 *
 * Version 2018.250
 * Copyright (c) 2016-2018 Guenther Brunthaler. All rights reserved.
 * 
 * This source file is free software.
 * Distribution is permitted under the terms of the LGPLv3. */


#ifndef HEADER_NH7LLL77VB62YCGWZWF30ZLLN_INCLUDED
#define HEADER_NH7LLL77VB62YCGWZWF30ZLLN_INCLUDED
#ifdef __cplusplus
   extern "C" {
#endif


/* Portable POSIX-compliant command line option parser which only depends on
 * the standard C libraries and will thus also work on non-POSIX systems.
 * Returns the next one-character option encountered by parsing the command
 * line vector <argv> containing <argc> elements (the first of which, if
 * present, is the program name). Returns 0 when no more options have been
 * found. <optind_ref> and <optpos_ref> are pointers to working variables
 * which must have been initialized to 0 by the caller before the first call.
 * The working variable where <optind_ref> points to will contain the argv[]
 * index of the first non-option argument when no more options have been
 * found. Option switch clustering and "--" are supported. Note that POSIX
 * requires that all options must come before all normal arguments. */
int getopt_simplest(
   int *optind_ref, int *optpos_ref, int argc, char const *const *argv
);

/* Write an error message complaining about an unsupported option to the
 * standard error stream and ignore any output error. Use this if
 * getopt_simplest() returned an option character which is not supported by
 * the application. */
void getopt_simplest_perror(int bad_option_char);


#ifdef __cplusplus
   }
#endif
#endif /* !HEADER_NH7LLL77VB62YCGWZWF30ZLLN_INCLUDED */
