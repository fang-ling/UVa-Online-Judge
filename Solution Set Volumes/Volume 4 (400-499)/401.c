//
//  401.c
//  hxy
//
//  Created by Fang Ling on 2023/11/26.
//

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define var __auto_type

char mirror_401(char c) {
  /*    index: ABCDEFGHIJKLMNOPQRSTUVWXYZ */
  var TBL_A = "A   3  HIL JM O   2TUVWXY5";
  /*    index: 123456789 */
  var TBL_N = "1SE Z  8 ";
  
  if (isalpha(c)) { /* A-Za-z */
    return TBL_A[c - 'A'];
  } else {
    return TBL_N[c - '1'];
  }
}

void main_401(void) {
  char buf[512];
  
  while (scanf("%s", buf) == 1) {
    var count = strlen(buf);
    var is_palindrome = true;
    var is_mirrored = true;
    
    var i = 0;
    for (; i < (count + 1) / 2; i += 1) {
      if (buf[i] != buf[count - 1 - i]) {
        is_palindrome = false;
      }
      if (mirror_401(buf[i]) != buf[count - 1 - i]) {
        is_mirrored = false;
      }
    }
    
    printf("%s ", buf);
    if (is_palindrome && is_mirrored) {
      printf("-- is a mirrored palindrome.");
    } else if (is_palindrome && !is_mirrored) {
      printf("-- is a regular palindrome.");
    } else if (!is_palindrome && is_mirrored) {
      printf("-- is a mirrored string.");
    } else {
      printf("-- is not a palindrome.");
    }
    printf("\n\n");
  }
}
