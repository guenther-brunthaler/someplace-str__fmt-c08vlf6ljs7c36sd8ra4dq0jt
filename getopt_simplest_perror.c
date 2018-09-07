#include <gettext-9qcw53n397sxlyu259tcq4twy.h>
#include <getopt_nh7lll77vb62ycgwzwf30zlln.h>
#include <sfmt-8fhsyuxltzwiucx68ikkgkxzm.h>
#include <stdio.h>

void getopt_simplest_perror(int bad_option_char) {
   char s[2];
   s[0]= bad_option_char;
   s[1]= 0;
   (void)pfmt(stdout, '1', s, 0, T("Unsupported option -%1!\n"));
}
