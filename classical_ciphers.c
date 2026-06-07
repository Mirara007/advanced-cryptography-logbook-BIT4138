#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Fig 1: Caesar Cipher Implementation
void caesarCipher(char* text, int shift, int encrypt) {
    if (!encrypt) shift = -shift; 
    for (int i = 0; text[i] != '\0'; ++i) {
        char ch = text[i];
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            text[i] = (char)(((ch - base + shift) % 26 + 26) % 26 + base);
        }
    }
}

// Fig 2: Vigenere Cipher Encryption Process
void vigenereCipher(char* text, const char* key, int encrypt) {
    int keyLen = strlen(key);
    for (int i = 0, j = 0; text[i] != '\0'; ++i) {
        char ch = text[i];
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            char keyBase = islower(key[j % keyLen]) ? 'a' : 'A';
            int shift = key[j % keyLen] - keyBase;
            
            if (!encrypt) shift = -shift;
            text[i] = (char)(((ch - base + shift) % 26 + 26) % 26 + base);
            j++; 
        }
    }
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int choice;
    char text[256];
    char keyStr[256];
    int shift;

    printf("--- Classical Cryptography Testing Interface ---\n");
    printf("1. Test Caesar Cipher\n");
    printf("2. Test Vigenere Cipher\n");
    printf("Select an option: ");
    
    if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
        printf("Invalid input. Security protocol aborted.\n");
        return 1;
    }
    clearBuffer();

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0; 

    if (choice == 1) {
        printf("Enter shift key (integer): ");
        scanf("%d", &shift);
        caesarCipher(text, shift, 1);
        printf("\n[ENCRYPTED]: %s\n", text);
        caesarCipher(text, shift, 0);
        printf("[DECRYPTED]: %s\n", text);
    } else if (choice == 2) {
        printf("Enter keyword (letters only): ");
        scanf("%s", keyStr);
        vigenereCipher(text, keyStr, 1);
        printf("\n[ENCRYPTED]: %s\n", text);
        vigenereCipher(text, keyStr, 0);
        printf("[DECRYPTED]: %s\n", text);
    }
    return 0;
}
