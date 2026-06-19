#include "prime.h"
#include <math.h>

int is_prime(int x) {
    if (x < 2) return 0;
    if (x % 2 == 0) return 0;
    
    double dx = sqrt(x);
    int i = 3;
    while (i < dx) {
        if (x % i == 0) return 0;
        i ++;
    }
    return 1;
}

int next_prime(int x) {
    int i = x + 1;
    for (;;)
        if (is_prime(i++))
            return --i;
    
}
