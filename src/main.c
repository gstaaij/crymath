#include <stdio.h>
#include "crymath.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

int main() {
    const long long divtest1 = -240;
    const long long divtest2 = 25;
    printf("%lld // %lld = %lld\n\n", divtest1, divtest2, gcm_div(divtest1, divtest2));


    const long long a = 3573253;
    const long long m = 25546;

    printf("Recursive euclides gcd(%lld, %lld) = %lld\n\n", a, m, gcm_euclidRecursive(a, m));

    gcm_EuclidRow* rows = gcm_euclidIterative(a, m);
    gcm_euclidExtended(rows, false);

    size_t len = arrlenu(rows);
    printf("a\t\tm\t\tq\t\tr\t\tb\t\tk\n");
    for (size_t i = 0; i < len; ++i) {
        printf("%lld\t\t%lld\t\t%lld\t\t%lld\t\t%lld\t\t%lld\n", rows[i].a, rows[i].m, rows[i].q, rows[i].r, rows[i].b, rows[i].k);
    }
    printf("\n");

    printf("a_0 * b_0 + m_0 * k_0 = gcd(a_0, m_0) = a_last\n");
    printf("%lld * %lld + %lld * %lld = %lld\n", rows[0].a, rows[0].b, rows[0].m, rows[0].k, rows[len - 1].a);
    printf("\n");

    printf("(m_0 * k_0) %% a_0 = gcd(a_0, m_0) = a_last\n");
    printf("(%lld * %lld) %% %lld = %lld\n", rows[0].m, rows[0].k, rows[0].a, rows[len - 1].a);
    printf("(%lld * %lld) %% %lld = %lld\n", gcm_mod(rows[0].m, rows[0].a), gcm_mod(rows[0].k, rows[0].a), rows[0].a, rows[len - 1].a);
    printf("\n");

    printf("(a_0 * b_0) %% m_0 = gcd(a_0, m_0) = a_last\n");
    printf("(%lld * %lld) %% %lld = %lld\n", rows[0].a, rows[0].b, rows[0].m, rows[len - 1].a);
    printf("(%lld * %lld) %% %lld = %lld\n", gcm_mod(rows[0].a, rows[0].m), gcm_mod(rows[0].b, rows[0].m), rows[0].m, rows[len - 1].a);

    return 0;
}
