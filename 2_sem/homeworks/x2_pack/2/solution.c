#include <assert.h>
#include "modular.h"

int main() {
    MOD = 13;
    assert(pnorm(-1) == 12);
    assert(pnorm(4) == 4);
    assert(pnorm(15) == 2);
    assert(padd(7, 7) == 1);
    assert(padd(7, 1) == 8);
    assert(psub(7, 4) == 3);
    assert(psub(4, 7) == 10);
    assert(pmul(2, 3) == 6);
    assert(pmul(10, 2) == 7);
    assert(pdiv(7, 4) == 5);
    assert(pdiv(4, 7) == 8);
    assert(pnorm(1000000000) == 12);
    assert(pnorm(-1000000000) == 1);

    MOD = 999999937;
    assert(pnorm(999999936) == 999999936);
    assert(pnorm(-999999936) == 1);
    assert(padd(999999936, 999999936) == 999999935);
    assert(psub(1, 999999936) == 2);
    assert(pmul(999999935, 999999935) == 4);
    assert(pdiv(999999935, 5) == 199999987);
    assert(pdiv(999999935, 999999935) == 1);
    assert(pdiv(7, 999999935) == 499999965);


    return 0;
}
