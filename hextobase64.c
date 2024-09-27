#include <stdio.h>
#include <string.h>

const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void stringToBase64(const char *input) {
    int input_len = strlen(input);
    int i, j;
    unsigned char input_bytes[3];
    unsigned char output_bytes[4];

    for (i = 0; i < input_len;) {
        memset(input_bytes, 0, 3);
        for (j = 0; j < 3 && i < input_len; j++, i++) {
            input_bytes[j] = input[i];
        }

        output_bytes[0] = (input_bytes[0] & 0xFC) >> 2;
        output_bytes[1] = ((input_bytes[0] & 0x03) << 4) | ((input_bytes[1] & 0xF0) >> 4);
        output_bytes[2] = ((input_bytes[1] & 0x0F) << 2) | ((input_bytes[2] & 0xC0) >> 6);
        output_bytes[3] = input_bytes[2] & 0x3F;

        for (j = 0; j < 4; j++) {
            if (j <= (input_len % 3 ? input_len % 3 + 1 : 3)) {
                printf("%c", base64_chars[output_bytes[j]]);
            } else {
                printf("=");
            }
        }
    }

    printf("\n");
}

int main() {
    char input[] = "this is a string to be converted to base 64";

    printf("Base-64 encoded string: ");
    stringToBase64(input);

    return 0;
}

