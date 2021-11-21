# Assignment 6 Huffman encoding
The programs included are an RSA key generator, encryptor, and decryptor, for encrypting messages using RSA encryption, and generation RSA public-private key pairs. The programs use the gmp library to enable usage of numbers larger than 64 bits.
## Run the following to build the programs:
```
$ make
```
For keygen only
```
$ make keygen
```
For encrypt only
```
$ make encrypt
```
For decrypt only
```
$ make decrypt
```
## Running
```
./keygen -args
```
SYNOPSIS
   Generates an RSA public/private key pair.

USAGE
   ./keygen [-hv] [-b bits] -n pbfile -d pvfile

OPTIONS
   -h              Display program help and usage.
   -v              Display verbose program output.
   -b bits         Minimum bits needed for public key n (default: 256).
   -i confidence   Miller-Rabin iterations for testing primes (default: 50).
   -n pbfile       Public key file (default: rsa.pub).
   -d pvfile       Private key file (default: rsa.priv).
   -s seed         Random seed for testing.
```
./encrypt -args
```
SYNOPSIS
   Encrypts data using RSA encryption.
   Encrypted data is decrypted by the decrypt program.

USAGE
   ./encrypt [-hv] [-i infile] [-o outfile] -n pubkey

OPTIONS
   -h              Display program help and usage.
   -v              Display verbose program output.
   -i infile       Input file of data to encrypt (default: stdin).
   -o outfile      Output file for encrypted data (default: stdout).
   -n pbfile       Public key file (default: rsa.pub).
```
./decrypt -args
```
SYNOPSIS
   Decrypts data using RSA decryption.
   Encrypted data is encrypted by the encrypt program.

USAGE
   ./decrypt [-hv] [-i infile] [-o outfile] -n privkey

OPTIONS
   -h              Display program help and usage.
   -v              Display verbose program output.
   -i infile       Input file of data to decrypt (default: stdin).
   -o outfile      Output file for decrypted data (default: stdout).
   -n pvfile       Private key file (default: rsa.priv).
```

