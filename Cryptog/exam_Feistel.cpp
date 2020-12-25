#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

char function(char subblock, unsigned key)
{
    return (subblock + 1) ^ key; // ôóíêöèÿ
}

void decrypt(string &mes, unsigned key[], int n)
{
    char temp = '0', l = '0', r = '0';
    for (int desc = 0; desc < mes.size(); desc += 2) // ðàññìàòðèâàåì áëîêè ïî 2 ñèìâîëà
    {
        l = mes[desc];
        r = mes[desc + 1];
        for (int i = n-1; i >= 0; --i)  // n ðàóíäîâ
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
    for (int desc = 0; desc < mes.size(); desc += 2) // ðàññìàòðèâàåì áëîêè ïî 2 ñèìâîëà
    {
        l = mes[desc + 1];
        std::cout<<"Left subblock:\t"<< l<<std::endl;
        r = mes[desc];
        std::cout<<"Right subblock:\t"<< r <<std::endl;
        for (int i = 0; i < n; ++i) // n ðàóíäîâ
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
    string block = "TEST"; //Èñõîäíîå ñîîáùåíèå

    unsigned key [] = {0x0d, 0xf0, 0xfe, 0xca};// Êëþ÷

    std::cout << "Message\t" << block << std::endl;
    encrypt(block, key, block.length());
    std::cout << "Encrypted\t" << block << std::endl;
    decrypt(block, key, block.length());
    std::cout << "Decrypted\t" << block << std::endl;
    return 0;
}
