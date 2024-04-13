

// including the requierd headers
#include <iostream>
#include <string>
using namespace std;
#include "Image_Class.h"

// this function is for fliping the image horizontal in filter 4
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

// this function  is used to flip the image vertical in filter 4
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

// the main function of the app
int main()
{
    /*
    welcoming the user in our app
    make a var to store the name of the image file
    save the photo name in the var filename.
    */
    string filename;
    cout << "***********************************" << endl;
    cout << "ًWelcome to our baby photoshop app." << endl;
    cout << "***********************************" << endl;
    cout << "Please enter the photo Name : ";
    cin >> filename;

    // this line responisable to open the photo
    Image image(filename);

    /*
    this punch of code is responsible for saveing the choice of wich filter the user needs.
    */
    int choice;
    cout << "Choose filter type:" << endl;
    cout << "1. Grayscale." << endl;
    cout << "2. Black and White." << endl;
    cout << "3. image invert." << endl;
    cout << "4. flip filter." << endl;
    cout << "5. Detect Image Edges" << endl;
    cout << "6. save the pic with another extention. " << endl;
    cout << "Enter your choice (1 , 2 , 3 , 4 , 5 or 6): ";
    cin >> choice;

    /*
    Convert to grayscale.
    iterate over each pixel in the image and calculate the average intensity.
    assign this average intensity to each channel of the pixel.
    effectively converting the pixel to grayscale.
    summ all channels of each pixels then dividing it by the number of the channels(3)
    they are 3 for the RGB colores , then assign the average value to all channels.
    */
    if (choice == 1)
    {
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
        // this lines is responsiable for saving the new image after edited.
        cout << "Please enter the name for the output image: ";
        cin >> filename;
        image.saveImage(filename);
    }

    /*
    Convert to Black and white.
    As the past filter there is a nested loop to iterates over each pixil in the image.
    for each pixil the code will calculate the average across all the channels
    Then it determines a new pixel value based on whether the average intensity
    if it is less than 128 the new value will be black which is zero
    if it is more than 128 the new value will be white  which is 255
    finally the new value will be assigned to each value of the channel of the pixel.
    */
    else if (choice == 2)
    {
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
        cout << "Please enter the name for the output image: ";
        cin >> filename;
        image.saveImage(filename);
    }

    // invert the image.
    else if (choice == 3)
    {
        // nested loop to iterate over each pixil
        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                // this loop iterates over the channels of the image
                for (int k = 0; k < image.channels; ++k)
                {
                    // Each pixel value is subtracted from 255,
                    // effectively inverting the color intensity.
                    // This operation is performed for each channel of the pixel.
                    image(i, j, k) = 255 - image(i, j, k);
                }
            }
        }

        cout << "Please enter the name for the output image: ";
        cin >> filename;
        image.saveImage(filename);
    }

    // flip the image filter.
    else if (choice == 4)
    {
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
        cout << "Please enter the name for the output image: ";
        cin >> filename;
        image.saveImage(filename);
    }

    // saving the image with another extention.
    else if (choice == 6)
    {
        cout << "Please enter the name for the output image: ";
        cin >> filename;
        image.saveImage(filename);
    }

    // the Detect Image Edges filter.
    else if (choice == 5)
    {
        Image edgeDetectedImage(filename);

        for (int x = 1; x < image.width - 1; ++x)
        {
            for (int y = 1; y < image.height - 1; ++y)
            {
                for (int k = 0; k < image.channels; ++k)
                {

                    int sobelX = -image(x - 1, y - 1, k) - 2 * image(x - 1, y, k) - image(x - 1, y + 1, k) +
                                 image(x + 1, y - 1, k) + 2 * image(x + 1, y, k) + image(x + 1, y + 1, k);

                    int sobelY = -image(x - 1, y - 1, k) - 2 * image(x, y - 1, k) - image(x + 1, y - 1, k) +
                                 image(x - 1, y + 1, k) + 2 * image(x, y + 1, k) + image(x + 1, y + 1, k);

                    int gradientMagnitude = sqrt(sobelX * sobelX + sobelY * sobelY);

                    gradientMagnitude = min(max(gradientMagnitude, 0), 255);

                    edgeDetectedImage(x, y, k) = gradientMagnitude;
                }
            }
        }

        for (int x = 0; x < edgeDetectedImage.width; ++x)
        {
            for (int y = 0; y < edgeDetectedImage.height; ++y)
            {
                for (int k = 0; k < edgeDetectedImage.channels; ++k)
                {
                    edgeDetectedImage(x, y, k) = 255 - edgeDetectedImage(x, y, k);
                }
            }
        }

        cout << "Please enter the name of the new edited photo followed by the desired extension: ";
        cin >> filename;
        edgeDetectedImage.saveImage(filename);

        return 0;
    }

    // this choice is for the choice 7 which is exit the app.
    else if (choice == 7)
    {
        cout << "Exiting the application. Goodbye ya user!" << endl;
        return 0; // Exit the program
    }
}