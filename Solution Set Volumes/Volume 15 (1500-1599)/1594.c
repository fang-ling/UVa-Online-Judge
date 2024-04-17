//
//  1594.c
//  hxy
//
//  Created by Fang Ling on 2024/4/17.
//

#include <stdio.h>

#define var __auto_type
#define LEN 32

#define ABS(n) (n) > 0 ? (n) : (-n)

static void ducci(int* seq, int count) {
  var old_first = seq[0];
  var i = 0;
  for (i = 0; i < count - 1; i += 1) {
    seq[i] = ABS(seq[i] - seq[i + 1]);
  }
  seq[count - 1] = ABS(seq[count - 1] - old_first);
}

void main_1594(void) {
  int seq[LEN];
  
  var t = 0;
  scanf("%d", &t);
  while (t--) {
    var n = 0;
    scanf("%d", &n);
    
    var i = 0;
    for (i = 0; i < n; i += 1) {
      scanf("%d", &seq[i]);
    }
    
    var loop_count = 1001;
    while (loop_count--) {
      ducci(seq, n);
    }
    
    for (i = 0; i < n; i += 1) {
      if (seq[i] != 0) {
        printf("LOOP\n");
        goto loop;
      }
    }
    printf("ZERO\n");
    
  loop:;
  }
}
