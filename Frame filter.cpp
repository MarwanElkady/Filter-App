#include <iostream>
#include "Image_Class.h"
#include <map>
#include <array>

int main() {
    try {
        // Load the image
        std::string filename;
        std::cout << "Enter filename of the image: ";
        std::cin >> filename;
        Image image(filename);

        // Get frame width from the user
        int frameWidth;
        std::cout << "Enter frame width: ";
        std::cin >> frameWidth;

        // Define color presets
        std::map<std::string, std::array<int, 3>> colorPresets = {
            {"red", {255, 0, 0}},
            {"green", {0, 255, 0}},
            {"blue", {0, 0, 255}},
            {"yellow", {255, 255, 0}},
            {"white", {255, 255, 255}},
            {"black", {0, 0, 0}},
            {"cyan", {0, 255, 255}},
            {"magenta", {255, 0, 255}},
            {"orange", {255, 165, 0}},
            {"purple", {128, 0, 128}},
            {"pink", {255, 192, 203}},
            {"brown", {165, 42, 42}}
        };

        // Get frame color from the user
        std::string frameColorName;
        std::cout << "Enter frame color (red, green, blue, yellow, white, black, cyan, magenta, orange, purple, pink, brown): ";
        std::cin >> frameColorName;

        if (colorPresets.find(frameColorName) == colorPresets.end()) {
            throw std::invalid_argument("Invalid color name. Please enter one of the following: red, green, blue, yellow, white, black, cyan, magenta, orange, purple, pink, brown.");
        }

        std::array<int, 3> frameColor = colorPresets[frameColorName];

        // Ask user for frame style
        std::string frameStyle;
        std::cout << "Enter frame style (solid, checkerboard): ";
        std::cin >> frameStyle;

        // Create a new image with frame
        int newWidth = image.width + 2 * frameWidth;
        int newHeight = image.height + 2 * frameWidth;
        Image framedImage(newWidth, newHeight);

        // Add frame to the image
        for (int y = 0; y < newHeight; y++) {
            for (int x = 0; x < newWidth; x++) {
                if (x < frameWidth || x >= newWidth - frameWidth || y < frameWidth || y >= newHeight - frameWidth) {
                    // Frame region
                    if (frameStyle == "solid") {
                        for (int c = 0; c < 3; c++) {
                            framedImage.setPixel(x, y, c, frameColor[c]);
                        }
                    } else if (frameStyle == "checkerboard") {
                        // Create a checkerboard pattern
                        bool isCheckerboardSquare = ((x / 30) % 2) == ((y / 30) % 2);
                        for (int c = 0; c < 3; c++) {
                            framedImage.setPixel(x, y, c, isCheckerboardSquare ? frameColor[c] : 255 - frameColor[c]);
                        }
                    } else {
                        throw std::invalid_argument("Invalid frame style. Please enter one of the following: solid, checkerboard.");
                    }
                } else {
                    // Image region
                    for (int c = 0; c < 3; c++) {
                        framedImage.setPixel(x, y, c, image.getPixel(x - frameWidth, y - frameWidth, c));
                    }
                }
            }
        }

        // Save the framed image
        std::string outputFilename = "framed_image.png"; // Output filename
        framedImage.saveImage(outputFilename);
        std::cout << "Framed image saved as " << outputFilename << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
