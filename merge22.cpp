#include <iostream>
#include "Image_Class.h"

using namespace std;

Image mergeImages(const Image &image1, const Image &image2)
{
    // Determine minimum dimensions
    int minWidth = min(image1.width, image2.width);
    int minHeight = min(image1.height, image2.height);

    // Create a new image for the merged result
    Image mergedImage(minWidth, minHeight);

    // Merge images by adding pixel values and dividing by 2
    for (int y = 0; y < minHeight; ++y)
    {
        for (int x = 0; x < minWidth; ++x)
        {
            for (int c = 0; c < mergedImage.channels; ++c)
            {
                int pixelValue1 = image1.imageData[(y * image1.width + x) * image1.channels + c];
                int pixelValue2 = image2.imageData[(y * image2.width + x) * image2.channels + c];
                mergedImage.imageData[(y * minWidth + x) * mergedImage.channels + c] = (pixelValue1 + pixelValue2) / 2;
            }
        }
    }

    return mergedImage;
}

int main()
{
    // Prompt the user to enter the names of the images
    string imageName1, imageName2;
    cout << "Enter the name of the first image: ";
    cin >> imageName1;
    cout << "Enter the name of the second image: ";
    cin >> imageName2;

    // Load images
    Image image1(imageName1);
    Image image2(imageName2);

    // Merge images
    Image mergedImage = mergeImages(image1, image2);

    // Save the merged image
    mergedImage.saveImage("merged_image.jpg");

    return 0;
}
