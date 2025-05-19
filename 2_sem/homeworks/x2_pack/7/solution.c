#include <assert.h>
#include <stdio.h>
#include "primes.h"


int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    // Проверка isPrime
    assert(isPrime(2) == 1);    // минимальное простое
    assert(isPrime(3) == 1);    // простое
    assert(isPrime(4) == 0);    // составное
    assert(isPrime(1) == 0);    // 1 - не простое
    assert(isPrime(-5) == 0);   // отрицательное
    assert(isPrime(17) == 1);   // большое простое

    // Проверка findNextPrime
    assert(findNextPrime(2) == 2);  // уже простое
    assert(findNextPrime(4) == 5);  // следующее после составного
    assert(findNextPrime(13) == 13); // граничное простое
    assert(findNextPrime(1) == 2);  // минимальный случай
    assert(findNextPrime(25) == 29); // перескакиваем несколько чисел

    // Проверка getPrimesCount
    assert(getPrimesCount(2, 3) == 1);   // один элемент
    assert(getPrimesCount(2, 10) == 4);  // несколько простых
    assert(getPrimesCount(10, 20) == 4); // диапазон без начальной границы
    assert(getPrimesCount(5, 5) == 0);   // нулевой диапазон
    assert(getPrimesCount(0, 100) == 25);// известное количество простых
    assert(getPrimesCount(20, 10) == 0); // обратный диапазон

    return 0;
}