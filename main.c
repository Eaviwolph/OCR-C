#include "IMGtreatment/LoadIm.h"
#include "CharDetector/CharBlockDetector.h"
#include "string.h"
#include "UI/ui.h"

void help()
{
    printf("Usage: main [OPTION]\n");
    printf("Options:\n");
    printf("XOR -> XOR training\n");
    printf("OCR -> OCR system\n");
}

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        if(strcmp(argv[1],"XOR") == 0)
        {
            XORTrain();
        }
        else if(strcmp(argv[1],"OCR") == 0)
        {
            ui();
        }
        else
        {
            help();
        }
    }
    else
    {
        help();
    }
    return 0;
}
