#include <cstdio>
extern "C" {
#include <libfec/fec.h>
#include <libfec/fixed.h>
#include <libfec/tables.h>
}
#include <stdio.h>

int main() {
    unsigned char data[NN - NROOTS] = {0};
    unsigned char parity[NROOTS] = {0};
    for (int i = 0; i < NN - NROOTS; i++) {
        data[i] = (i * 100) % 255;
    }
    encode_rs_ccsds(data, parity);
    printf("Results: ");
    for (int i = 0; i < NN; i++) {
        if (i < NN - NROOTS) {
            printf("%d, ",(int)data[i]);
        } else {
            printf("%d, ",(int)parity[i - NN + NROOTS]);
        }
    }

    return 0;
}