//
//  509.c
//  hxy
//
//  Created by Fang Ling on 2024/2/4.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define var __auto_type

struct String {
  char str[128];
};

static bool is_available_509(struct String* stripe, int count) {
  var i = 0;
  for (i = 0; i < count; i += 1) {
    var len = (int)strlen(stripe[i].str);
    var j = 0;
    for (j = 0; j < len; j += 1) {
      if (stripe[i].str[j] == 'x') {
        return false;
      }
    }
  }
  return true;
}

static bool recovery_509(struct String* stripe, int count, int parity, int s) {
  if (is_available_509(stripe, count)) {
    var i = 0;
    for (i = 0; i < s; i += 1) {
      var x = 0; /* p xor 0 = p */
      var j = 0;
      for (j = 0; j < count; j += 1) {
        x ^= stripe[j].str[i] - '0';
      }
      if (x != parity) {
        return false;
      }
    }
  }
  var i = 0;
  for (i = 0; i < s; i += 1) {
    var unavailable_count = 0;
    var j = 0;
    for (j = 0; j < count; j += 1) {
      if (stripe[j].str[i] == 'x') {
        unavailable_count += 1;
      }
    }
    if (unavailable_count > 1) {
      return false;
    }
  }
  /* Start recovery */
  for (i = 0; i < s; i += 1) {
    var x = 0;
    var x_pos = -1;
    
    var j = 0;
    for (j = 0; j < count; j += 1) {
      if (stripe[j].str[i] != 'x') {
        x ^= stripe[j].str[i] - '0';
      } else {
        x_pos = j;
      }
    }
    if (x_pos == -1) {
      if (x != parity) {
        return false;
      }
      continue;
    }
    x ^= parity;
    stripe[x_pos].str[i] = x + '0';
  }
  return true;
}

/* strtol causes SIGABRT, don't know why. */
/*static int _string2int(const char* string) {
  var result = 0;
  var count = (int)strlen(string);
  
  var i = 0;
  var pow = 1;
  for (i = count - 1; i >= 0; i -= 1) {
    result += (string[i] - '0') * pow;
    pow *= 2;
  }
  
  return result;
}*/

void to_string(struct String stripes[100][6], int d, int s, int b) {
  var res = (char*)malloc(d * s * b * sizeof(char));
  var res_count = 0;
  var i = 0;
  for (i = 0; i < b; i += 1) {
    var j = 0;
    for (j = 0; j < d; j += 1) {
      if (i % d == j) { /* Parity data */
        continue;
      }
      var k = 0;
      for (k = 0; k < s; k += 1) {
        res[res_count] = stripes[i][j].str[k];
        res_count += 1;
      }
    }
  }
  while (res_count % 4 != 0) {
    res[res_count] = '0';
    res_count += 1;
  }
  var len = res_count / 4;
  char buf[8];
  for (i = 0; i < len; i += 1) {
    var buf_i = 0;
    var k = 0;
    for (k = i * 4; k < (i + 1) * 4; k += 1) {
      buf[buf_i] = res[k];
      buf_i += 1;
    }
    buf[buf_i] = '\0';
    printf("%X", /*_string2int(buf)*/(int)strtol(buf, NULL, 2));
  }
  
  free(res);
}

void main_509(void) {
  var read_buf = (char*)malloc(8192 * sizeof(char));
  struct String disks[6][100];
  struct String stripes[100][6];
  
  var disk_count = 0;
  var d = 0;
  while (scanf("%d", &d) == 1 && d != 0) {
    var s = 0;
    var b = 0;
    scanf("%d %d", &s, &b);
    scanf("%s", read_buf);
    var is_even = read_buf[0] == 'E' ? 0 : 1;
    
    var i = 0;
    for (i = 0; i < d; i += 1) { /* Read each disk */
      scanf("%s", read_buf);
      var j = 0;
      for (j = 0; j < b; j += 1) {
        var k = 0;
        for (k = 0; k < s; k += 1) {
          disks[i][j].str[k] = read_buf[j * s + k];
        }
        disks[i][j].str[k] = '\0';
      }
    }
    for (i = 0; i < b; i += 1) { /* Transpose disks */
      var j = 0;
      for (j = 0; j < d; j += 1) {
        stripes[i][j] = disks[j][i];
      }
    }
    var status = 2; /* 0: fail; 1: recoverable; 2: ok */
    for (i = 0; i < b; i += 1) {
      if (!recovery_509(stripes[i], d, is_even, s)) {
        status = 0;
      }
    }
    disk_count += 1;
    if (status == 0) {
      printf("Disk set %d is invalid.\n", disk_count);
    } else {
      printf("Disk set %d is valid, contents are: ", disk_count);
      to_string(stripes, d, s, b);
      printf("\n");
    }
  }
  
  free(read_buf);
}
