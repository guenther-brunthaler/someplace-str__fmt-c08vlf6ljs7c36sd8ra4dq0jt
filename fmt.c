#include <sfmt-8fhsyuxltzwiucx68ikkgkxzm.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
   char const *error= 0;
   char *str= 0;
   {
      size_t len= 0;
      {
         unsigned i;
         for (i= 1; i <= 10; ++i) {
            char num[UINT_BASE10_BUFSIZE(i)];
            if (sprintf(num, "%u", i) < 0) {
               error= "Internal error!";
               goto fail;
            }
            if (sfmt(&str, &len, 'n', num, 0, "The number is %n.")) {
               goto fmt_error;
            }
            if (puts(str) < 0) goto output_error;
         }
      }
      if (
         sfmt(
               &str, &len
            ,  'Y', "2001", 'M', "12", 'D', "24", 'w', "Santa Claus"
            ,  'm', "Ho Ho Ho"
            ,  0, "On %Y-%M-%D, %w said %m."
         )
      ) {
         fmt_error:
         error= str; str= 0;
         goto fail;
      }
   }
   if (puts(str) < 0) goto output_error;
   if (fflush(0)) {
      output_error:
      error= "output error!";
      fail:
      (void)fputs(error, stderr);
      (void)fputc('\n', stderr);
   }
   free(str);
   return error ? EXIT_FAILURE : EXIT_SUCCESS;
}
