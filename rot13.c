#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

const char Alphabet[27] = {"abcdefghijklmnopqrstuvwxyz\0"};

void Help() {
    printf("ROT13 v241114 - Usage\n");
    printf("-h\n    Print this help message\n\n");
    printf("-d [String]\n    Decrypt the string by shifting each letter by -13 letters.\n");
    printf("-e [String]\n    Encrypt the string by shifting each letter by +13 letters.\n");
    // printf("-s [int]\n   Shift by [int] letters instead of the default 13.\n"); I'm too lazy to do this
}

// Note: does not support caps lol
int main(int argc, char* argv[]) {    
    // Avoid segmentation fault if there's nothing provided in the arguments
    if (argc == 1) { Help(); return 0; }

    // Handling arguments
    int opt; int Shift = 13; int Letter;
    bool Encrypt;
    char* String; // This sounds stupid and might cause problems later on
    while ((opt = getopt(argc, argv, "he:d:")) != -1) {
        switch (opt) {
            case 'h':
                Help();
                return 0;
                break;
            case 'd':
                printf("Setting '%s' to be decrypted...\n", optarg);
                String = optarg;
                Encrypt = false;
                break;
            case 'e':
                printf("Setting '%s' to be encrypted...\n", optarg);
                String = optarg;
                Encrypt = true;
                break;
            case ':':
                printf("Missing argument for '%d'!\n", opt);
            case '?':
                printf("Unknown argument: '%d'\n", opt);
                break;
        }
    }

    int Displayed_Shift;
    (Encrypt == true) ? (Displayed_Shift=13) : (Displayed_Shift=-13);
    printf("Processing '%s' while shifting every character by '%d'...\n", String, Displayed_Shift);

    int String_Length = sizeof(String) / sizeof(String[0]);
    char Final[String_Length];

    goto Process;

    // Turn this idiot into a function later u lazy fuckhead
    Process:
        for (int cycle = 0; cycle < String_Length; cycle++) {
            switch (String[cycle]) {
                case '\0':
                    // printf("NULL found, stopping! \n");
                    goto Output;
                default:
                    for (int subcycle = 0; subcycle < 26; subcycle++) {
                        if (String[cycle] == Alphabet[subcycle]) {
                            // If we encrypt then we go [SHIFT] amounts forwards, otherwise go backwards.
                            Letter = subcycle;
                            (Encrypt == true) ? (Letter-=Shift) : (Letter-=Shift);
                            // If OOB then readjust
                            if (Letter >= 26) { Letter-=26; }
                            if (Letter < 0 ) { Letter+=26; }
                            //printf("Shifting letter %c (position %d) to letter %c (position %d)... \n", String[cycle], subcycle, Alphabet[Letter], Letter);
                            Final[cycle] = Alphabet[Letter];
                            break;
                        }
                    }
                    // printf("%c\n", Final[cycle]);
                    break;
                }
        }

    Output:
        Final[String_Length] = '\0';
        printf("Output: '%s'\n", Final);
        return 0;
}
