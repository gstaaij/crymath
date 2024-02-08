// gstaaij's cryptographic math library
// Also known as crymath or gcm for short
//
// MIT License, see LICENSE or crymath.c
// Copyright (c) 2024 gstaaij

#pragma once
#include <stdbool.h>

// I'm too lazy to type "long long" every time
#define i64 long long

// A row in the Euclid's algorithm table
typedef struct {
    // a div m = q
    // a mod m = r

    i64 a;
    i64 m;
    i64 q;
    i64 r;

    // The extended part:

    i64 b;
    i64 k;
    // ab + mk = gcd(a, m)
} gcm_EuclidRow;

// Returns the largest k for b * k <= a
i64 gcm_div(i64 a, i64 b);

// a mod m = a - m * (a div m)
i64 gcm_mod(i64 a, i64 m);

// Runs the recursive version of the algorithm of Euclid and returns the result (gcd)
i64 gcm_euclidRecursive(i64 a, i64 b);

// Runs the iterative version of the algorithm of Euclid and returns a list of EuclidRows
gcm_EuclidRow* gcm_euclidIterative(i64 a, i64 m);

// Runs the extended algorithm of Euclid on a list of EuclidRows that has been generated with the gcm_euclidIterative function
void gcm_euclidExtended(gcm_EuclidRow* rows, const bool shouldModWithA);
