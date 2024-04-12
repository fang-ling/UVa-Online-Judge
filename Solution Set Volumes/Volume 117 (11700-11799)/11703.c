//
//  11703.c
//  hxy
//
//  Created by Fang Ling on 2024/4/12.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define var __auto_type

static int x(int* X, int i) {
  if (X[i] == -1) {
    X[i] = (x(X, (int)(i - sqrt(i))) +
            x(X, (int)log(i)) +
            x(X, (int)(i * sin(i) * sin(i)))) % 1000000;
  }
  return X[i];
}

void main_11703(void) {
  var X = (int*)malloc(sizeof(int) * 1000001);
  var i = 0;
  for (i = 0; i < 1000001; i += 1) {
    X[i] = -1;
  }
  X[0] = 1;
  
  while (scanf("%d", &i) == 1 && i != -1) {
    printf("%d\n", x(X, i));
  }
  
  free(X);
}
