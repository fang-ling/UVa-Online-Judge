//
//  1586.c
//  hxy
//
//  Created by Fang Ling on 2023/12/1.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define var __auto_type

void main_1586(void) {
  /*               A  B  C      D  E  F  G  H      I  J  K  L  M  N      O */
  double mass[] = {0, 0, 12.01, 0, 0, 0, 0, 1.008, 0, 0, 0, 0, 0, 14.01, 16};

  char formula[80 + 1];
  var T = 0;
  scanf("%d", &T);
  while (T--) {
    scanf("%s", formula);
    var count = strlen(formula);

    var m = 0.0;
    var i = 0;
    for (i = 0; i < count; i += 1) {
      if (isalpha(formula[i])) { /* Current char is an alphabetic character */
        /* avoid buffer overflow */
        if (i + 1 < count && isdigit(formula[i + 1])) {
          /* since 2 <= n <= 99 */
          if (i + 2 < count && isdigit(formula[i + 2])) {
            var n = (formula[i + 1] - '0') * 10 + formula[i + 2] - '0';
            m += mass[formula[i] - 'A'] * n;
          } else {
            m += mass[formula[i] - 'A'] * (formula[i + 1] - '0');
          }
        } else {
          m += mass[formula[i] - 'A'] * 1;
        }
      }
    }
    printf("%.3lf\n", m);
  }
}
