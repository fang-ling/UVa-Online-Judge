//
//  10300.c
//  hxy
//
//  Created by Fang Ling on 2023/12/9.
//

/*
 * premium_k = size_k / animal_k * envfir_k * animal_k
 *           = size_k * envfir_k
 * premium = ∑premium_k
 *
 * if animal_k == 0, then premium_k = 0.
 */

#include <stdio.h>

#define var __auto_type

void main_10300(void) {
  var n = 0;
  scanf("%d", &n);
  while (n--) {
    var sum = 0ll;
    var f = 0;
    scanf("%d", &f);
    while (f--) {
      var size = 0;
      var animal = 0;
      var envfri = 0;
      scanf("%d %d %d", &size, &animal, &envfri);
      if (animal != 0) {
        sum += (long long)size * envfri;
      }
    }
    printf("%lld\n", sum);
  }
}
