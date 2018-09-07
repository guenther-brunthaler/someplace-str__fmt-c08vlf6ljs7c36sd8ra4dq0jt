#include <sfmt-8fhsyuxltzwiucx68ikkgkxzm.h>
#include <stdio.h>
#include <stdlib.h>
#include <gettext-9qcw53n397sxlyu259tcq4twy.h>

void vpfmtm(
   char **buffer_ref, size_t *buffer_size_ref, FILE *out, va_list args
) {
   vsfmt(buffer_ref, buffer_size_ref, args);
   if (*buffer_size_ref) {
      if (fputs(*buffer_ref, out) >= 0) return;
      free(*buffer_ref); *buffer_size_ref= 0;
      *buffer_ref= T("Output error!");
   }
   (void)fprintf(stderr, "%s\n", *buffer_ref);
}
