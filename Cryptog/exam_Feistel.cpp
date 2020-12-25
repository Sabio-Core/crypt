#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

char function(char subblock, unsigned key)
{
    return (subblock + 1) ^ key; // функция
    //(subblock * key[round]) % static_cast<char>(pow(2, round)+1)
}

void decrypt(string &mes, unsigned key[], int n)
{
    char temp = '0', l = '0', r = '0';
    for (int desc = 0; desc < mes.size(); desc += 2) // рассматриваем блоки по 2 символа
    {
        l = mes[desc];
        r = mes[desc + 1];
        for (int i = n-1; i >= 0; --i)  // n раундов
        {
            temp = l ^ function(r, key[i]);
            l = r;
            r = temp;
        }
        mes[desc+1] = l;
        mes[desc] = r;
    }
}

void encrypt(string &mes, unsigned key[], int n)
{
    char temp = '0', l = '0', r = '0';
    for (int desc = 0; desc < mes.size(); desc += 2) // рассматриваем блоки по 2 символа
    {
        l = mes[desc + 1];
        std::cout<<"Левый подблок: "<< l<<std::endl;
        r = mes[desc];
        std::cout<<"Правый подблок: "<< r <<std::endl;
        for (int i = 0; i < n; ++i) // n раундов
        {
            temp = r ^ function(l, key[i]);
            r = l;
            l = temp;
        }
        mes[desc] = l;
        mes[desc + 1] = r;
    }
}

int main(int arc, char** argv) {
    string block = "TEST"; //Исходное сообщение

    unsigned key [] = {0x0d, 0xf0, 0xfe, 0xca};// Ключ

    std::cout << "Сообщение\t" << block << std::endl;
    encrypt(block, key, block.length());
    std::cout << "Защифровано\t" << block << std::endl;
    decrypt(block, key, block.length());
    std::cout << "Расшифровано\t" << block << std::endl;
    return 0;
}
