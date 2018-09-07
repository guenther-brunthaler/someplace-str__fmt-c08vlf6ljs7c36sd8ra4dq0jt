/* Version 2018.250
 * Copyright (c) 2018 Guenther Brunthaler. All rights reserved.
 *
 * This source file is free software.
 * Distribution is permitted under the terms of the LGPLv3. */

#include <sfmt-8fhsyuxltzwiucx68ikkgkxzm.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

struct isq {
   int key;
   char const *expansion;
   struct isq *parent;
};

struct sfmt_vars {
   struct isq *head;
   char **result;
   size_t *size;
   va_list args;
};

static void sfmt_helper2(struct sfmt_vars *v) {
   char *buffer= *v->result;
   const char *fstr= v->head->expansion, *insert;
   size_t bsz= *v->size, used= 0, isz;
   assert(!v->head->key); assert(buffer ? bsz != 0 : bsz == 0);
   for (;;) {
      if (*fstr == '%') {
         struct isq *search;
         int key= *++fstr;
         for (search= v->head->parent; ; search= search->parent) {
            if (!search) {
               *v->result=
                  (char *)
                  "Undefined insertion sequence referenced in format string!"
               ;
               goto fail;
            }
            if (search->key == key) break;
         }
         assert(search);
         assert(*fstr);
         isz= strlen(insert= search->expansion);
      } else if (used < bsz) {
         buffer[used++]= *fstr;
         goto copied;
      } else {
         insert= fstr; isz= 1;
      }
      if (used + isz >= bsz) {
         void *nbuf;
         if (!bsz) bsz= 80;
         while (used + isz > bsz) bsz+= bsz;
         if (!(nbuf= realloc(buffer, bsz))) {
            *v->result= (char *)"Memory allocation failure!";
            fail:
            free(buffer); *v->size= 0;
            break;
         }
         buffer= nbuf; *v->size= bsz;
      }
      (void)memcpy(buffer + used, insert, isz); used+= isz;
      copied:
      if (!*fstr) {
         *v->result= buffer;
         break;
      }
      ++fstr;
   }
}

static void sfmt_helper(struct sfmt_vars *v) {
   if (v->head->key) {
      struct isq child;
      child.key= va_arg(v->args, int);
      child.expansion= va_arg(v->args, char const *);
      child.parent= v->head;
      v->head= &child;
      sfmt_helper(v);
   } else {
      sfmt_helper2(v);
   }
}

void vsfmt(char **buffer_ref, size_t *buffer_size_ref, va_list args) {
   struct sfmt_vars v;
   assert(buffer_ref); assert(buffer_size_ref);
   assert(*buffer_ref ? *buffer_size_ref != 0 : *buffer_size_ref == 0);
   v.head= 0;
   v.result= buffer_ref;
   v.size= buffer_size_ref;
   v.args= args;
   sfmt_helper(&v);
   assert(*buffer_ref); /* Either allocated buffer or static error message. */
}
