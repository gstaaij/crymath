// gstaaij's cryptographic math library
// Also known as crymath or gcm for short
//
// MIT License, see LICENSE or crymath.c
// Copyright (c) 2024 gstaaij

#pragma once
#include <stdbool.h>

#define i64 long long

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

i64 gcm_div(i64 a, i64 b);

i64 gcm_mod(i64 a, i64 m);

i64 gcm_euclidRecursive(i64 a, i64 b);

gcm_EuclidRow* gcm_euclidIterative(i64 a, i64 m);

void gcm_euclidExtended(gcm_EuclidRow* rows, const bool shouldModWithA);
