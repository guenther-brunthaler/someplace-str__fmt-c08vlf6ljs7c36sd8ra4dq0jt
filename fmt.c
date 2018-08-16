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
               free(buffer);
               return
                  (char *)"\0"
                  "Undefined insertion sequence referenced in format string!"
               ;
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
         if (!(nbuf= realloc(buffer, bsz))) {
            realloc_failure:
            free(buffer);
            return (char *)"\0" "Memory allocation failure!";
         }
         buffer= nbuf;
      }
      (void)memcpy(buffer + used, insert, isz); used+= isz;
      if (!*fstr) {
         char *final;
         if (!(final= realloc(buffer, used))) goto realloc_failure;
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

/* Expand a simple format string containing string insertion sequences into a
 * dynamically alloated buffer.
 *
 * <result> is the address of a text pointer where the result will be stored.
 *
 * <key_1> and <expansion_1> are the first pair of char/string pairs which
 * define all available insertion sequences as well as the format string.
 *
 * Insertion sequences come first in arbitrary order and define a "char" key
 * and an expansion string associated with the key.
 *
 * A key of 0 is special and its associated insertion string then actually
 * represents the format string, which always has to be the last argument.
 *
 * Within the format string, all characters are copied literally to the output
 * buffer except sequences of the form "%" followed by some character. This
 * represents an insertion sequence, and the character following the "%" will
 * be used as a lookup key for finding the expansion string to insert.
 *
 * There is no built-in way to output a literal "%", but if required an
 * expansion can be defined to insert it (e. g. one with a key of '%' which
 * will insert "%").
 *
 * Return value: If the function returns non-zero then *<result> contains a
 * pointer to the successfully dynamically allocated string. It is the
 * responsibility of the caller to free() this string eventually.
 *
 * If the function returns 0, then the format operation has failed and
 * *<result> contains a read-only statically allocated error message which
 * must not be freed. */
static int sfmt(char **result, int key_1, const char *expansion_1, ...) {
   struct isq root= {0, key_1, expansion_1};
   va_list args;
   va_start(args, expansion_1);
   *result= sfmt_helper(&root, &args);
   va_end(args);
   if (*result) return 1;
   ++*result;
   return 0;
}

int main(void) {
   char *str;
   char const *error= 0;
   if (
      !sfmt(
            &str
         ,  'Y', "2001", 'M', "12", 'D', "24", 'w', "Santa Claus", 'm'
         ,  "Ho Ho Ho", 0, "On %Y-%M-%D, %w said %m."
      )
   ) {
      error= str;
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
