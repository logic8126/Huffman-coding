#include"decoder.h"
#include"encoder.h"
//#include"vld.h"
int main()
{
	Encoder en;
	Decoder de;
	string source =R"(.\img\home.bmp)"; //Ŀ���ļ�
	string temp = R"(.\output\home.bin)"; //ѹ�����ļ�
	string target = R"(.\output\home.bmp)"; //��ѹ���ļ�
	en.compress(source, temp);
	de.deCompress(temp, target);
	return 1;

}