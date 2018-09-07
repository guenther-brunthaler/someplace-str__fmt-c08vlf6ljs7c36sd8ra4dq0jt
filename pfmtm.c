#include <gettext-9qcw53n397sxlyu259tcq4twy.h>
#include <sfmt-8fhsyuxltzwiucx68ikkgkxzm.h>
#include <stdarg.h>

int pfmtm(char **buffer_ref, size_t *buffer_size_ref, FILE *out, ...) {
   {
      va_list args;
      va_start(args, out);
      vpfmtm(buffer_ref, buffer_size_ref, out, args);
      va_end(args);
   }
   return !*buffer_size_ref;
}
