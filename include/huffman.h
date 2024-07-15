#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

typedef struct {
    unsigned char uch;
    unsigned long weight;
} TmpNode;

typedef struct HufNode {
    unsigned char uch;
    unsigned long weight;
    char* code;
    int parent, lchild, rchild;
} HufNode;

void huf_select(HufNode* huf_tree, unsigned int n, int* s1, int* s2);
void CreateTree(HufNode* huf_tree, unsigned int char_kinds, unsigned int node_num);
void HufCode(HufNode* huf_tree, unsigned int char_kinds);
int compress(const char* ifname, const char* ofname);
int extract(const char* ifname, const char* ofname);

#endif /* HUFFMAN_H */
