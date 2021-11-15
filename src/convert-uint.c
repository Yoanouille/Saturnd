#include "convert-uint.h"

uint16_t reverse_byte16(uint16_t n) {
    return (n<<8) | (n>>8);
}

uint32_t reverse_byte32(uint32_t n) {
    uint32_t r = 0x0;
    uint32_t mask = 0x000000ff;
    for(int i = 0; i < 3; i++){
        r |= n&mask;
        n >>= 8;
        r <<= 8;
    }
    return r | (n&mask);
}


uint64_t reverse_byte64(uint64_t n) {
    uint64_t r = 0x0;
    uint64_t mask = 0x00000000000000ff;
    for(int i = 0; i < 7; i++){
        r |= n&mask;
        n >>= 8;
        r <<= 8;
    }
    return r | (n&mask);
}