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

        // Prompt the user to choose to darken or lighten the image
        char choice;
        cout << "Do you want to darken (D) or lighten (L) the image? ";
        cin >> choice;

        // Create a new image for the filtered result
        Image filteredImage(originalImage.width, originalImage.height);

        // Apply the filter by adjusting each pixel's RGB values
        for (int y = 0; y < originalImage.height; ++y) {
            for (int x = 0; x < originalImage.width; ++x) {
                for (int c = 0; c < 3; ++c) {
                    // Get the original pixel value
                    unsigned char pixelValue = originalImage.getPixel(x, y, c);

                    // Adjust the pixel value based on user choice
                    if (choice == 'D' || choice == 'd') {
                        // Darken the pixel value by 50%
                        int adjustedValue = pixelValue / 1.5;
                        filteredImage.setPixel(x, y, c, adjustedValue);
                    } else if (choice == 'L' || choice == 'l') {
                        // Lighten the pixel value by 50%
                        int adjustedValue = pixelValue * 1.5;
                        if (adjustedValue > 255) adjustedValue = 255; // Ensure the value doesn't exceed 255
                        filteredImage.setPixel(x, y, c, adjustedValue);
                    } else {
                        throw invalid_argument("Invalid choice. Please enter 'D' or 'L'.");
                    }
                }
            }
        }

        // Save the filtered image
        string outputFilename;
        cout << "Enter filename for the filtered image: ";
        cin >> outputFilename;
        filteredImage.saveImage(outputFilename);
        cout << "Filtered image saved as " << outputFilename << endl;

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
