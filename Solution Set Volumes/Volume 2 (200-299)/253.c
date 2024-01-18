//
//  253.c
//  hxy
//
//  Created by Fang Ling on 2024/1/18.
//

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define var __auto_type

static void rotate_clockwise_z_253(char* dice, char* result) {
  result[0] = dice[1 - 1];
  result[1] = dice[4 - 1];
  result[2] = dice[2 - 1];
  result[3] = dice[5 - 1];
  result[4] = dice[3 - 1];
  result[5] = dice[6 - 1];
}

static void rotate_clockwise_x_253(char* dice, char* result) {
  result[0] = dice[3 - 1];
  result[1] = dice[2 - 1];
  result[2] = dice[6 - 1];
  result[3] = dice[1 - 1];
  result[4] = dice[5 - 1];
  result[5] = dice[4 - 1];
}

static void rotate_clockwise_y_253(char* dice, char* result) {
  result[0] = dice[5 - 1];
  result[1] = dice[1 - 1];
  result[2] = dice[3 - 1];
  result[3] = dice[4 - 1];
  result[4] = dice[6 - 1];
  result[5] = dice[2 - 1];
}

void main_253(void) {
  char delta[12 + 1];
  char a[6];
  char b[6];
  char buf[6];
  
  while (scanf("%s", delta) == 1) {
    var i = 0;
    for (i = 0; i < 6; i += 1) {
      a[i] = delta[i];
    }
    for (; i < 12; i += 1) {
      b[i - 6] = delta[i];
    }
    
    var is_equal = false;
    for (i = 0; i < 4; i += 1) {
      rotate_clockwise_z_253(a, buf);
      memcpy(a, buf, 6 * sizeof(char));
      
      var j = 0;
      for (j = 0; j < 4; j += 1) {
        rotate_clockwise_x_253(a, buf);
        memcpy(a, buf, 6 * sizeof(char));
        
        var k = 0;
        for (k = 0; k < 4; k += 1) {
          rotate_clockwise_y_253(a, buf);
          memcpy(a, buf, 6 * sizeof(char));
          
          if (memcmp(a, b, 6 * sizeof(char)) == 0) {
            is_equal = true;
            break;
          }
        }
      }
    }
    
    if (is_equal) {
      printf("TRUE\n");
    } else {
      printf("FALSE\n");
    }
  }
}
