#include<stdio.h>
#include<stdlib.h>

void print_string(char* buffer, int size) {
    printf(" |");
    for (int i = 0; i < size; i++) {
        char ch = buffer[i];
        
        // display clear text characters and
        // replace special characters with dot
        if (0x20 <= ch && ch <= 0x7e)
            printf("%c", ch);
        else
            printf(".");
    }
    printf("|\n");
}


int main() {
    int ch; // character variable
    int mem_a = 0x0; // memory address
    char *buffer = (char *) calloc(0x10, sizeof(char));   // allocate spaces for 16 characters

    // read the input memory that we feed via stdin
    while ((ch = getchar()) != EOF) {
        // mem_a % 0x10 means the number of characters in each row
       
        buffer[mem_a % 0x10] = ch;
        
        // printing every 16th (0x10) memory address
        // x: format specifier for hexadecimal
        // 0: for padding zero
        // 8: each character's width being at least 8
        if (mem_a % 0x10 == 0x0)
            printf("%08x  ", mem_a);

        // printing each character
        printf("%02x ", ch); 

        // increment the memory address
        mem_a++;

        // print the string at the end of each row
        if (mem_a % 0x10 == 0x0)
            print_string(buffer, 0x10);

        // add one extra space between two sections (each section contains 8 hex values)
        if (mem_a % 0x10 == 8)
            printf(" ");

    }
    
    int n = mem_a % 0x10;
    int spaces = 3 * (0x10 - n);

    if (n < 8)
        spaces++;

    if (n && spaces)
        printf("%*s", spaces, " ");     // filling the last empty line with spaces

    if (n % 0x10 != 0)
        print_string(buffer, n);      // printing the last line
                                    
    if (mem_a != 0x0)
        printf("%08x\n", mem_a);     // last memeory address

    free(buffer);     // free the allocated memory

    return 0;
}
