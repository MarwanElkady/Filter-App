#include <iostream>
#include "Image_Class.h"
using namespace std;

int main()
{
    string imageName;
    cout << "Pleases enter the name of your photo with the extension: ";
    cin >> imageName;
    Image image(imageName);

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

    cout << "Please enter the name of the new edited photo followed by the desired extenstion: ";
    cin >> imageName;
    image.saveImage(imageName);

    return 0;
}