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
            cout << "7. Exit the application." << endl;
            ;
            cout << "Enter your choice (1, 2, 3, 4, 5, 6 or 7): ";
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
