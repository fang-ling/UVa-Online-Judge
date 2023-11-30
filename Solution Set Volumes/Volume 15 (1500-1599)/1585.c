//
//  1585.c
//  hxy
//
//  Created by Fang Ling on 2023/11/30.
//

/*
 * 1. Initialize two variables, score and current_length, to keep track of the
 * total score and the number of consecutive 'O's respectively.
 * 2. Iterate over each character in the given string.
 * 3. If the current character is 'O', increment the current_length by 1 and add
 * it to the total score.
 * 4. If the current character is 'X', reset the current_length to 0.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define var __auto_type

void main_1585(void) {
  var T = 0;
  scanf("%d", &T);
  char str[80 + 1];
  while (T--) {
    scanf("%s", str);
    var count = strlen(str);
    var score = 0;
    var current_length = 0;
    var i = 0;
    for (i = 0; i < count; i += 1) {
      if (str[i] == 'O') {
        current_length += 1;
        score += current_length;
      } else {
        current_length = 0;
      }
    }
    printf("%d\n", score);
  }
}
