#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>

using namespace std;

char decrypt_byte(const char orig, const char crypt) {   return crypt - orig;   }

std::string get_key(FILE* orig_file, FILE* crypt_file)
{
    size_t cnt1 = 0, cnt2 = 0;
    char orig_byte = 0, crypt_byte = 0;
    std::string key;

    while (1) {
        cnt1 = fread(&orig_byte, sizeof(char), 1, orig_file);
        cnt2 = fread(&crypt_byte, sizeof(char), 1, crypt_file);

        if (!(cnt1 && cnt2)) {
            break;
        }

        key += decrypt_byte(orig_byte, crypt_byte);
    }

    return key;
}

int main(int argc, char** argv)
{
    FILE* orig_file = fopen("description.txt", "rb");
    FILE* crypt_file = fopen("description.enc", "rb");
    
    if (!orig_file) {
        cout << "There is no original file" << endl;
        return 0;
    }
    
    if (!crypt_file) {
        cout << "There is no crypted file" << endl;
        return 0;
    }

    std::string key = get_key(orig_file, crypt_file);
    
    cout << "Key: " << key << endl;

    return 0;
}
