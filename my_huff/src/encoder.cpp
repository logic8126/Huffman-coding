#include "encoder.h"

Encoder::Encoder()
{
	p = vector<vector<unsigned char>>(size);
	counter = vector<int>(size, 0);
	file_size = 0;
	leaf = vector<HuffmanTree*>(size);
}

bool Encoder::openFile(string source_file, string target_file)
{
	input.open(source_file,ios::binary);
	if (!input.is_open())
	{
		cout << "source file open failed ..." << endl;
		return false;
	}
	output.open(target_file, ios::binary);
	if (!output.is_open())
	{
		cout << "target file open failed ..." << endl;
		return false;
	}
	return true;
}

void Encoder::statistics()
{
		unsigned char buff;
		while (input >> noskipws >> buff)
		{
			counter.at(buff)++;
			file_size++;
		}
		cout << "the size of file is " << file_size << " byte"<<endl;
		input.clear();
		input.seekg(0, ios::beg);	
}
void Encoder::createTree()
{	
	for (int i = 0; i < size; ++i)
	{
		leaf.at(i) = new HuffmanTree;
		leaf.at(i)->weight = counter.at(i);
		leaf.at(i)->code = i;
		leaf.at(i)->data = i;
		leaf.at(i)->lchild = NULL;
		leaf.at(i)->rchild = NULL;
	}
	HuffmanTree* lnode;
	HuffmanTree* rnode;

	HuffmanTree *f;
	//f = new HuffmanTree[size];
	while (leaf.size() > 1)
	{
		f = new HuffmanTree;
		//从大到小排序，每次取最后两个
		sort(leaf.begin(), leaf.end(), [=](HuffmanTree* i1, HuffmanTree* i2) {
			return i1->weight > i2->weight;
			}); 
		lnode = leaf.back();
		leaf.pop_back();
		rnode = leaf.back();
		leaf.pop_back();

	
		f->lchild = lnode;
		lnode->code = 1; //左1右0
		f->rchild = rnode;
		rnode->code = 0;
		f->weight = rnode->weight + lnode->weight;
		f->code = 0;
		leaf.push_back(f);
		if (leaf.size() == 1)
		{
			tree_head = f;
			leaf.pop_back();
			return;
		}
		f++;
	}
	return ;
}



void Encoder::creatTable(HuffmanTree* node, vector<char> temp, int len)
{   

	if (node != NULL)
	{
		if (node->lchild == NULL && node->rchild == NULL)  
		{
			temp.at(len) = node->code;
			p.at(node->data).assign(temp.begin()+1, temp.begin()+len+1);
		}
		else
		{
			temp.at(len++) = node->code;
			creatTable(node->lchild, temp, len);
			creatTable(node->rchild, temp, len);
		}
	}
}

void Encoder::compress(string source_file, string target_file)
{
	vector<char> temp(size, 0);
	unsigned char buff;
	unsigned char out = 0;
	vector<char> code;

	openFile(source_file, target_file);
	statistics();
	createTree();
	creatTable(tree_head, temp, 0);

	for (vector<int>::iterator it = counter.begin(); it != counter.end(); ++it)
	{
		output << *it << endl;
	}//写入每个字符出现的次数，解压时根据这个构建Huffman树
	while (input >> noskipws >> buff)
	{
		code.insert(code.end(), p[buff].begin(), p[buff].end());
		while (code.size() >= 8)
		{
			out = 0;
			for (int j = 0; j < 8; ++j)
			{
				out = out ^ (code.at(j) << j);
			}
			output << out;

			vector<char>::const_iterator First = code.begin() + 8;
			vector<char>::const_iterator Second = code.end();
			code.assign(First, Second);

		}
	}
	if (code.size() != 0)
	{
		for (int j = 0; j < code.size(); ++j)
		{
			out = out ^ (code.at(j) << j);
		}
		output << out;
		output << code.size();
	}
	output.close();
	input.close();
	
}



Encoder::~Encoder()
{
	destroyTree(tree_head);
}

void Encoder::destroyTree(HuffmanTree* root)
{

	if (root == NULL )
	{
		return;
	}
	destroyTree(root->lchild);
	destroyTree(root->rchild);

	delete root;

	root = NULL;

}