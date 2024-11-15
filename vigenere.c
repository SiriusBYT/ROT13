#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

const char Alphabet[27] = {"abcdefghijklmnopqrstuvwxyz\0"};

void Help() {
    printf("Vigenere v241114 - Usage\n");
    printf("-h\n    Print this help message\n\n");
    printf("-d [String]\n    Decrypt the string\n");
    printf("-e [String]\n    Encrypt the string\n");
    printf("-k [String]\n   Specify the key used for Decrypting/Encrypting\n");
}

// Note: does not support caps lol
int main(int argc, char* argv[]) {    
    // Avoid segmentation fault if there's nothing provided in the arguments
    if (argc == 1) { Help(); return 0; }

    // Handling arguments
    int opt = 0; int Key_Letter = 0; int Letter = 0;
    bool Encrypt;
    char* String; char* Key; // This sounds stupid and might cause problems later on
    while ((opt = getopt(argc, argv, "hk:ed:")) != -1) {
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
            case 'k':
                printf("Setting '%s' as the key...\n", optarg);
                Key = optarg;
                Encrypt = true;
                break;
            case ':':
                printf("Missing argument for '%d'!\n", opt);
                break;
            case '?':
                printf("Unknown argument: '%d'\n", opt);
                break;
        }
    }

    printf("Processing '%s' with key '%s'...\n", String, Key);

    int String_Length = strlen(String);
    int Key_Length = strlen(Key);
    char* Final;
    int Current_Length = 0;

    goto Process;

    // Turn this idiot into a function later u lazy fuckhead
    // not today
    Process:
        for (int cycle = 0; cycle < String_Length; cycle++) {
            if (String[cycle] != '\0') {
                for (int subcycle = 0; subcycle < 26; subcycle++) {
                    if (String[cycle] == Alphabet[subcycle]) {
                        Letter = subcycle;
                        // this looks retarded and I hate it.
                        for (int minicycle = 0; minicycle < 26; minicycle++) {
                            if (Key[cycle % Key_Length] == Alphabet[minicycle]) {
                                Key_Letter = minicycle;
                            }
                        }
                        Letter = ((cycle + Key_Letter) % 26);
                        printf("Shifting letter %c (position %d) to letter %c (position %d)... \n", String[cycle], subcycle, Alphabet[Letter], Letter);
                        Final[cycle] = Alphabet[Letter];
                        break;
                    }
                }
                // If the length of this shit isn't what we expect then a character was skipped so we add it back
                /* this is fucked, will check later
                Current_Length = strlen(Final);
                if (Current_Length != cycle) {
                    Final[cycle] = String[cycle];
                }
                // printf("%c\n", Final[cycle]);
                */
            } else {
                printf("NULL found, stopping! \n");
                goto Output;
            }
        }

    Output:
        Final[String_Length] = '\0';
        printf("Output: '%s'\n", Final);
        return 0;
}
