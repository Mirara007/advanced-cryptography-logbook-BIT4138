#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

void handleErrors(void) { printf("Cryptography Error.\n"); exit(1); }

// Fig 3: File Encryption Demonstration
double encrypt_file(const char *in_file, const char *out_file, unsigned char *key, unsigned char *iv) {
    FILE *ifp = fopen(in_file, "rb"), *ofp = fopen(out_file, "wb");
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    unsigned char in_buf[1024], out_buf[1024 + EVP_MAX_BLOCK_LENGTH];
    int in_len, out_len;
    clock_t start = clock(); // Start performance timer

    while ((in_len = fread(in_buf, 1, 1024, ifp)) > 0) {
        EVP_EncryptUpdate(ctx, out_buf, &out_len, in_buf, in_len);
        fwrite(out_buf, 1, out_len, ofp);
    }
    EVP_EncryptFinal_ex(ctx, out_buf, &out_len);
    fwrite(out_buf, 1, out_len, ofp);

    clock_t end = clock();
    EVP_CIPHER_CTX_free(ctx); fclose(ifp); fclose(ofp);
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

// Fig 4: Decryption Results
double decrypt_file(const char *in_file, const char *out_file, unsigned char *key, unsigned char *iv) {
    FILE *ifp = fopen(in_file, "rb"), *ofp = fopen(out_file, "wb");
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    unsigned char in_buf[1024], out_buf[1024 + EVP_MAX_BLOCK_LENGTH];
    int in_len, out_len;
    clock_t start = clock();

    while ((in_len = fread(in_buf, 1, 1024, ifp)) > 0) {
        EVP_DecryptUpdate(ctx, out_buf, &out_len, in_buf, in_len);
        fwrite(out_buf, 1, out_len, ofp);
    }
    EVP_DecryptFinal_ex(ctx, out_buf, &out_len);
    fwrite(out_buf, 1, out_len, ofp);

    clock_t end = clock();
    EVP_CIPHER_CTX_free(ctx); fclose(ifp); fclose(ofp);
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

int main() {
    printf("--- Week 4: AES File Encryption & Performance ---\n");

    // Fig 2: Key Generation Process
    unsigned char key[32], iv[16];
    if (!RAND_bytes(key, sizeof(key)) || !RAND_bytes(iv, sizeof(iv))) handleErrors();
    printf("[+] Secure 256-bit AES Key and IV Generated via OpenSSL RAND_bytes.\n");

    // Create a dummy file to encrypt
    FILE *fp = fopen("secret.txt", "w");
    for(int i=0; i<50000; i++) fprintf(fp, "MKU Cryptography Padding Data... ");
    fclose(fp);

    // Fig 5: AES Performance Testing
    printf("[+] Encrypting 'secret.txt' to 'encrypted.bin'...\n");
    double enc_time = encrypt_file("secret.txt", "encrypted.bin", key, iv);
    printf("    -> Encryption Time: %f seconds\n", enc_time);

    printf("[+] Decrypting 'encrypted.bin' to 'decrypted.txt'...\n");
    double dec_time = decrypt_file("encrypted.bin", "decrypted.txt", key, iv);
    printf("    -> Decryption Time: %f seconds\n", dec_time);

    return 0;
}
