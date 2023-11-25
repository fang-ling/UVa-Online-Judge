//
//  272.c
//  hxy
//
//  Created by Fang Ling on 2023/11/25.
//

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
