#pragma once
#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

struct  HuffmanTree
{
	HuffmanTree* lchild;
	HuffmanTree* rchild;
	int weight;  //���ִ���
	unsigned char data;
	unsigned char code;  // ��1��0
};


#endif