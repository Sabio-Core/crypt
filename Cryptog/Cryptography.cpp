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
	std::ifstream bynaryFile;// создание потока
	bynaryFile.open("BMP.bmp", std::ios::binary | std::ios::ate );//ќткрытие потока дл€ чтени€
	std::ofstream out;
	out.open("container", std::ios::binary | std::ios::ate);

	bynaryFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);//вылавливание исключений
	auto size = bynaryFile.tellg();

	Header hdr{}; //объ€вление структуры
	hdr.sig = 0xdeadbeef;//перезапись переменной
	hdr.orig_size = size;//перезапись переменной

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
	std::ifstream bynaryFile;// создание потока
	bynaryFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);//вылавливание исключений
	bynaryFile.open("container", std::ios::binary);//ќткрытие потока дл€ чтени€
	std::ofstream out;
	out.open("output", std::ios::binary);

	Header hdr{}; //объ€вление структуры
	bynaryFile.read(reinterpret_cast <char*>(&hdr), sizeof(hdr));
	if(hdr.sig != 0xdeadbeef)
	{
		std::cout << "Ќеверный формат файла" << std::endl;
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
