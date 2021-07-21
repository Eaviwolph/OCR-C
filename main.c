#include "NeuralSystem/XORNeuralSystem.h"
#include "IMGtreatment/LoadIm.h"
#include "CharDetector/CharBlockDetector.h"
#include "string.h"

void help()
{
    printf("Usage: main [OPTION]\n");
    printf("Options:\n");
    printf("XOR -> XOR training\n");
    printf("Image {File.bmp} -> Image tests\n");
    printf("Cut -> Cuts matrix tests\n");
}

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        if(strcmp(argv[1],"XOR") == 0)
        {
            XORTrain();
        }
        else if(strcmp(argv[1],"Cut") == 0)
        {
            CharDetector();
        }
        else
        {
            help();
        }
    }
    else if(argc == 3 && strcmp(argv[1],"Image") == 0)
    {
        IMGTreatment(argv[2]);
    }
    else
    {
        help();
    }
    return 0;
}
