#pragma once
#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

struct  HuffmanTree
{
	HuffmanTree* lchild;
	HuffmanTree* rchild;
	int weight;  //出现次数
	unsigned char data;
	unsigned char code;  // 左1右0
};


#endif