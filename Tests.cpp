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
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    // Convert to grayscale
    if (choice == 1)
    {
        /*
        i : weidth
        j : height
        k : color channel index (يعني البيكسل دي شايله لون ايه ) 0 for red , 1 for green , 2 for blue.

        hwa fe awl w tany loop de by3dy 3la kol pixil fe el sora by height and weidth
        fe talt loop byhsb el average bta3 kol pixil fe el sora

        */
        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                unsigned int avg = 0; // Initialize average value

                for (int k = 0; k < 3; ++k)
                {
                    // bygm3 kol values el pixiles
                    avg += image(i, j, k); // Accumulate pixel values
                }

                // b3d ma bygm3hom by2smhom 3la talata 3shan ygeb el average
                avg /= 3; // Calculate average

                // Set all channels to the average value
                // hwa hna bykhly el red pixels average
                image(i, j, 0) = avg;
                // hwa hna bykhly el green pixels average
                image(i, j, 1) = avg;
                // hwa hna bykhly el blue pixels average.
                image(i, j, 2) = avg;
            }
        }
    }
    else if (choice == 2)
    {
        // Apply black and white filter
        // el threshold da el hwa el midnumber bta3 el arkam l2nna 3ndna el values from 0 to 255
        // 255 de kda white w 0 kda black fa ahna 3mlna divide 255/2 tl3lna 127.5 y3ny 128
        // ahna b2a hnhsb el values zy ma 3mlna fe el grayscale lw tl3t akbr mn 128 yb2a white
        int threshold = 128; // Adjust threshold as needed
        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                // Calculate grayscale value
                unsigned int avg = 0;
                for (int k = 0; k < 3; ++k)
                {
                    avg += image(i, j, k);
                }
                avg /= 3;

                // Check if pixel value is above threshold
                if (avg > threshold)
                {
                    // Set pixel to white
                    image(i, j, 0) = 255;
                    image(i, j, 1) = 255;
                    image(i, j, 2) = 255;
                }
                else
                {
                    // Set pixel to black
                    image(i, j, 0) = 0;
                    image(i, j, 1) = 0;
                    image(i, j, 2) = 0;
                }
            }
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
