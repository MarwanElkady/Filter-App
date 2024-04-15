#include <iostream>
#include "Image_Class.h"
using namespace std;

// Function to darken the image.
void darkenImage(Image& image) {
    int width = image.width;
    int height = image.height;
    int channels = image.channels;

    // Darken the image by reducing the intensity by 50%.
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            for (int k = 0; k < channels; ++k) {
                image(x, y, k) /= 2; // Divide by 2 to reduce the image's intensity by 50%.
            }
        }
    }
}

// Function to lighten the image.
void lightenImage(Image& image) {
    int width = image.width;
    int height = image.height;
    int channels = image.channels;

    // Lighten the image by increasing the intensity by 50%
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            for (int k = 0; k < channels; ++k) {
                image(x, y, k) += (255 - image(x, y, k)) / 2; // Increase intensity by half of the difference from maximum intensity
            }
        }
    }
}

int main (){
    string imageName;
    cout << "Please enter the name of your photo with the extension: ";
    cin >> imageName;
    Image image(imageName);

    char filterType;
    cout << "Enter 'D' to darken the image or 'L' to lighten it: ";
    cin >> filterType;

    if (filterType == 'D' || filterType == 'd') {
        darkenImage(image);
    } else if (filterType == 'L' || filterType == 'l') {
        lightenImage(image);
    } else {
        cout << "Invalid input. Please enter 'D' or 'L'." << endl;
        return 1;
    }

    cout << "Please enter the name of the new edited photo followed by the desired extension: ";
    cin >> imageName;
    image.saveImage(imageName); 

    return 0;
}
