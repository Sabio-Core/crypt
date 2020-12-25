#include<fstream>
#include<string>
#include<iostream>
#include<vector>

#pragma pack(push, 1)
struct Header
{
	uint32_t sig;
	size_t orig_size;
};
#pragma pack(pop)

void shifr(char** argv)
{
	std::ifstream bynaryFile;// �������� ������
	bynaryFile.open("BMP.bmp", std::ios::binary | std::ios::ate );//�������� ������ ��� ������
	std::ofstream out;
	out.open("container", std::ios::binary | std::ios::ate);

	bynaryFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);//������������ ����������
	auto size = bynaryFile.tellg();

	Header hdr{}; //���������� ���������
	hdr.sig = 0xdeadbeef;//���������� ����������
	hdr.orig_size = size;//���������� ����������

	bynaryFile.seekg(0);
	unsigned blocks = size/8;
	if(size%8) ++blocks;

	std::vector<uint64_t> data(blocks);
	data[blocks - 1] = 0;
	bynaryFile.read(reinterpret_cast<char*>(&data[0]), size);
	bynaryFile.close();
	out.write((char*)&hdr, sizeof(hdr));
	out.write((char*)&data[0], sizeof(uint64_t)*blocks);

	out.close();
}
void rasshifr(char** argv)
{
	std::ifstream bynaryFile;// �������� ������
	bynaryFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);//������������ ����������
	bynaryFile.open("container", std::ios::binary);//�������� ������ ��� ������
	std::ofstream out;
	out.open("output", std::ios::binary);

	Header hdr{}; //���������� ���������
	bynaryFile.read(reinterpret_cast <char*>(&hdr), sizeof(hdr));
	if(hdr.sig != 0xdeadbeef)
	{
		std::cout << "�������� ������ �����" << std::endl;
		exit(-1);
	}

	unsigned blocks = hdr.orig_size/8;
	if(hdr.orig_size%8) ++blocks;
	std::vector<uint64_t> data(blocks);
	bynaryFile.read(reinterpret_cast<char*>(&data[0]), sizeof(uint64_t)*blocks);
	bynaryFile.close();
	out.write(reinterpret_cast<char*>(&data[0]), sizeof(uint64_t)*blocks);
	out.close();

}

int main(int argc, char** argv)
{
	shifr(argv);
	rasshifr(argv);
	return 0;
}
