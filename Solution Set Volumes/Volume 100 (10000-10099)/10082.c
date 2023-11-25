//
//  10082.c
//  hxy
//
//  Created by Fang Ling on 2023/11/25.
//

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define var __auto_type

void main_10082(void) {
  var TBL = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";
  var count = strlen(TBL);
  
  var delta = ' ';
  while ((delta = getchar()) != EOF) {
    var i = 0;
    var is_in_tbl = false;
    for (; i < count; i += 1) {
      if (TBL[i] == delta) {
        is_in_tbl = true;
        break;
      }
    }
    printf("%c", is_in_tbl ? TBL[i - 1] : delta);
  }
}
