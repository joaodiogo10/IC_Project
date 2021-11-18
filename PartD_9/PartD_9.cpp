#include "AudioFile/AudioFile.h"
#include <math.h>

/*
    IC
    PartD
    9.Implement a program to reduce the number of bits used
    to represent each audio sample (uniform scalar quantization).

    João Ferreira 99305
*/
int main(int argc, char * argv[])
{

    //validate input
    if(argc != 3) {
        std::cout << "Usage: reduceBits <audioFilePath> <nBits>" << std::endl;
        return -1;
    }

    std::string filePath = argv[1];
    int reduceAmount = atoi(argv[2]);

    AudioFile<double> audioFile;
    audioFile.load(filePath);

    int numChannels = audioFile.getNumChannels();
    int numSamples = audioFile.getNumSamplesPerChannel();
    int bitDepth = audioFile.getBitDepth();
    audioFile.printSummary();


    int nLevels = std::pow(2,bitDepth);
    int maxValue = 1;
    int minValue = -1;

    //delta: interval between each level
    double delta = (maxValue-minValue)/( (float) nLevels);

    //new parameters
    int newBitDepth = bitDepth - reduceAmount;
    int newLevels = std::pow(2,newBitDepth);
    double newDelta = (maxValue-minValue)/( (float) newLevels - 1);

    //calculate new amplitude level for each sample, according to new bit depth
    for(int i = 0; i < numChannels; i++)
    {  
        for(int j = 0; j < numSamples; j++)
        {
            // somar 1 para evitar problemas na representação de numeros em complemento para 2
            double sampleWithOffset = audioFile.samples[i][j] + 1;
            int sampleLevel = ((int) (sampleWithOffset/delta)) >> reduceAmount;
            double sampleValue = newDelta * sampleLevel;

            // subtrair 1 para compensar
            audioFile.samples[i][j] = sampleValue - 1;
        }
    }
    audioFile.save("result.wav");
    audioFile.setBitDepth(newBitDepth);

    audioFile.printSummary();
}
