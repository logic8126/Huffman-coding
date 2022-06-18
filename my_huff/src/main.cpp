#include"decoder.h"
#include"encoder.h"
//#include"vld.h"
int main()
{
	Encoder en;
	Decoder de;
	string source =R"(.\img\2.bmp)"; //目标文件
	string temp = R"(.\output\2.bin)"; //压缩后文件
	string target = R"(.\output\2.bmp)"; //解压后文件
	en.compress(source, temp);
	de.deCompress(temp, target);
	return 1;

}