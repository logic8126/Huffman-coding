#include"decoder.h"

Decoder::Decoder()
{
	counter = vector<int>(size, 0);
	file_size = 0;
}

bool Decoder::openFile(string source_file, string target_file)
{
	input.open(source_file,ios::binary);
	if (!input.is_open())
	{
		cout << "compressed file open failed ..." << endl;
		return false;
	}
	output.open(target_file,ios::binary);
	if (!output.is_open())
	{
		cout << "created file open failed ..." << endl;
		return false;
	}
	return true;
}

void Decoder::statistics()// 统计各个字符出现次数,并进行排序
{
	if (!input.is_open())
	{
		cout << "打开文件失败" << endl;
		return;
	}
	for (vector<int>::iterator it = counter.begin(); it != counter.end(); ++it)
	{
		input >> *it;
	}
}
void Decoder::createTree()// 生成huffman树
{

	leaf = vector<HuffmanTree*>(size);
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
	HuffmanTree* f;
	//f = new HuffmanTree[256];
	while (leaf.size() > 1)
	{
		f = new HuffmanTree;
		sort(leaf.begin(), leaf.end(), [=](HuffmanTree* i1, HuffmanTree* i2) {
			return i1->weight > i2->weight;
			});
		lnode = leaf.back();
		leaf.pop_back();
		rnode = leaf.back();
		leaf.pop_back();
		

		f->lchild = lnode;
		lnode->code = 1;
		f->rchild = rnode;
		rnode->code = 0;
		f->weight = rnode->weight + lnode->weight;
		f->code = 0;
		leaf.push_back(f);
		if (leaf.size() == 1)
		{
			root = f;
			return;
		}
		f++;
	}

}

void Decoder::deCompress(string sourece_file,string target_file) // 压缩编码
{
	HuffmanTree* p;
	unsigned char buff;
	int count = 0;
	int temp;
	openFile(sourece_file, target_file);
	statistics();
	createTree();

	p = root;
	for (vector<int>::iterator it = counter.begin(); it != counter.end(); ++it)
	{
		file_size += *it;
	}
	input >> noskipws >> buff;
	while (input >> noskipws >> buff)
	{
	
		for (int i = 0; i < 8; ++i)
		{

			if (!(p->lchild == NULL && p->rchild == NULL))
			{
				temp = (buff & (1 << i)) ? 1 : 0;
				//cout << temp;
				if (temp == 0)
				{
					p = p->rchild;
				}
				else
					p = p->lchild;
			}
			if (p->lchild == NULL && p->rchild == NULL)
			{
				output << p->data;
				p = root;
				count++;
				if (count == file_size)
				{
					cout << "decompress successfully";
					return;
				}
			}
		}
	}
	input.close();
	output.close();
}
Decoder::~Decoder()
{
	destroyTree(root);
}

void Decoder::destroyTree(HuffmanTree* root)
{

	if (root == NULL)
	{
		return;
	}
	destroyTree(root->lchild);
	destroyTree(root->rchild);
	delete  root;
	root = NULL;

}