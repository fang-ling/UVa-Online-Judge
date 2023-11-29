//
//  1584.c
//  hxy
//
//  Created by Fang Ling on 2023/11/29.
//

/*
 * Like how we find the minimum element in an integer array, we assume that the
 * current DNA sequence is the minimum. We then generate all possible DNA
 * sequence on-the-fly and compare them with the current minimum, updating it
 * when necessary.
 */

#include <stdio.h>
#include <string.h>

#define var __auto_type

void main_1584(void) {
  var T = 0;
  scanf("%d", &T);
  char dna[100 + 1];
  char new_seq[100 + 1];
  char min[100 + 1];
  while (T--) {
    scanf("%s", dna);
    var count = strlen(dna);
    memset(new_seq, 0, 100 + 1); /* !!! */
    strcpy(min, dna);
    var bp = 0; /* Break point */
    for (bp = 0; bp < count; bp += 1) {
      var i = 0;
      var k = 0; /* points to end inex of new_seq */
      for (i = bp; i < count; i += 1) { /* After break point */
        new_seq[k] = dna[i];
        k += 1;
      }
      for (i = 0; i < bp; i += 1) { /* Before break point */
        new_seq[k] = dna[i];
        k += 1;
      }

      if (strcmp(new_seq, min) < 0) {
        strcpy(min, new_seq);
      }
    }
    printf("%s\n", min);
  }
}
