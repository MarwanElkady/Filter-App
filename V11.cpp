/*
File Name:CS112_A3_Part1_S1_20230187_20230361_20230378.cpp
Marwan IBraheem Isamel - 20230378 - did the menu and the invert image filter and handeled the code writing.
Seif wael naem : 20230187 - did the flip image filter and grayscaled filter
mohamed waleed osama : 20230361 - did the black and white and detect image filter
*/

// including the required headers
#include <iostream>
#include <string>
#include <cmath> // Include cmath for mathematical operations
#include "Image_Class.h"
#include <map>
#include <array>
#include <algorithm>
#include <algorithm> // Include for case-insensitive comparison
#include <cctype>    // Include for character classification functions
using namespace std;

// Function to trim leading and trailing spaces from a string
std::string trim(const std::string &str)
{
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    if (start == std::string::npos || end == std::string::npos)
        return "";
    return str.substr(start, end - start + 1);
}

// Function to apply frame filter to the image
void applyFrameFilter(Image &img)
{
    try
    {
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
            {"brown", {165, 42, 42}}};

        // Get frame color from the user
        std::string frameColorName;
        std::cout << "Enter frame color (red, green, blue, yellow, white, black, cyan, magenta, orange, purple, pink, brown): ";
        std::cin.ignore(); // Ignore newline character from previous input
        std::getline(std::cin, frameColorName);

        // Trim leading and trailing spaces from the input color name
        frameColorName = trim(frameColorName);

        // Convert entered color name to lowercase for case-insensitive comparison
        std::transform(frameColorName.begin(), frameColorName.end(), frameColorName.begin(), ::tolower);

        // Check if the entered color name exists in the presets
        if (colorPresets.find(frameColorName) == colorPresets.end())
        {
            throw std::invalid_argument("Invalid color name. Please enter one of the following: red, green, blue, yellow, white, black, cyan, magenta, orange, purple, pink, brown.");
        }

        std::array<int, 3> frameColor = colorPresets[frameColorName];

        // Ask user for frame style
        std::string frameStyle;
        std::cout << "Enter frame style (solid, checkerboard): ";
        std::cin >> frameStyle;

        // Create a new image with frame
        int newWidth = img.width + 2 * frameWidth;
        int newHeight = img.height + 2 * frameWidth;
        Image framedImage(newWidth, newHeight);

        // Add frame to the image
        for (int y = 0; y < newHeight; y++)
        {
            for (int x = 0; x < newWidth; x++)
            {
                if (x < frameWidth || x >= newWidth - frameWidth || y < frameWidth || y >= newHeight - frameWidth)
                {
                    // Frame region
                    if (frameStyle == "solid")
                    {
                        for (int c = 0; c < 3; c++)
                        {
                            framedImage.setPixel(x, y, c, frameColor[c]);
                        }
                    }
                    else if (frameStyle == "checkerboard")
                    {
                        // Create a checkerboard pattern
                        bool isCheckerboardSquare = ((x / 30) % 2) == ((y / 30) % 2);
                        for (int c = 0; c < 3; c++)
                        {
                            framedImage.setPixel(x, y, c, isCheckerboardSquare ? frameColor[c] : 255 - frameColor[c]);
                        }
                    }
                    else
                    {
                        throw std::invalid_argument("Invalid frame style. Please enter one of the following: solid, checkerboard.");
                    }
                }
                else
                {
                    // Image region
                    for (int c = 0; c < 3; c++)
                    {
                        framedImage.setPixel(x, y, c, img.getPixel(x - frameWidth, y - frameWidth, c));
                    }
                }
            }
        }

        // Replace the original image with the framed image
        img = framedImage;

        std::cout << "Frame filter applied successfully." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Function to resize the image
void resizeImage(Image &img)
{
    try
    {
        // Get new dimensions from the user
        int newWidth, newHeight;
        cout << "Enter new width: ";
        cin >> newWidth;
        cout << "Enter new height: ";
        cin >> newHeight;

        // Create a new image for the resized result
        Image resizedImage(newWidth, newHeight);

        // Calculate the scaling factors
        float scaleX = (float)img.width / newWidth;
        float scaleY = (float)img.height / newHeight;

        // Resize the image using nearest-neighbor interpolation
        for (int y = 0; y < newHeight; ++y)
        {
            for (int x = 0; x < newWidth; ++x)
            {
                for (int c = 0; c < img.channels; ++c)
                {
                    // Sample the original image at scaled coordinates
                    int sampleX = int(x * scaleX);
                    int sampleY = int(y * scaleY);

                    // Set the pixel value in the resized image
                    resizedImage.setPixel(x, y, c, img.getPixel(sampleX, sampleY, c));
                }
            }
        }

        // Replace the original image with the resized image
        img = resizedImage;

        cout << "Image resized successfully." << endl;
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}

// Function to lighten of darken the image
void adjustBrightness(Image &img)
{
    try
    {
        // Prompt the user to choose to darken or lighten the image
        char choice;
        cout << "Do you want to darken (D) or lighten (L) the image? ";
        cin >> choice;

        // Create a new image for the filtered result
        Image filteredImage(img.width, img.height);

        // Apply the filter by adjusting each pixel's RGB values
        for (int y = 0; y < img.height; ++y)
        {
            for (int x = 0; x < img.width; ++x)
            {
                for (int c = 0; c < img.channels; ++c)
                {
                    // Get the original pixel value
                    unsigned char pixelValue = img.getPixel(x, y, c);

                    // Adjust the pixel value based on user choice
                    if (choice == 'D' || choice == 'd')
                    {
                        // Darken the pixel value by 50%
                        int adjustedValue = pixelValue / 1.5;
                        filteredImage.setPixel(x, y, c, adjustedValue);
                    }
                    else if (choice == 'L' || choice == 'l')
                    {
                        // Lighten the pixel value by 50%
                        int adjustedValue = pixelValue * 1.5;
                        if (adjustedValue > 255)
                            adjustedValue = 255; // Ensure the value doesn't exceed 255
                        filteredImage.setPixel(x, y, c, adjustedValue);
                    }
                    else
                    {
                        throw invalid_argument("Invalid choice. Please enter 'D' or 'L'.");
                    }
                }
            }
        }

        // Replace the original image with the filtered image
        img = filteredImage;

        cout << "Brightness adjusted successfully." << endl;
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}

// Function to crop the image
void cropImage(Image &img)
{
    try
    {
        // Get cropping dimensions from the user
        int x, y, width, height;
        cout << "Enter x-coordinate of the starting point (top-left corner): ";
        cin >> x;
        cout << "Enter y-coordinate of the starting point (top-left corner): ";
        cin >> y;
        cout << "Enter width of the area to crop: ";
        cin >> width;
        cout << "Enter height of the area to crop: ";
        cin >> height;

        // Verify dimensions are within bounds
        if (x < 0 || y < 0 || width <= 0 || height <= 0 || x + width > img.width || y + height > img.height)
        {
            throw invalid_argument("Invalid cropping dimensions or starting point.");
        }

        // Create a new image for the cropped area
        Image croppedImage(width, height);

        // Copy pixels from the original image to the cropped image
        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                for (int c = 0; c < img.channels; c++)
                {
                    croppedImage.setPixel(i, j, c, img.getPixel(x + i, y + j, c));
                }
            }
        }

        // Replace the original image with the cropped image
        img = croppedImage;

        cout << "Image cropped successfully." << endl;
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}

void rotateImage(Image &img, int angle)
{
    int newWidth, newHeight;
    if (angle == 90 || angle == 270)
    {
        // Swap width and height for 90° or 270° rotation
        newWidth = img.height;
        newHeight = img.width;
    }
    else
    {
        // Keep width and height the same for 180° rotation
        newWidth = img.width;
        newHeight = img.height;
    }

    // Create a new image with the rotated dimensions
    Image rotatedImage(newWidth, newHeight); // Removed img.channels parameter

    // Copy pixels from the original image to the rotated image according to the chosen angle
    for (int y = 0; y < img.height; ++y)
    {
        for (int x = 0; x < img.width; ++x)
        {
            int newX, newY;
            if (angle == 90)
            {
                newX = y;
                newY = img.width - 1 - x;
            }
            else if (angle == 180)
            {
                newX = img.width - 1 - x;
                newY = img.height - 1 - y;
            }
            else if (angle == 270)
            {
                newX = img.height - 1 - y;
                newY = x;
            }
            for (int c = 0; c < img.channels; ++c)
            {
                rotatedImage(newX, newY, c) = img(x, y, c);
            }
        }
    }

    // Replace the original image with the rotated image
    img = rotatedImage;
}

// Function to flip the image horizontally
void flipHorizontal(Image &img)
{
    int halfWidth = img.width / 2;
    for (int y = 0; y < img.height; ++y)
    {
        for (int x = 0; x < halfWidth; ++x)
        {
            for (int c = 0; c < img.channels; ++c)
            {
                swap(img(x, y, c), img(img.width - 1 - x, y, c));
            }
        }
    }
}

// Function to flip the image vertically
void flipVertical(Image &img)
{
    int halfHeight = img.height / 2;
    for (int y = 0; y < halfHeight; ++y)
    {
        for (int x = 0; x < img.width; ++x)
        {
            for (int c = 0; c < img.channels; ++c)
            {
                swap(img(x, y, c), img(x, img.height - 1 - y, c));
            }
        }
    }
}

// Main function of the application
int main()
{
    string filename;
    cout << "***********************************" << endl;
    cout << "Welcome to our baby photoshop app." << endl;
    cout << "***********************************" << endl;

    while (true)
    {
        cout << "Please enter the photo Name : ";
        cin >> filename;

        Image image(filename);

        int choice;

        // Loop for continuous editing until the user chooses to exit
        while (true)
        {
            cout << "Choose filter type:" << endl;
            cout << "1. Grayscale." << endl;
            cout << "2. Black and White." << endl;
            cout << "3. Image Invert." << endl;
            cout << "4. Flip Filter." << endl;
            cout << "5. Detect Image Edges." << endl;
            cout << "6. Save the pic with another extension." << endl;
            cout << "7. Rotate image" << endl;
            cout << "8. crop image." << endl;
            cout << "9. Darken and lighten image filter." << endl;
            cout << "10. Resize image filter." << endl;
            cout << "11. Frame filter." << endl;
            cout << "12. Exite the app." << endl;

            ;
            cout << "Enter your choice (1, 2, 3, 4, 5, 6 , 7 , 8 or 9): ";
            cin >> choice;

            if (choice == 1)
            {
                // Convert to grayscale
                for (int i = 0; i < image.width; ++i)
                {
                    for (int j = 0; j < image.height; ++j)
                    {
                        unsigned int avg = 0;
                        for (int k = 0; k < image.channels; ++k)
                        {
                            avg += image(i, j, k);
                        }
                        avg = avg / 3;
                        for (int k = 0; k < image.channels; ++k)
                        {
                            image(i, j, k) = avg;
                        }
                    }
                }
                cout << "Grayscale filter applied." << endl;
            }

            else if (choice == 2)
            {
                // Convert to Black and White
                for (int i = 0; i < image.width; ++i)
                {
                    for (int j = 0; j < image.height; ++j)
                    {
                        unsigned int avg = 0;
                        for (int k = 0; k < image.channels; ++k)
                        {
                            avg += image(i, j, k);
                        }
                        avg = avg / 3;
                        unsigned char newValue = (avg < 128) ? 0 : 255;
                        for (int k = 0; k < image.channels; ++k)
                        {
                            image(i, j, k) = newValue;
                        }
                    }
                }
                cout << "Black and White filter applied." << endl;
            }

            else if (choice == 3)
            {
                // Invert the image
                for (int i = 0; i < image.width; ++i)
                {
                    for (int j = 0; j < image.height; ++j)
                    {
                        for (int k = 0; k < image.channels; ++k)
                        {
                            image(i, j, k) = 255 - image(i, j, k);
                        }
                    }
                }
                cout << "Image Invert filter applied." << endl;
            }

            else if (choice == 4)
            {
                // Flip the image
                char choicefilter4;
                cout << "Do you want to flip the image horizontally (h) or vertically (v)? ";
                cin >> choicefilter4;
                if (choicefilter4 == 'h')
                {
                    flipHorizontal(image);
                }
                else if (choicefilter4 == 'v')
                {
                    flipVertical(image);
                }
                else
                {
                    cout << "Invalid choice. Exiting..." << endl;
                    return 1;
                }
                cout << "Image flipped." << endl;
            }

            else if (choice == 5)
            {
                // Detect Image Edges
                cout << "Detect Image Edges filter applied." << endl;
                // Add code to detect edges here
            }

            else if (choice == 6)
            {
                // Save the image with another extension
                cout << "Please enter the name for the output image: ";
                cin >> filename;
                image.saveImage(filename);
                cout << "Image saved successfully." << endl;
            }

            else if (choice == 7)
            {
                // Rotate image int angle;
                int angle;
                cout << "Enter the rotation angle (90, 180, or 270): ";
                cin >> angle;

                rotateImage(image, angle);
                cout << "Image rotated." << endl;
            }

            else if (choice == 8)
            {
                cropImage(image);
            }

            else if (choice == 9)
            {
                adjustBrightness(image);
            }

            else if (choice == 10)
            {
                resizeImage(image);
            }

            else if (choice == 11)
            {
                applyFrameFilter(image);
            }

            else if (choice == 12)
            {
                // Exit the application
                cout << "Exiting the application. Goodbye ya user!" << endl;
                break; // Exit the loop and choose another photo
            }

            else
            {
                cout << "Invalid choice. Please enter a valid option." << endl;
            }
        }
    }

    return 0;
}