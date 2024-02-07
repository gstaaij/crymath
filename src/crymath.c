// gstaaij's cryptographic math library
// Also known as crymath or gcm for short
//
// MIT License
//
// Copyright (c) 2024 gstaaij
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#include "crymath.h"
#include "stb_ds.h"

/// TODO: make this a library (cryptomath) (or crymath?)

i64 gcm_div(i64 a, i64 b) {
    i64 k = a / b;
    while (k * b <= a)
        ++k;
    while (k * b > a)
        --k;
    return k;
}

// a mod m = a - m * (a div m)
i64 gcm_mod(i64 a, i64 m) {
    return a - m * gcm_div(a, m);
}

i64 gcm_euclidRecursive(i64 a, i64 b) {
    if (b > a) {
        i64 temp = a;
        a = b;
        b = temp;
    }
    if (gcm_mod(a, b) == 0)
        return b;
    return gcm_euclidRecursive(b, gcm_mod(a, b));
}

gcm_EuclidRow* gcm_euclidIterative(i64 a, i64 m) {
    gcm_EuclidRow* rows = NULL;
    gcm_EuclidRow currentRow = {0};
    currentRow.a = a;
    currentRow.m = m;
    do {
        currentRow.q = currentRow.a / currentRow.m;
        currentRow.r = currentRow.a % currentRow.m;
        i64 aNext = currentRow.m;
        i64 mNext = currentRow.r;
        arrput(rows, currentRow);
        currentRow = (gcm_EuclidRow) {0};
        currentRow.a = aNext;
        currentRow.m = mNext;
    } while (currentRow.m != 0);
    arrput(rows, currentRow);
    return rows;
}

void gcm_euclidExtended(gcm_EuclidRow* rows, const bool shouldModWithA) {
    size_t len = arrlenu(rows);
    rows[len - 1].b = 1;
    rows[len - 1].k = 0;
    for (long i = arrlenu(rows) - 2; i >= 0; --i) {
        rows[i].b = rows[i + 1].k;
        rows[i].k = rows[i + 1].b - rows[i].q * rows[i + 1].k;

        if (shouldModWithA) {
            rows[i].k = gcm_mod(rows[i].k, rows[0].a);
        }
    }
}
