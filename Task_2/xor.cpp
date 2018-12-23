#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>

using namespace std;

std::string do_and_img(FILE* img1, FILE* img2)
{
    size_t cnt1 = 0, cnt2 = 0;
    std::string secret;

    while (1) {
        char img1_bytes, img2_bytes;

        cnt1 = fread(&img1_bytes, sizeof(char), 1, img1);
        cnt2 = fread(&img2_bytes, sizeof(char), 1, img2);

        if (!(cnt1 && cnt2)) {
            break;
        }

        secret += img1_bytes & img2_bytes;
    }

    return secret;
}

std::string do_xor_img(FILE* img1, FILE* img2)
{
    size_t cnt1 = 0, cnt2 = 0;
    std::string secret;

    while (1) {
        char img1_bytes, img2_bytes;

        cnt1 = fread(&img1_bytes, sizeof(char), 1, img1);
        cnt2 = fread(&img2_bytes, sizeof(char), 1, img2);

        if (!(cnt1 && cnt2)) {
            break;
        }

        secret += img1_bytes ^ img2_bytes;
    }

    return secret;
}

int main(int argc, char *argv[])
{
    FILE* img1 = fopen("image_489x488.enc", "rb");
    FILE* img2 = fopen("secret_489x488.enc", "rb");
    
    if (!img1) {
        cout << "f1 is not specified" << endl;
        return 1;
    }

    if (!img2) {
        cout << "f2 is not specified" << endl;
        return 1;
    }

    std::string xored = do_xor_img(img1, img2);

    ofstream outfile;
    outfile.open ("output_489x488.raw");
    outfile << xored << endl;
    outfile.close();

    fclose(img1);
    fclose(img2);

    return 0;
}
