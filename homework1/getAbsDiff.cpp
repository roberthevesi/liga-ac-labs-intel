#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

typedef struct image{
    int R;
    int G;
    int B;
}RGBimage;

int main(int argc, char **argv){
    if(argc != 3){
        cout << "Usage error. Please provide both source images.\nUsage: " << argv[0] << " [.ppm image] [.ppm image]\n";
        return 0;
        // exit(0);
    }

    // open the first .ppm image
    ifstream f1;
    f1.open(argv[1]);

    if(!f1.is_open()){
        cout << "Could not open input file 1." << endl;
        return 0;
    }

    // open the second .ppm image
    ifstream f2;
    f2.open(argv[2]);

    if(!f2.is_open()){
        cout << "Could not open input file 2." << endl;
        return 0;
    }

    int maxValue1;
    int width1, height1;
    char type1[3];

    f1 >> type1; // get img type (P3/P6/etc)
    f1 >> width1 >> height1;
    f1 >> maxValue1; // get RGB max value from ppm file

    int maxValue2;
    int width2, height2;
    char type2[3];

    f2 >> type2; // get img type (P3/P6/etc)
    f2 >> width2 >> height2;
    f2 >> maxValue2; // get RGB max value from ppm file

    // check wether the two images are compatible or not
    if(width1 != width2 || height1 != height2 || maxValue1 != maxValue2 || strcmp(type1, type2) != 0){
        cout << "Incompatible images!" << endl;
        return 0;
    }

    // create the output image
    ofstream fout;
    fout.open("abs_diff_output.ppm");

    if(!fout.is_open()){
        cout << "Could not open output file." << endl;
        return 0;
    }

    fout << type1 << endl;
    fout << width1 << endl << height1 << endl;
    fout << maxValue1 << endl;

    int R1, G1, B1;
    int R2, G2, B2;

    for(int line=0; line<height1; line++){ 
        for(int col=0; col<width1; col++){
            f1 >> R1 >> G1 >> B1;
            f2 >> R2 >> G2 >> B2;

            fout << abs(R1-R2) << endl;
            fout << abs(G1-G2) << endl;
            fout << abs(B1-B2) << endl;
        }
    }

    cout << "The absolute difference has been written to output.ppm" << endl;

    f1.close();
    f2.close();
    
    return 0;  
}