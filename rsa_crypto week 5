import sys
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.primitives.asymmetric import padding
from cryptography.hazmat.primitives import hashes

# Fig 1: RSA Key Pair Generation
def generate_keypair():
    """Generates a 2048-bit RSA private/public key pair."""
    # public_exponent=65537 is the standard equivalent to RSA_F4
    private_key = rsa.generate_private_key(
        public_exponent=65537,
        key_size=2048,
    )
    return private_key

# Fig 2: Public Key Encryption Process
def public_encrypt(data: bytes, public_key) -> bytes:
    """Encrypts data using the public key and OAEP padding."""
    # Using SHA1 to match OpenSSL's default RSA_PKCS1_OAEP_PADDING behavior
    pad = padding.OAEP(
        mgf=padding.MGF1(algorithm=hashes.SHA1()),
        algorithm=hashes.SHA1(),
        label=None
    )
    return public_key.encrypt(data, pad)

# Fig 3: Private Key Decryption Results
def private_decrypt(enc_data: bytes, private_key) -> bytes:
    """Decrypts data using the private key and OAEP padding."""
    pad = padding.OAEP(
        mgf=padding.MGF1(algorithm=hashes.SHA1()),
        algorithm=hashes.SHA1(),
        label=None
    )
    return private_key.decrypt(enc_data, pad)

def main():
    print("--- Week 5: RSA Public Key Cryptography ---")

    try:
        private_key = generate_keypair()
        public_key = private_key.public_key()
        print("[+] RSA 2048-bit Key Pair Generated.")
    except Exception as e:
        print(f"Key generation failed: {e}", file=sys.stderr)
        sys.exit(1)

    plaintext = b"MKU Classified Directive - Asymmetric Transfer"

    # Fig 4: Secure Message Transmission (Encryption Output)
    try:
        encrypted = public_encrypt(plaintext, public_key)
        
        print("\n[SECURE TRANSMISSION - ENCRYPTED HEX]:")
        # Python's .hex() handles the formatting natively
        print(encrypted.hex())
        
    except Exception as e:
        print(f"Encryption failed: {e}", file=sys.stderr)
        sys.exit(1)

    # Fig 5: RSA Testing and Validation (Decryption Output)
    try:
        decrypted_bytes = private_decrypt(encrypted, private_key)
        decrypted = decrypted_bytes.decode('utf-8')
        
        print(f"\n[VALIDATION - DECRYPTED TEXT]:\n{decrypted}\n")
        print("[+] Validation Successful: Asymmetric transmission secure.")
        
    except Exception as e:
        print(f"Decryption failed: {e}", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()
