#include <stdio.h>
#include <openssl/opensslv.h>

int main() {
    printf("Advanced Cryptography Environment Setup Successful!\n");
    printf("Using %s on Kali Linux VM\n", OPENSSL_VERSION_TEXT);
    return 0;
}
