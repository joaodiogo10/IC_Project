#include "AudioFile/AudioFile.h"
#include <math.h>

std::string filePathOriginal = "sample04.wav";
std::string filePathReduced = "result.wav";

int main(int argc, char * argv[]){
    AudioFile<double> audioFile;
    audioFile.load(filePathOriginal);

    AudioFile<double> reducedAudio;
    reducedAudio.load(filePathReduced);

    int numChannels = audioFile.getNumChannels();
    int numSamples = audioFile.getNumSamplesPerChannel();
    int bitDepth = audioFile.getBitDepth();
    audioFile.printSummary();

    int sum = 0;

    for(int i = 0; i < numChannels; i++){
        for(int j = 0; j < numSamples; j++){
            sum += std::pow(audioFile.samples[i][j] - reducedAudio.samples[i][j], 2);
        }
    }

    double MSE = (double)sum/((double)numChannels * (double)numSamples);

    int MAX = std::pow(2,bitDepth * 16) - 1;
    float PSNR = 10* std::log10(std::pow(MAX,2)/MSE);
    std::cout << PSNR << std::endl;
}