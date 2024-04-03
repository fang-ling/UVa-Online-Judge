//
//  12289.c
//  hxy
//
//  Created by Fang Ling on 2024/4/3.
//

#include <stdio.h>
#include <string.h>

#define var __auto_type

void main_12289(void) {
  char word[8];
  
  var n = 0;
  scanf("%d", &n);
  while (n--) {
    scanf("%s", word);
    var count = (int)strlen(word);
    if (count == 5) {
      printf("3\n");
    } else {
      if (
        (word[0] == 'o' && word[1] == 'n') ||
        (word[1] == 'n' && word[2] == 'e') ||
        (word[0] == 'o' && word[2] == 'e')
      ) {
        printf("1\n");
      } else {
        printf("2\n");
      }
    }
  }
}
