#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

struct isq {
   struct isq *parent;
   int key;
   char const *expansion;
};

static char *sfmt_helper2(struct isq *fmt) {
   char *buffer= 0;
   const char *fstr= fmt->expansion, *insert;
   size_t bsz= 0, used= 0, isz;
   assert(!fmt->key);
   for (;;) {
      if (*fstr == '%') {
         struct isq *search;
         int key= *++fstr;
         for (search= fmt->parent; ; search= search->parent) {
            if (!search) {
               fail:
               free(buffer);
               return 0;
            }
            if (search->key == key) break;
         }
         assert(search);
         assert(*fstr);
         isz= strlen(insert= search->expansion);
      } else {
         insert= fstr; isz= 1;
      }
      if (used + isz >= bsz) {
         char *nbuf;
         if (!bsz) bsz= 80;
         while (used + isz >= bsz) bsz+= bsz;
         if (!(nbuf= realloc(buffer, bsz))) goto fail;
         buffer= nbuf;
      }
      (void)memcpy(buffer + used, insert, isz); used+= isz;
      if (!*fstr) {
         char *final;
         if (!(final= realloc(buffer, used))) goto fail;
         return final;
      }
      ++fstr;
   }
}

static char *sfmt_helper(struct isq *sq, va_list *args) {
   if (!sq->key) return sfmt_helper2(sq);
   {
      struct isq child= {sq, va_arg(*args, int)};
      child.expansion= va_arg(*args, char const *);
      return sfmt_helper(&child, args);
   }
}

static char *sfmt(int key_1, ...) {
   struct isq root= {0, key_1};
   char *result;
   va_list args;
   va_start(args, key_1);
   root.expansion= va_arg(args, char const *);
   result= sfmt_helper(&root, &args);
   va_end(args);
   return result;
}

int main(void) {
   char *str;
   char const *error= 0;
   if (
      !(
         str= sfmt(
               'Y', "2001", 'M', "12", 'D', "24", 'w', "Santa Claus", 'm'
            ,  "Ho Ho Ho", 0, "On %Y-%M-%D, %w said %m."
         )
      )
   ) {
      error= "string formatting error!";
      fail:
      (void)fputs(error, stderr);
      (void)fputc('\n', stderr);
      goto cleanup;
   } else if (puts(str) < 0 || fflush(0)) {
      error= "output error!";
      goto fail;
   }
   cleanup:
   if (str) { free(str); str= 0; }
   return error ? EXIT_FAILURE : EXIT_SUCCESS;
}
