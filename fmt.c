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

struct sfmt_vars {
   struct isq *sq;
   char **result;
   int failure;
   va_list *args;
};

static void sfmt_helper2(struct sfmt_vars *v) {
   char *buffer= 0;
   const char *fstr= v->sq->expansion, *insert;
   size_t bsz= 0, used= 0, isz;
   assert(!v->sq->key);
   for (;;) {
      if (*fstr == '%') {
         struct isq *search;
         int key= *++fstr;
         for (search= v->sq->parent; ; search= search->parent) {
            if (!search) {
               *v->result=
                  (char *)
                  "Undefined insertion sequence referenced in format string!"
               ;
               fail:
               v->failure= 1;
               free(buffer);
               return;
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
            *v->result= (char *)"Memory allocation failure!";
            goto fail;
         }
         buffer= nbuf;
      }
      (void)memcpy(buffer + used, insert, isz); used+= isz;
      if (!*fstr) {
         if (!(*v->result= realloc(buffer, used))) goto realloc_failure;
         return;
      }
      ++fstr;
   }
}

static void sfmt_helper(struct sfmt_vars *v) {
   if (v->sq->key) {
      struct isq child= {v->sq, va_arg(*v->args, int)};
      child.expansion= va_arg(*v->args, char const *);
      v->sq= &child;
      sfmt_helper(v);
   } else {
      sfmt_helper2(v);
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
 * Return value: Returns 0 if successful.
 *
 * If successful, *<result> contains a pointer to the dynamically allocated
 * formatted string. It is then the responsibility of the caller to free()
 * this string eventually.
 *
 * On unsuccessful return, *<result> contains a read-only statically allocated
 * error message which must not be freed. */
static int sfmt(char **result, int key_1, const char *expansion_1, ...) {
   struct isq root= {0, key_1, expansion_1};
   struct sfmt_vars v= {&root, result, 0};
   va_list args;
   va_start(args, expansion_1);
   v.args= &args;
   sfmt_helper(&v);
   va_end(args);
   return v.failure;
}

int main(void) {
   char *str;
   char const *error= 0;
   if (
      sfmt(
            &str
         ,  'Y', "2001", 'M', "12", 'D', "24", 'w', "Santa Claus", 'm'
         ,  "Ho Ho Ho", 0, "On %Y-%M-%D, %w said %m."
      )
   ) {
      error= str; str= 0;
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
