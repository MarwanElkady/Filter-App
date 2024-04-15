#include <iostream>
#include "Image_Class.h"

using namespace std;

int main() {
    try {
        // Load the original image
        string filename;
        cout << "Enter filename of the original image: ";
        cin >> filename;
        Image originalImage(filename);

        // Get new dimensions from the user
        int newWidth, newHeight;
        cout << "Enter new width: ";
        cin >> newWidth;
        cout << "Enter new height: ";
        cin >> newHeight;

        // Create a new image for the resized result
        Image resizedImage(newWidth, newHeight);

        // Calculate the scaling factors
        float scaleX = (float)originalImage.width / newWidth;
        float scaleY = (float)originalImage.height / newHeight;

        // Resize the image using nearest-neighbor interpolation
        for (int y = 0; y < newHeight; ++y) {
            for (int x = 0; x < newWidth; ++x) {
                for (int c = 0; c < 3; ++c) {
                    // Sample the original image at scaled coordinates
                    int sampleX = int(x * scaleX);
                    int sampleY = int(y * scaleY);

                    // Set the pixel value in the resized image
                    resizedImage.setPixel(x, y, c, originalImage.getPixel(sampleX, sampleY, c));
                }
            }
        }

        // Save the resized image
        string outputFilename;
        cout << "Enter filename for the resized image: ";
        cin >> outputFilename;
        resizedImage.saveImage(outputFilename);
        cout << "Resized image saved as " << outputFilename << endl;

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
