// including the requierd headers
#include <iostream>
using namespace std;
#include "Image_Class.h"

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
        /* code */
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
