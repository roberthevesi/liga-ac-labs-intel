#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

#define BOX_SIZE 5

typedef struct image{
    int R;
    int G;
    int B;
}RGBimage;

int main(int argc, char* argv[]){
    // check wether we have 2 arguments (code and source image) or not
    if(argc != 2){
        cout << "Usage error. Please provide source image.\nUsage: " << argv[0] << " [.ppm image]\n";
        exit(0);
    }

    ifstream f;
    f.open(argv[1]);

    // check if we can open source file
    if(!f.is_open()){
        cout << "Could not open input file.\n";
        exit(0);
    }

    // generate output file name
    std::string fileName = std::to_string(BOX_SIZE);
    fileName += "x";
    fileName += std::to_string(BOX_SIZE);
    fileName += "_blurred_";
    fileName += argv[1];

    ofstream fout;
    fout.open(fileName);

    // check if we can open dest file
    if(!fout.is_open()){
        cout << "Could not open output file.\n";
        exit(0);
    }

    int maxValue;
    int width, height;
    char type[3];

    f >> type; // get img type (P3/P6/etc)
    f >> width >> height;
    f >> maxValue; // get RGB max value from ppm file

    // write above to dest image
    fout << type << endl; 
    fout << width << " " << height << endl;
    fout << maxValue << endl;

    RGBimage **image = new RGBimage*[height];
    for(int i=0; i<height; i++)
        image[i] = new RGBimage[width];

    // check if memory can be allocated
    if(image == nullptr){
        cout << "Memory could not be allocated.\n";
        exit(0);
    }
    
    int line, col;

    // read image from .ppm file
    for(line=0; line<height; line++){ 
        for(col=0; col<width; col++){
            f >> image[line][col].R >> image[line][col].G >> image[line][col].B;
        }
    }

    int totalRed, totalGreen, totalBlue;
    int k;
    int x, y;

    // apply box blur 
    for(line=0; line<height; line++){
        for(col=0; col<width; col++){
            totalRed = totalGreen = totalBlue = 0;
            k = 0;

            if(line < floor(BOX_SIZE/2)) // check wether we can go BOX_SIZE/2 pixels before the current line or not
                x = 0;
            else
                x = line - floor(BOX_SIZE/2);

            if(col < floor(BOX_SIZE/2)) // check wether we can go BOX_SIZE/2 pixels before the current col or not
                y = 0;
            else
                y = col - floor(BOX_SIZE/2);            

            for(int i = x; i < x+BOX_SIZE; i++){
                if(i == height) // check if we're outside of matrix
                    break;
                for(int j = y; j < y+BOX_SIZE; j++){
                    if(j == width) // check if we're outside of matrix
                        break;

                    k++;
                    totalRed += image[i][j].R;
                    totalGreen += image[i][j].G;
                    totalBlue += image[i][j].B;
                }
            }

            // get the average of all pixels in the submatrix of size BOX_SIZE
            image[line][col].R = round(totalRed/(k*1.0));
            image[line][col].G = round(totalGreen/(k*1.0));
            image[line][col].B = round(totalBlue/(k*1.0));

            // write the blurred pixels to our output image
            fout << image[line][col].R << endl << image[line][col].G << endl << image[line][col].B << endl;
        }
    }

    cout << "Successfully blurred photo to " << fileName << endl;

    // free allocated memory
    for(int i=0; i<height; i++)
        delete[] image[i];
    delete[] image;

    f.close();
    fout.close();

    return 0;
}