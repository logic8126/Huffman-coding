#pragma once
#ifndef DECODER_H
#define DECODER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "huffmantree.h"

using namespace std;
class Decoder
{
private:
	const int size = 256;
	int file_size;
	ifstream input;
	ofstream output;
	vector<int> counter;
	HuffmanTree* root;
	vector<HuffmanTree*> leaf;

	bool openFile(string source_file, string target_file);
	void statistics();// ͳ�Ƹ����ַ����ִ���,����������
	void createTree();// ����huffman��
	void destroyTree(HuffmanTree* root);
public:
	Decoder();
	void deCompress(string source_file,string target_file); // ѹ������
	~Decoder();

};






#endif