//
//  272.c
//  hxy
//
//  Created by Fang Ling on 2023/11/25.
//

/*
 * This program uses a flag `is_left` to keep track of whether we are inside an
 * open quote or not. When we encounter a double-quote character, we check the
 * flag to determine whether it should be replaced by "``" or "''". We toggle
 * the flag after each replacement to alternate between opening and closing
 * quotes.
 */

#include <stdio.h>
#include <stdbool.h>

#define var __auto_type

void main_272(void) {
  var delta = ' ';
  var is_left = true;
  
  while ((delta = getchar()) != EOF) {
    if (delta == '"') {
      printf("%s", is_left ? "``" : "''");
      is_left = !is_left;
    } else {
      printf("%c", delta);
    }
  }
}
