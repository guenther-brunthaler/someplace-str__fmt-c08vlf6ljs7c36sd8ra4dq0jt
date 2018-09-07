/* Version 2018.250.1
 * Copyright (c) 2018 Guenther Brunthaler. All rights reserved.
 *
 * This source file is free software.
 * Distribution is permitted under the terms of the LGPLv3. */

#include <sfmt-8fhsyuxltzwiucx68ikkgkxzm.h>
#include <stdarg.h>

int sfmt(char **buffer_ref, size_t *buffer_size_ref, ...) {
   {
      va_list args;
      va_start(args, buffer_size_ref);
      vsfmt(buffer_ref, buffer_size_ref, args);
      va_end(args);
   }
   return !*buffer_size_ref;
}
