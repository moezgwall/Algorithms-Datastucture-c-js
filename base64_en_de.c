#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char* base64_encode(const unsigned char* data, size_t len, size_t* out_len) {
    *out_len = 4 * ((len + 2) / 3);
    char* encoded = malloc(*out_len + 1);
    if (!encoded) return NULL;

    size_t i, j = 0;
    for (i = 0; i < len; i += 3) {
        unsigned int triple = 0;
        int remain = len - i;

        triple |= data[i] << 16;
        if (remain > 1) triple |= data[i+1] << 8;
        if (remain > 2) triple |= data[i+2];

        encoded[j++] = base64_chars[(triple >> 18) & 0x3F];
        encoded[j++] = base64_chars[(triple >> 12) & 0x3F];
        encoded[j++] = (remain > 1) ? base64_chars[(triple >> 6) & 0x3F] : '=';
        encoded[j++] = (remain > 2) ? base64_chars[triple & 0x3F] : '=';
    }
    encoded[j] = '\0';
    return encoded;
}


int base64_char_index(char c) {
    if ('A' <= c && c <= 'Z') return c - 'A';
    if ('a' <= c && c <= 'z') return c - 'a' + 26;
    if ('0' <= c && c <= '9') return c - '0' + 52;
    if (c == '+') return 62;
    if (c == '/') return 63;
    return -1;
}

unsigned char* base64_decode(const char* input, size_t* out_len) {
    size_t len = strlen(input);
    if (len % 4 != 0) return NULL; 


    *out_len = len / 4 * 3;
    if (input[len - 1] == '=') (*out_len)--;
    if (input[len - 2] == '=') (*out_len)--;

    unsigned char* decoded = malloc(*out_len + 1);
    if (!decoded) return NULL;

    size_t i = 0, j = 0;
    while (i < len) {
        int idx[4];
        for (int k = 0; k < 4; k++) {
            idx[k] = (input[i + k] == '=') ? 0 : base64_char_index(input[i + k]);
            if (idx[k] == -1 && input[i + k] != '=') { free(decoded); return NULL; }
        }

        decoded[j++] = (unsigned char)((idx[0] << 2) | (idx[1] >> 4));
        if (input[i + 2] != '=')
            decoded[j++] = (unsigned char)(((idx[1] & 0xF) << 4) | (idx[2] >> 2));
        if (input[i + 3] != '=')
            decoded[j++] = (unsigned char)(((idx[2] & 0x3) << 6) | idx[3]);

        i += 4;
    }
    decoded[*out_len] = '\0'; 
    return decoded;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <string-to-encode>\n", argv[0]);
        return 1;
    }

    const char* message = argv[1];
    size_t encoded_len, decoded_len;


    char* encoded = base64_encode((const unsigned char*)message, strlen(message), &encoded_len);
    if (!encoded) {
        printf("Encoding failed!\n");
        return 1;
    }
    printf("Encoded (%zu bytes): %s\n", encoded_len, encoded);

   
    unsigned char* decoded = base64_decode(encoded, &decoded_len);
    if (!decoded) {
        printf("Decoding failed!\n");
        free(encoded);
        return 1;
    }
    printf("Decoded (%zu bytes): %s\n", decoded_len, decoded);

    free(encoded);
    free(decoded);
    return 0;
}