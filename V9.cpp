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
using namespace std;
#include "Image_Class.h"

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
    cout << "ًWelcome to our baby photoshop app." << endl;
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
            cout << "10. Exite the app." << endl;

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
