#pragma once
#ifndef ENCODER_H
#define ENCODER_H

#include"huffmantree.h"
#include<vector>
#include<fstream>
#include<iostream>
#include <algorithm>
using namespace std;


class Encoder 
{
private :
    const int size = 256;
	vector<int> counter;
	ifstream input;
	ofstream output;
	vector<HuffmanTree*> leaf;
	vector<vector<unsigned char>> p; // 码表
	HuffmanTree* tree_head;
	int file_size;



	bool openFile(string source_file, string target_file);
	void statistics();// 统计各个字符出现次数,并进行排序
	void createTree();// 生成huffman树
	void destroyTree(HuffmanTree* root);
	void creatTable(HuffmanTree* node, vector<char> temp, int len);
	
public:
	Encoder();
	void compress(string source_file, string target_file); // 压缩编码
	~Encoder();

};




#endif