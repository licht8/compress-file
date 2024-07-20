#include "huffman.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <errno.h>
#include <linux/limits.h>
#endif

void huf_select(HufNode* huf_tree, unsigned int n, int* s1, int* s2) {
    unsigned int i;
    unsigned long min1 = ULONG_MAX, min2 = ULONG_MAX;
    *s1 = *s2 = -1;

    for (i = 0; i < n; ++i) {
        if (huf_tree[i].parent == 0) {
            if (huf_tree[i].weight < min1) {
                min2 = min1;
                *s2 = *s1;
                min1 = huf_tree[i].weight;
                *s1 = i;
            } else if (huf_tree[i].weight < min2) {
                min2 = huf_tree[i].weight;
                *s2 = i;
            }
        }
    }
}

void CreateTree(HufNode* huf_tree, unsigned int char_kinds, unsigned int node_num) {
    unsigned int i;
    int s1, s2;
    for (i = char_kinds; i < node_num; ++i) {
        huf_select(huf_tree, i, &s1, &s2);
        huf_tree[s1].parent = huf_tree[s2].parent = i;
        huf_tree[i].lchild = s1;
        huf_tree[i].rchild = s2;
        huf_tree[i].weight = huf_tree[s1].weight + huf_tree[s2].weight;
    }
}

void HufCode(HufNode* huf_tree, unsigned int char_kinds) {
    unsigned int i;
    int cur, next, index;
    char code_tmp[257];
    code_tmp[256] = '\0';

    for (i = 0; i < char_kinds; ++i) {
        index = 256;
        for (cur = i, next = huf_tree[i].parent; next != 0;
             cur = next, next = huf_tree[next].parent)
            code_tmp[--index] = (huf_tree[next].lchild == cur) ? '0' : '1';
        huf_tree[i].code = strdup(&code_tmp[index]);
    }
}

int compress(const char* ifname, const char* ofname) {
    unsigned int i, j;
    unsigned int char_kinds;
    unsigned char char_temp;
    unsigned long file_len = 0;
    FILE* infile, * outfile;
    TmpNode node_temp;
    unsigned int node_num;
    HufNode* huf_tree;
    char code_buf[257] = {0};
    size_t code_len;

    clock_t start_time = clock();

    TmpNode tmp_nodes[256] = {0};

    for (i = 0; i < 256; ++i) {
        tmp_nodes[i].uch = (unsigned char)i;
    }

    infile = fopen(ifname, "rb");
    if (infile == NULL)
        return -1;

    while (fread(&char_temp, sizeof(unsigned char), 1, infile) == 1) {
        ++tmp_nodes[char_temp].weight;
        ++file_len;
    }
    fclose(infile);

    for (i = 0; i < 255; ++i)
        for (j = i + 1; j < 256; ++j)
            if (tmp_nodes[i].weight < tmp_nodes[j].weight) {
                node_temp = tmp_nodes[i];
                tmp_nodes[i] = tmp_nodes[j];
                tmp_nodes[j] = node_temp;
            }

    for (char_kinds = 0; char_kinds < 256 && tmp_nodes[char_kinds].weight > 0; ++char_kinds);

    outfile = fopen(ofname, "wb");
    if (outfile == NULL)
        return -1;

    fwrite(&char_kinds, sizeof(unsigned int), 1, outfile);

    if (char_kinds == 1) {
        fwrite(&tmp_nodes[0].uch, sizeof(unsigned char), 1, outfile);
        fwrite(&tmp_nodes[0].weight, sizeof(unsigned long), 1, outfile);
        fclose(outfile);
        return 0;
    }

    node_num = 2 * char_kinds - 1;
    huf_tree = (HufNode*)calloc(node_num, sizeof(HufNode));

    for (i = 0; i < char_kinds; ++i) {
        huf_tree[i].uch = tmp_nodes[i].uch;
        huf_tree[i].weight = tmp_nodes[i].weight;
    }

    CreateTree(huf_tree, char_kinds, node_num);
    HufCode(huf_tree, char_kinds);

    for (i = 0; i < char_kinds; ++i) {
        fwrite(&huf_tree[i].uch, sizeof(unsigned char), 1, outfile);
        fwrite(&huf_tree[i].weight, sizeof(unsigned long), 1, outfile);
    }

    fwrite(&file_len, sizeof(unsigned long), 1, outfile);

    infile = fopen(ifname, "rb");
    if (infile == NULL) {
        fclose(outfile);
        return -1;
    }

    while (fread(&char_temp, sizeof(unsigned char), 1, infile) == 1) {
        for (i = 0; i < char_kinds; ++i)
            if (char_temp == huf_tree[i].uch) {
                strcat(code_buf, huf_tree[i].code);
                break;
            }

        while (strlen(code_buf) >= 8) {
            char_temp = 0;
            for (i = 0; i < 8; ++i) {
                char_temp = (char_temp << 1) | (code_buf[i] == '1');
            }
            fwrite(&char_temp, sizeof(unsigned char), 1, outfile);
            memmove(code_buf, code_buf + 8, strlen(code_buf) - 7);
        }
    }

    if ((code_len = strlen(code_buf)) > 0) {
        char_temp = 0;
        for (i = 0; i < code_len; ++i) {
            char_temp = (char_temp << 1) | (code_buf[i] == '1');
        }
        char_temp <<= 8 - code_len;
        fwrite(&char_temp, sizeof(unsigned char), 1, outfile);
    }

    fclose(infile);
    fclose(outfile);

    for (i = 0; i < char_kinds; ++i)
        free(huf_tree[i].code);
    free(huf_tree);

    printf("Compression time: %.4f seconds\n", ((double)(clock() - start_time)) / CLOCKS_PER_SEC);

    return 0;
}

int extract(const char* ifname, const char* ofname) {
    unsigned int i;
    unsigned long file_len;
    unsigned long writen_len = 0;
    FILE* infile, * outfile;
    unsigned int char_kinds;
    unsigned int node_num;
    HufNode* huf_tree;
    unsigned char code_temp;
    unsigned int root;

    clock_t start_time = clock();

    infile = fopen(ifname, "rb");
    if (infile == NULL)
        return -1;

    if (fread(&char_kinds, sizeof(unsigned int), 1, infile) != 1) {
        fclose(infile);
        return -1;
    }

    if (char_kinds == 1) {
        if (fread(&code_temp, sizeof(unsigned char), 1, infile) != 1 || 
            fread(&file_len, sizeof(unsigned long), 1, infile) != 1) {
            fclose(infile);
            return -1;
        }

        outfile = fopen(ofname, "wb");
        if (outfile == NULL) {
            fclose(infile);
            return -1;
        }

        for (i = 0; i < file_len; ++i)
            fwrite(&code_temp, sizeof(unsigned char), 1, outfile);

        fclose(infile);
        fclose(outfile);
        return 0;
    } else {
        node_num = 2 * char_kinds - 1;
        huf_tree = (HufNode*)calloc(node_num, sizeof(HufNode));

        for (i = 0; i < char_kinds; ++i) {
            if (fread(&huf_tree[i].uch, sizeof(unsigned char), 1, infile) != 1 || 
                fread(&huf_tree[i].weight, sizeof(unsigned long), 1, infile) != 1) {
                free(huf_tree);
                fclose(infile);
                return -1;
            }
        }

        CreateTree(huf_tree, char_kinds, node_num);

        if (fread(&file_len, sizeof(unsigned long), 1, infile) != 1) {
            free(huf_tree);
            fclose(infile);
            return -1;
        }

        outfile = fopen(ofname, "wb");
        if (outfile == NULL) {
            fclose(infile);
            free(huf_tree);
            return -1;
        }
        root = node_num - 1;

        while (writen_len < file_len) {
            if (fread(&code_temp, sizeof(unsigned char), 1, infile) != 1) {
                free(huf_tree);
                fclose(infile);
                fclose(outfile);
                return -1;
            }
            for (i = 0; i < 8 && writen_len < file_len; ++i) {
                root = (code_temp & 0x80) ? huf_tree[root].rchild : huf_tree[root].lchild;
                if (root < char_kinds) {
                    fwrite(&huf_tree[root].uch, sizeof(unsigned char), 1, outfile);
                    root = node_num - 1;
                    ++writen_len;
                }
                code_temp <<= 1;
            }
        }

        free(huf_tree);
        fclose(infile);
        fclose(outfile);
    }

    printf("Decompression time: %.4f seconds\n", ((double)(clock() - start_time)) / CLOCKS_PER_SEC);

    return 0;
}

char* find_file(const char* filename) {
    char* filepath = (char*)malloc(PATH_MAX);
    if (filepath == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return NULL;
    }
    filepath[0] = '\0';

#ifdef _WIN32
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(filename, &findFileData);
    if (hFind != INVALID_HANDLE_VALUE) {
        GetFullPathName(findFileData.cFileName, PATH_MAX, filepath, NULL);
        FindClose(hFind);
    }
#else
    char command[PATH_MAX + 32];
    snprintf(command, sizeof(command), "find / -name %s 2>/dev/null", filename);
    FILE* pipe = popen(command, "r");
    if (pipe == NULL) {
        fprintf(stderr, "Error executing find command\n");
        free(filepath);
        return NULL;
    }
    fgets(filepath, PATH_MAX, pipe);
    pclose(pipe);

    if (filepath[0] != '\0') {
        filepath[strcspn(filepath, "\n")] = '\0'; // Remove newline character
    } else {
        free(filepath);
        return NULL;
    }
#endif

    return filepath;
}
