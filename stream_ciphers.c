#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Fig 1: LFSR Generator Implementation
unsigned int lfsr_step(unsigned int state) {
    // 16-bit LFSR with polynomial x^16 + x^14 + x^13 + x^11 + 1
    unsigned int bit = ((state >> 0) ^ (state >> 2) ^ (state >> 3) ^ (state >> 5)) & 1u;
    return (state >> 1) | (bit << 15);
}

void generate_lfsr_sequence(unsigned int seed, int length) {
    unsigned int state = seed;
    printf("\n[LFSR Sequence]: ");
    for (int i = 0; i < length; i++) {
        printf("%d", state & 1);
        state = lfsr_step(state);
    }
    printf("\n");
}

// Fig 4: RC4 Stream Cipher Simulation (Key Scheduling Algorithm)
void rc4_ksa(unsigned char *key, int key_len, unsigned char *S) {
    int i, j = 0;
    unsigned char temp;
    for (i = 0; i < 256; i++) S[i] = i;
    for (i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key_len]) % 256;
        temp = S[i]; S[i] = S[j]; S[j] = temp;
    }
}

// RC4 Pseudo-Random Generation Algorithm & Encryption
void rc4_prga(unsigned char *S, unsigned char *plaintext, unsigned char *ciphertext) {
    int i = 0, j = 0, n = 0;
    unsigned char temp, K;
    while (plaintext[n] != '\0') {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        temp = S[i]; S[i] = S[j]; S[j] = temp;
        K = S[(S[i] + S[j]) % 256];
        ciphertext[n] = plaintext[n] ^ K; 
        n++;
    }
}

void clearBuffer() { int c; while ((c = getchar()) != '\n' && c != EOF); }

int main() {
    int choice;
    printf("--- Stream Cipher & Randomness Testing ---\n");
    printf("1. Generate LFSR Pseudorandom Sequence\n");
    printf("2. Test RC4 Stream Encryption\n");
    printf("Select protocol: ");
    
    if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
        printf("Invalid input. Aborting.\n");
        return 1;
    }
    clearBuffer();

    if (choice == 1) {
        printf("Enter an initial integer seed: ");
        unsigned int seed;
        scanf("%u", &seed);
        generate_lfsr_sequence(seed, 64); 
    } else if (choice == 2) {
        unsigned char key[256], plaintext[256], ciphertext[256], decrypted[256];
        unsigned char S[256];
        
        printf("Enter RC4 Key: ");
        fgets((char*)key, sizeof(key), stdin);
        key[strcspn((char*)key, "\n")] = 0;
        
        printf("Enter Text to Encrypt: ");
        fgets((char*)plaintext, sizeof(plaintext), stdin);
        plaintext[strcspn((char*)plaintext, "\n")] = 0;

        // Encrypt
        rc4_ksa(key, strlen((char*)key), S);
        rc4_prga(S, plaintext, ciphertext);
        
        printf("\n[ENCRYPTED HEX]: ");
        for(int i = 0; i < strlen((char*)plaintext); i++) printf("%02X", ciphertext[i]);
        
        // Decrypt 
        rc4_ksa(key, strlen((char*)key), S);
        rc4_prga(S, ciphertext, decrypted);
        decrypted[strlen((char*)plaintext)] = '\0';
        
        printf("\n\n[DECRYPTED TEXT]: %s\n", decrypted);
    }
    return 0;
}
