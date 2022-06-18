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
	vector<vector<unsigned char>> p; // ���
	HuffmanTree* tree_head;
	int file_size;



	bool openFile(string source_file, string target_file);
	void statistics();// ͳ�Ƹ����ַ����ִ���,����������
	void createTree();// ����huffman��
	void destroyTree(HuffmanTree* root);
	void creatTable(HuffmanTree* node, vector<char> temp, int len);
	
public:
	Encoder();
	void compress(string source_file, string target_file); // ѹ������
	~Encoder();

};




#endif