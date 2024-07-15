#include <stdio.h>
#include "include\huffman.h"

int main() {
    int choice;
    char ifname[100], ofname[100];

    printf("Choose operation (1: Compress, 2: Decompress): ");
    if (scanf("%d", &choice) != 1) {
        fprintf(stderr, "Error reading choice\n");
        return 1;
    }

    if (choice == 1) {
        printf("Enter input filename: ");
        if (scanf("%s", ifname) != 1) {
            fprintf(stderr, "Error reading input filename\n");
            return 1;
        }
        printf("Enter output filename: ");
        if (scanf("%s", ofname) != 1) {
            fprintf(stderr, "Error reading output filename\n");
            return 1;
        }
        if (compress(ifname, ofname) != 0) {
            fprintf(stderr, "Compression failed\n");
            return 1;
        }
    } else if (choice == 2) {
        printf("Enter input filename: ");
        if (scanf("%s", ifname) != 1) {
            fprintf(stderr, "Error reading input filename\n");
            return 1;
        }
        printf("Enter output filename: ");
        if (scanf("%s", ofname) != 1) {
            fprintf(stderr, "Error reading output filename\n");
            return 1;
        }
        if (extract(ifname, ofname) != 0) {
            fprintf(stderr, "Decompression failed\n");
            return 1;
        }
    } else {
        fprintf(stderr, "Invalid choice\n");
        return 1;
    }

    return 0;
}
