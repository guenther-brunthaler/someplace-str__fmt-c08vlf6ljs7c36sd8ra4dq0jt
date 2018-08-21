/*
 * Copyright (c) 2018 Guenther Brunthaler. All rights reserved.
 *
 * This file is free software.
 * Distribution is permitted under the terms of the LGPLv3.
 */

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
   struct isq *sq;
   char **result;
   size_t *size;
   va_list args;
};

static void sfmt_helper2(struct sfmt_vars *v) {
   char *buffer= *v->result;
   const char *fstr= v->sq->expansion, *insert;
   size_t bsz= *v->size, used= 0, isz;
   assert(!v->sq->key); assert(buffer ? bsz != 0 : bsz == 0);
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
               free(buffer); *v->size= 0;
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
            *v->result= (char *)"Memory allocation failure!";
            goto fail;
         }
         buffer= nbuf; *v->size= bsz;
      }
      (void)memcpy(buffer + used, insert, isz); used+= isz;
      if (!*fstr) {
         *v->result= buffer;
         return;
      }
      ++fstr;
   }
}

static void sfmt_helper(struct sfmt_vars *v) {
   if (v->sq->key) {
      struct isq child= {va_arg(v->args, int), 0, v->sq};
      child.expansion= va_arg(v->args, char const *);
      v->sq= &child;
      sfmt_helper(v);
   } else {
      sfmt_helper2(v);
   }
}

int sfmt(
      char **buffer_ref, size_t *buffer_size_ref
   ,  int key_1, const char *expansion_1, ...
) {
   struct isq root= {key_1, expansion_1};
   struct sfmt_vars v= {&root, buffer_ref, buffer_size_ref};
   assert(buffer_ref); assert(buffer_size_ref);
   assert(*buffer_ref ? *buffer_size_ref != 0 : *buffer_size_ref == 0);
   va_start(v.args, expansion_1);
   sfmt_helper(&v);
   va_end(v.args);
   return !*buffer_size_ref && *buffer_ref;
}
