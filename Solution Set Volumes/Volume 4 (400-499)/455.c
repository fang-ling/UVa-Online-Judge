//
//  455.c
//  hxy
//
//  Created by Fang Ling on 2023/12/2.
//

/*
 * For every input string s, we can try to reconstruct the whole string by 
 * duplicating substrings from length 1 to the length of s.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define var __auto_type

void main_455(void) {
  char str[80 + 1];
  char recon[80 + 1];
  char substring[80 + 1];

  var is_first = true;

  var T = 0;
  scanf("%d", &T);
  while (T--) {
    scanf("%s", str);
    var count = strlen(str);
    var sublen = 0;
    for (sublen = 1; sublen < count; sublen += 1) {
      memset(recon, 0, 80 + 1);
      if (count % sublen != 0) { /* Impossible to reconstruct */
        continue;
      }
      var dup_count = count / sublen;
      var i = 0;
      for (i = 0; i < sublen; i += 1) {
        substring[i] = str[i];
      }
      substring[i] = '\0';
      for (i = 0; i < dup_count; i += 1) {
        strcat(recon, substring);
      }
      if (strcmp(recon, str) == 0) {
        break;
      }
    }
    if (!is_first) {
      printf("\n");
    }
    if (is_first) {
      is_first = !is_first;
    }
    printf("%d\n", sublen);
  }
}
