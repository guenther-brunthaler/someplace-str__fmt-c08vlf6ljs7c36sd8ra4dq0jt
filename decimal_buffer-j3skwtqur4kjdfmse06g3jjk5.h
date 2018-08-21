/* #include <decimal_buffer-j3skwtqur4kjdfmse06g3jjk5.h>
 *
 * Copyright (c) 2018 Guenther Brunthaler. All rights reserved.
 *
 * This header file and its associated implementations are free software.
 * Distribution is permitted under the terms of the LGPLv3.
 */

#ifndef HEADER_J3SKWTQUR4KJDFMSE06G3JJK5_INCLUDED
#define HEADER_J3SKWTQUR4KJDFMSE06G3JJK5_INCLUDED
#include <limits.h>

/* # of decimal digits in a format buffer, NOT including a null terminator. */
#define UINT_BASE10_MAXCHARS(type_or_value) ( \
   sizeof(type_or_value) * CHAR_BIT * 617 + 2047 >> 11 \
)
#define INT_BASE10_MAXCHARS(type_or_value) ( \
   1 + UINT_BASE10_MAXCHARS(type_or_value) \
)

/* # of maximum bytes required for a format buffer, including null the
 * terminator. */
#define UINT_BASE10_BUFSIZE(type_or_value) ( \
   UINT_BASE10_MAXCHARS(type_or_value) + 1 \
)
#define INT_BASE10_BUFSIZE(type_or_value) ( \
   INT_BASE10_MAXCHARS(type_or_value) + 1 \
)

#endif /* !HEADER_J3SKWTQUR4KJDFMSE06G3JJK5_INCLUDED */
