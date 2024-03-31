//
//  12626.c
//  hxy
//
//  Created by Fang Ling on 2024/3/31.
//

#include <stdio.h>
#include <string.h>

#define var __auto_type

#define MIN(a, b) (a) < (b) ? (a) : (b)

void main_12626(void) {
  int F[32];
  char A[1024];
  
  var n = 0;
  scanf("%d", &n);
  while (n--) {
    var i = 0;
    for (i = 0; i < 26; i += 1) {
      F[i] = 0;
    }
    
    scanf("%s", A);
    var count = (int)strlen(A);
    for (i = 0; i < count; i += 1) {
      F[A[i] - 'A'] += 1;
    }
    F['A' - 'A'] /= 3;
    F['R' - 'A'] /= 2;
    printf(
      "%d\n",
      MIN(
        F['M' - 'A'],
        MIN(
          F['A' - 'A'],
          MIN(
            F['R' - 'A'],
            MIN(
              F['G' - 'A'],
              MIN(
                F['I' - 'A'],
                F['T' - 'A']
              )
            )
          )
        )
      )
    );
  }
}
