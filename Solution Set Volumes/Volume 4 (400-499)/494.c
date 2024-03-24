//
//  494.c
//  hxy
//
//  Created by Fang Ling on 2024/3/24.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define var __auto_type

void main_494(void) {
  char buf[128];
  
  var line = (char*)NULL;
  var linecap = (unsigned long)0;
  var count = 0;
  while ((count = (int)getline(&line, &linecap, stdin)) > 0) {
    var word_count = 0;
    
    var i = 0;
    for (i = 0; i < count; i += 1) {
      if (!isalpha(line[i])) {
        line[i] = ' ';
      }
    }
    
    var line_copy = line;
    /*
     * Examples: "aaabbb   asdasd asd"
     *           "    xzcjxzlkadn wdasd"
     */
    while (*line_copy != '\0') {
      /* Skip leading spaces */
      while (*line_copy == ' ') {
        line_copy += 1;
      }
      /* Break if end of string is reached */
      if (*line_copy == '\0') {
        break;
      }
      /* Store current token */
      var j = 0;
      while (*line_copy != ' ' && *line_copy != '\0') {
        buf[j] = *line_copy;
        j += 1;
        line_copy += 1;
      }
      buf[j] = '\0';
      if (j <= 0) { /* Empty string */
        continue;
      }
      for (i = 0; buf[i] != '\0'; i += 1) {
        if (isalpha(buf[i])) {
          word_count += 1;
          break;
        }
      }
    }
    printf("%d\n", word_count);
  }
}
