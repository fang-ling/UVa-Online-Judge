//
//  1368.c
//  hxy
//
//  Created by Fang Ling on 2023/12/7.
//

/*
 * For each test case, we first calcualte the frequency of occurence of each
 * nucleotide at each position. Then we choose the nucleotide with the maximum
 * frequency at each position. Finally, we compare the newly generated DNA
 * sequence with the known set to find the consensus error.
 */

#include <stdio.h>

#define var __auto_type

void main_1368(void) {
  char DNAs[50][1000 + 1];
  int frequency[1000][20]; /* ABCDEFGHIJKLMNOPQRST */
  char cDNA[1000 + 1];

  var T = 0;
  scanf("%d", &T);
  while (T--) {
    var m = 0; /* number of DNA sequences */
    var n = 0; /* length of the DNA sequences */
    scanf("%d %d", &m, &n);

    var i = 0;
    for (i = 0; i < m; i += 1) {
      scanf("%s", DNAs[i]);
    }

    /* Calculate frequency array */
    for (i = 0; i < n; i += 1) {
      var j = 0;
      for (j = 0; j < 20; j += 1) {
        frequency[i][j] = 0;
      }
    }
    for (i = 0; i < m; i += 1) {
      var j = 0;
      for (j = 0; j < n; j += 1) {
        frequency[j][DNAs[i][j] - 'A'] += 1;
      }
    }
    for (i = 0; i < n; i += 1) {
      /* find max frequency and character for current char at position i */
      if (frequency[i]['A'-'A'] >= frequency[i]['C'-'A'] &&
          frequency[i]['A'-'A'] >= frequency[i]['G'-'A'] &&
          frequency[i]['A'-'A'] >= frequency[i]['T'-'A']) {
        cDNA[i] = 'A';
      } else if (frequency[i]['C'-'A'] >= frequency[i]['A'-'A'] &&
                 frequency[i]['C'-'A'] >= frequency[i]['G'-'A'] &&
                 frequency[i]['C'-'A'] >= frequency[i]['T'-'A']) {
        cDNA[i] = 'C';
      } else if (frequency[i]['G'-'A'] >= frequency[i]['A'-'A'] &&
                 frequency[i]['G'-'A'] >= frequency[i]['C'-'A'] &&
                 frequency[i]['G'-'A'] >= frequency[i]['T'-'A']) {
        cDNA[i] = 'G';
      } else if (frequency[i]['T'-'A'] >= frequency[i]['A'-'A'] &&
                 frequency[i]['T'-'A'] >= frequency[i]['C'-'A'] &&
                 frequency[i]['T'-'A'] >= frequency[i]['G'-'A']) {
        cDNA[i] = 'T';
      }
    }
    cDNA[n] = '\0';

    var c_error = 0;
    for (i = 0; i < m; i += 1) {
      var j = 0;
      for (j = 0; j < n; j += 1) {
        if (DNAs[i][j] != cDNA[j]) {
          c_error += 1;
        }
      }
    }
    printf("%s\n", cDNA);
    printf("%d\n", c_error);
  }
}
