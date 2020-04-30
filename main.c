#include <stdio.h>
#include "packet.h"

int main() {
    printf("gcomo: %lu\n", sizeof(gcomo_t));
    printf("downconverter: %lu\n", sizeof(downconverter_t));
    printf("adb3l: %lu\n", sizeof(adb3l_t));
    printf("core3h: %lu\n", sizeof(core3h_t));
    printf("bbc: %lu\n", sizeof(bbc_t));
    printf("full: %lu\n", sizeof(dbbc3_ddc_multicast_t));
}
