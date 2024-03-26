#include <iostream>
#include "Image_Class.h"
using namespace std;

int main (){
    Image image("building.jpg");

    for (int i = 0; i < image.width; ++i){
        for (int j = 0; j < image.height; ++j){
            unsigned int avg = 0;
            for (int k = 0; k < image.channels; ++k){
                avg += image(i,j,k);
            }
            avg = avg/3;
            unsigned char newValue = (avg < 128) ? 0 : 255;
            for (int k = 0; k < image.channels; ++k){
                image(i,j,k) = newValue;
            }
        }
    }

    image.saveImage("BuildingBlackWhite.png"); 

    return 0;
}