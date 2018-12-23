#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

char decrypt_byte(const char crypt, const char key)  {   return crypt - key;  }

std::string DecryptFile(FILE *crypt_file, const std::string &key)
{
    char crypt_byte;
    int key_pos = 0;
    std::string secret;
    size_t cnt;

    while (1) {
        cnt = fread(&crypt_byte, sizeof(char), 1, crypt_file);
        if (!cnt)
            break;

        char key_byte = key[key_pos];
        secret += decrypt_byte(crypt_byte, key_byte);
        key_pos = (key_pos + 1) % key.length();
    }

    return secret;
}

int main(int argc, char** argv)
{
    FILE *crypt_file = fopen("task.enc", "rb");

    if (!crypt_file) {
        cout << "There is no source file" << endl;
        return 0;
    }

    std::string secret = DecryptFile(crypt_file, "807f62f298122c881355a4e67965063de9544d55.");
    
    cout << secret << endl;
    fclose(crypt_file);

    return 0;
}
