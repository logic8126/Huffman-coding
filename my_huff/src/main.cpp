#include"decoder.h"
#include"encoder.h"
//#include"vld.h"
int main()
{
	Encoder en;
	Decoder de;
	string source =R"(.\img\2.bmp)"; //Ŀ���ļ�
	string temp = R"(.\output\2.bin)"; //ѹ�����ļ�
	string target = R"(.\output\2.bmp)"; //��ѹ���ļ�
	en.compress(source, temp);
	de.deCompress(temp, target);
	return 1;

}