//
//  492.c
//  hxy
//
//  Created by Fang Ling on 2024/4/12.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define var __auto_type

void main_492(void) {
  var buf = (char*)malloc(sizeof(char) * 1024 * 1024 * 1024);
  
  var i = 0;
  var c = '\0';
  while ((c = getchar()) != EOF) {
    if (!isalpha(c)) {
      buf[i] = '\0';
      i = 0;
      if (
        buf[0] == 'a' || buf[0] == 'e' || buf[0] == 'i' || buf[0] == 'o' ||
        buf[0] == 'u' || buf[0] == 'A' || buf[0] == 'E' || buf[0] == 'I' ||
        buf[0] == 'O' || buf[0] == 'U'
      ) {
        printf("%say", buf);
      } else if (isalpha(buf[0])) {
        var cc = buf[0];
        memmove(buf, buf + 1, strlen(buf) - 1);
        buf[strlen(buf) - 1] = cc;
        printf("%say", buf);
      }
      printf("%c", c);
    } else {
      buf[i] = c;
      i += 1;
    }
  }
  
  free(buf);
}
