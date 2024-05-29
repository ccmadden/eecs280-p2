#include <fstream>
#include <iostream>

#include "processing.hpp"
using namespace std;
int main(int argc, char** argv) {
    string input_file = argv[1];
    string output_file = argv[2];
    ifstream ifs(input_file);
    ofstream ofs(output_file);
    Image* img = new Image;
    Image_init(img, ifs);
    int og_width = img->height;
    int og_height = img->height;
    if (!(ifs.is_open())) {
        cout << "Error opening file" << input_file << endl;
        return 1;
    }

    if (!(ofs.is_open())) {
        cout << "Error opening file" << output_file << endl;
        return 1;
    }

    if (argc == 5) {
        if (stoi(argv[3]) <= 0 || stoi(argv[4]) <= 0 || stoi(argv[3])
         > og_width ||stoi(argv[4]) > og_height) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
            return 1;
        }
        seam_carve(img, stoi(argv[3]), stoi(argv[4]));
    }
    if (argc == 4) {
        if (stoi(argv[3]) <= 0 || stoi(argv[3]) > og_width) {
       cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
            return 1;
        }
        seam_carve(img, stoi(argv[3]), og_height);

    }
    Image_print(img, ofs);
    delete img;
    return 0;
}