//
//  10763.c
//  hxy
//
//  Created by Fang Ling on 2024/4/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define var __auto_type

static int compare(const void* a, const void* b) {
  var _a = *(int*)a;
  var _b = *(int*)b;
  if (_a > _b) {
    return 1;
  } else if (_a < _b) {
    return -1;
  }
  return 0;
}

void main_10763(void) {
  var origin = (int*)malloc(sizeof(int) * 500000);
  var foreign = (int*)malloc(sizeof(int) * 500000);
  
  var n = 0;
  while (scanf("%d", &n) == 1 && n != 0) {
    var i = 0;
    for (i = 0; i < n; i += 1) {
      scanf("%d %d", &origin[i], &foreign[i]);
    }
    
    qsort(origin, n, sizeof(int), compare);
    qsort(foreign, n, sizeof(int), compare);
    printf("%s\n", memcmp(origin, foreign, n*sizeof(int)) == 0 ? "YES" : "NO");
  }
  
  free(origin);
  free(foreign);
}
