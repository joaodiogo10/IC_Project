#include "AudioFile/AudioFile.h"
#include <math.h>

std::string filePath = "audioSamples/sample07.wav";
int reduceAmount = 14;

int main(int agrc, char * agrv[])
{
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
    double newDelta = (maxValue-minValue)/( (float) newLevels );

    //calculate new amplitude level for each sample, according to new bit depth
    for(int i = 0; i < numChannels; i++)
    {  
        for(int j = 0; j < numSamples; j++)
        {
            int sampleLevel = ((int) (audioFile.samples[i][j]/delta)) >> reduceAmount;
            double sampleValue = newDelta * sampleLevel;
            audioFile.samples[i][j] = sampleValue;
        }
    }
    audioFile.save("result.wav");
    audioFile.setBitDepth(newBitDepth);

    audioFile.printSummary();
}