//
//  201.c
//  hxy
//
//  Created by Fang Ling on 2024/1/17.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define var __auto_type

static int get_ptr_id_201(int i, int j, int n) {
  return i * n + j;
}

static bool is_square(bool board[121][121], int pid, int n, int length) {
  /* Top */
  var l = 0;
  for (l = 0; l < length; l += 1) {
    if (!board[pid + l][pid + l + 1]) {
      return false;
    }
  }
  /* Left */
  for (l = 0; l < length; l += 1) {
    if (!board[pid + l * n][pid + l * n + n]) {
      return false;
    }
  }
  /* Down */
  pid += length * n;
  for (l = 0; l < length; l += 1) {
    if (!board[pid + l][pid + l + 1]) {
      return false;
    }
  }
  /* Right */
  pid -= length * n;
  pid += length;
  for (l = 0; l < length; l += 1) {
    if (!board[pid + l * n][pid + l * n + n]) {
      return false;
    }
  }
  return true;
}

void main_201(void) {
  bool board[121][121];
  int cnt[10];
  char direction[2];
  
  var is_first = true;
  var problem = 0;
  var n = 0;
  var m = 0;
  while (scanf("%d %d", &n, &m) == 2) {
    var i = 0;
    for (i = 0; i < 10; i += 1) {
      cnt[i] = 0;
    }
    for (i = 0; i < (n + 2) * (n + 2); i += 1) {
      var j = 0;
      for (j = 0; j < 121; j += 1) {
        board[i][j] = false;
      }
    }

    for (i = 0; i < m; i += 1) {
      scanf("%s", direction);
      var x = 0;
      var y = 0;
      scanf("%d %d", &x, &y);
      x -= 1;
      y -= 1;
      if (direction[0] == 'H') {
        board[get_ptr_id_201(x, y, n)][get_ptr_id_201(x, y + 1, n)] = true;
        board[get_ptr_id_201(x, y + 1, n)][get_ptr_id_201(x, y, n)] = true;
      } else {
        var delta = x;
        x = y;
        y = delta;
        board[get_ptr_id_201(x, y, n)][get_ptr_id_201(x + 1, y, n)] = true;
        board[get_ptr_id_201(x + 1, y, n)][get_ptr_id_201(x, y, n)] = true;
      }
    }
    for (i = 0; i < n * n; i += 1) {
      var l = 0;
      for (l = 1; l <= n; l += 1) {
        if (is_square(board, i, n, l)) {
          cnt[l] += 1;
        }
      }
    }
    
    if (!is_first) {
      printf("\n**********************************\n\n");
    } else {
      is_first = false;
    }
    printf("Problem #%d\n\n", problem += 1);
    var is_result = false;
    for (i = 1; i <= n; i += 1) {
      if (cnt[i] != 0) {
        is_result = true;
      }
    }
    if (is_result) {
      for (i = 1; i <= n; i += 1) {
        if (cnt[i] == 0) {
          continue;
        }
        printf("%d square (s) of size %d\n", cnt[i], i);
      }
    } else {
      printf("No completed squares can be found.\n");
    }
  }
}
