#include <stdio.h>
#include "huffman.h"

int main() {
    int choice;
    char ifname[100], ofname[100];
    char* filepath;

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
        filepath = find_file(ifname);
        if (filepath == NULL) {
            fprintf(stderr, "Input file does not exist\n");
            return 1;
        }
        printf("Enter output filename: ");
        if (scanf("%s", ofname) != 1) {
            fprintf(stderr, "Error reading output filename\n");
            return 1;
        }
        if (compress(filepath, ofname) != 0) {
            fprintf(stderr, "Compression failed\n");
            free(filepath);
            return 1;
        }
        free(filepath);
    } else if (choice == 2) {
        printf("Enter input filename: ");
        if (scanf("%s", ifname) != 1) {
            fprintf(stderr, "Error reading input filename\n");
            return 1;
        }
        filepath = find_file(ifname);
        if (filepath == NULL) {
            fprintf(stderr, "Input file does not exist\n");
            return 1;
        }
        printf("Enter output filename: ");
        if (scanf("%s", ofname) != 1) {
            fprintf(stderr, "Error reading output filename\n");
            free(filepath);
            return 1;
        }
        if (extract(filepath, ofname) != 0) {
            fprintf(stderr, "Decompression failed\n");
            free(filepath);
            return 1;
        }
        free(filepath);
    } else {
        fprintf(stderr, "Invalid choice\n");
        return 1;
    }

    return 0;
}
