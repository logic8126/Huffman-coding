#include"decoder.h"
#include"encoder.h"
//#include"vld.h"
int main()
{
	Encoder en;
	Decoder de;
	string source =R"(.\img\home.bmp)"; //目标文件
	string temp = R"(.\output\home.bin)"; //压缩后文件
	string target = R"(.\output\home.bmp)"; //解压后文件
	en.compress(source, temp);
	de.deCompress(temp, target);
	return 1;

}