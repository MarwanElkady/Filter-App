// including the requierd headers
#include <iostream>
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
    // make a var to store the name of the image file
    string filename;
    cout << "Please enter the photo name : ";
    cin >> filename;

    // this line responisable to open the photo
    Image image(filename);

    int choice;
    cout << "Choose filter type:" << endl;
    cout << "1. Grayscale" << endl;
    cout << "2. Black and White" << endl;
    cout << "3. image invert" << endl;
    cout << "4. flip filter" << endl;
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    // Convert to grayscale
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
    }

    // Convert to Black and white
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
    }

    // invert the image
    else if (choice == 3)
    {
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
    }

    // flip the image filter
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
    }

    else
    {
        cout << "Invalid choice. Exiting program." << endl;
        return 1;
    }

    cout << "Please enter the name for the output image: ";
    cin >> filename;
    image.saveImage(filename);

    return 0;
}
