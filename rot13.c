#include <stdio.h>

int main(int argc, char* argv[]) {
    char alphabet[27] = {"abcdefghijklmnopqrstuvwxyz\0"};
    // printf("%s\n", alphabet);

    char* decrypted = argv[1];
    int text_length = sizeof(decrypted) / sizeof(decrypted[0]);
    char encrypted[text_length];
    int shift = 0;
    printf("ROT13-ing '%s'...\n\n", decrypted);

    Encrypt:
        for (int cycle = 0; cycle < text_length; cycle++) {
            switch (decrypted[cycle]) {
            case '\0':
                printf("NULL found, stopping! \n");
                break;
            default:
                for (int subcycle = 0; subcycle < 26; subcycle++) {
                    if (decrypted[cycle] == alphabet[subcycle]) {
                        shift = subcycle+13;
                        if (shift > 26) { shift-=26; }
                        printf("Shifting letter %c (position %d) to letter %c (position %d)... \n", decrypted[cycle], subcycle, alphabet[shift], shift);
                        encrypted[cycle] = alphabet[shift];
                        break;
                    }
                }
                break;
            }
        }

    Output:
        encrypted[text_length] = '\0';
        printf("ROT13-ified: '%s'\n", encrypted);
        printf("%d\n", text_length);
}