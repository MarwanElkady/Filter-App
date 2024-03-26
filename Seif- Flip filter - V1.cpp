#include <iostream>
#include "Image_Class.h"
using namespace std;

void flipHorizontal(Image& img) {
    int halfWidth = img.width / 2;
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < halfWidth; ++x) {
            for (int c = 0; c < img.channels; ++c) {
                swap(img(x, y, c), img(img.width - 1 - x, y, c));
            }
        }
    }
}

void flipVertical(Image& img) {
    int halfHeight = img.height / 2;
    for (int y = 0; y < halfHeight; ++y) {
        for (int x = 0; x < img.width; ++x) {
            for (int c = 0; c < img.channels; ++c) {
                swap(img(x, y, c), img(x, img.height - 1 - y, c));
            }
        }
    }
}

int main() {
    string filename;
    cout << "Enter the filename of the image: ";
    cin >> filename;
    Image img(filename);


    char choice;
    cout << "Do you want to flip the image horizontally (h) or vertically (v)? ";
    cin >> choice;


    if (choice == 'h') {
        flipHorizontal(img);
    } else if (choice == 'v') {
        flipVertical(img);
    } else {
        cout << "Invalid choice. Exiting..." << endl;
        return 1;
    }


    img.saveImage("flipped_image.jpg");

    cout << "Image flipped and saved successfully!" << endl;

    return 0;
}