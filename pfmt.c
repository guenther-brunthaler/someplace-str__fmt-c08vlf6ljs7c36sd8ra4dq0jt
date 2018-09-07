#include <sfmt-8fhsyuxltzwiucx68ikkgkxzm.h>
#include <stdarg.h>
#include <stdlib.h>

int pfmt(FILE *out, ...) {
   char *str= 0;
   {
      size_t len= 0;
      {
         va_list args;
         va_start(args, out);
         vpfmtm(&str, &len, out, args);
         va_end(args);
      }
      if (!len) return 1;
   }
   free(str);
   return 0;
}
