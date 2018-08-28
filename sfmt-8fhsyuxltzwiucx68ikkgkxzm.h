/* #include <sfmt-8fhsyuxltzwiucx68ikkgkxzm.h>
 *
 * Version 2018.240
 * Copyright (c) 2018 Guenther Brunthaler. All rights reserved.
 *
 * This header file and its associated implementations are free software.
 * Distribution is permitted under the terms of the LGPLv3. */

#ifndef HEADER_8FHSYUXLTZWIUCX68IKKGKXZM_INCLUDED
#define HEADER_8FHSYUXLTZWIUCX68IKKGKXZM_INCLUDED
#ifdef __cplusplus
   extern "C" {
#endif
#include <decimal_buffer-j3skwtqur4kjdfmse06g3jjk5.h>
#include <stddef.h>

/* Expand a simple format string containing string insertion sequences into a
 * dynamically alloated buffer.
 *
 * <key_1> and <expansion_1> are the first of char+string argument-pairs which
 * define all available insertion sequences as well as the format string.
 *
 * Insertion sequences come first in arbitrary order and define a "char" key
 * and an expansion string associated with that key. It the same key occurs
 * multiple times, only the last such argument-pair will be found when
 * referenced from within the format string. Argument-pairs which are never
 * referenced from within the format string are allowed and will have no
 * effect.
 *
 * A key of 0 is special and its associated insertion string then actually
 * represents the format string. The format string is usually also the last
 * argument, because any additional arguments will be ignored.
 *
 * Within the format string, all characters are copied literally to the output
 * buffer except sequences of the form "%" followed by some character. This
 * represents an insertion sequence, and the character following the "%" will
 * be used as a lookup key for finding the expansion string to insert.
 *
 * All possible "char" values (including '%') are valid as keys, not just
 * printable characters. However, a NUL value will not work as key, because
 * then the argument-pair defining its expansion value would be
 * mis-interpreted as the format string.
 *
 * There is no built-in way to output a literal "%". If required it is
 * recommended to include an argument-pair '%', "%" which will copy "%" into
 * the result buffer whenever "%%" occurs within the format string.
 *
 * Argument-pairs referenced by "%"-sequences will be located using a linear
 * search backwards through the pairs starting immediately before the format
 * string. Even though the referenced pairs will be found in any case, for
 * maximum performance more frequently referenced pairs should be placed after
 * less frequently referenced pairs. If all pairs are only referenced exactly
 * once, the order does not affect performance.
 *
 * <buffer_ref> and <buffer_size_ref> are the addresses of variables which
 * store the current buffer pointer and buffer allocation size. Note that the
 * allocation size is normally not the same as the size of the formatted
 * result string and will rather be larger than that. The referenced variables
 * must contain valid values. A null pointer and a size size of zero are also
 * considered valid, meaning no buffer has been allocated yet. This is also
 * the recommended way to initialize those variables.
 *
 * Return value: Returns 0 if successful.
 *
 * If successful, *<buffer_ref> contains a pointer to the dynamically
 * allocated (or re-allocated) null-terminated formatted string.
 * *<buffer_size_ref> gets updated as well. It is then the responsibility of
 * the caller to free() this string eventually.
 *
 * On unsuccessful return, *<buffer_ref> will be deallocated and
 * *<buffer_size_ref> will be set to zero. Then *<buffer_ref> will be replaced
 * by a pointer to a read-only statically allocated error message which must
 * not be freed. */
int sfmt(
      char **buffer_ref, size_t *buffer_size_ref
   ,  int key_1, const char *expansion_1, ...
);

#ifdef __cplusplus
   }
#endif
#endif /* !HEADER_8FHSYUXLTZWIUCX68IKKGKXZM_INCLUDED */
