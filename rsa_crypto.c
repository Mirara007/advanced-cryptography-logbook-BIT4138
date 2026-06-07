#include <stdio.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

int padding = RSA_PKCS1_OAEP_PADDING;

// Fig 1: RSA Key Pair Generation
RSA *generate_keypair() {
    RSA *rsa = RSA_new();
    BIGNUM *bne = BN_new();
    BN_set_word(bne, RSA_F4);
    RSA_generate_key_ex(rsa, 2048, bne, NULL);
    BN_free(bne);
    return rsa;
}

// Fig 2: Public Key Encryption Process
int public_encrypt(unsigned char *data, int data_len, RSA *rsa, unsigned char *encrypted) {
    return RSA_public_encrypt(data_len, data, encrypted, rsa, padding);
}

// Fig 3: Private Key Decryption Results
int private_decrypt(unsigned char *enc_data, int data_len, RSA *rsa, unsigned char *decrypted) {
    return RSA_private_decrypt(data_len, enc_data, decrypted, rsa, padding);
}

int main() {
    printf("--- Week 5: RSA Public Key Cryptography ---\n");

    RSA *keypair = generate_keypair();
    printf("[+] RSA 2048-bit Key Pair Generated.\n");

    unsigned char plaintext[] = "MKU Classified Directive - Asymmetric Transfer";
    unsigned char encrypted[4096];
    unsigned char decrypted[4096];

    // Fig 4: Secure Message Transmission (Encryption Output)
    int encrypted_length = public_encrypt(plaintext, strlen((char*)plaintext), keypair, encrypted);
    if(encrypted_length == -1) {
        ERR_print_errors_fp(stderr);
        return 1;
    }

    printf("\n[SECURE TRANSMISSION - ENCRYPTED HEX]:\n");
    for(int i = 0; i < encrypted_length; i++) printf("%02x", encrypted[i]);
    printf("\n");

    // Fig 5: RSA Testing and Validation (Decryption Output)
    int decrypted_length = private_decrypt(encrypted, encrypted_length, keypair, decrypted);
    if(decrypted_length == -1) {
        ERR_print_errors_fp(stderr);
        return 1;
    }
    decrypted[decrypted_length] = '\0';

    printf("\n[VALIDATION - DECRYPTED TEXT]:\n%s\n\n", decrypted);
    printf("[+] Validation Successful: Asymmetric transmission secure.\n");

    RSA_free(keypair);
    return 0;
}
