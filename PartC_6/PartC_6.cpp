#include "AudioFile/AudioFile.h"
#include <map>
#include <math.h>
#include <fstream>

float roundoff(float value, unsigned char prec);
void writeResults(const std::string filePath, const std::vector<std::map<float,int>> samplesMap, const std::vector<double> entropies);
void writeMatlabVectorFiles(const std::vector<std::map<float,int>> samplesMap);

u_char precision = 3;

int main(int argc, char* agrv[]) {

    //validate input
    if(argc != 3) {
        std::cout << "Usage: audioEntropy <audioFilePath> <resultFilePath>" << std::endl;
        return -1;
    }
    
    std::string filePath = agrv[1];
    std::string resultFile = agrv[2];

    AudioFile<double> audioFile;
    bool result = audioFile.load(filePath);
    if(!result)
    {
        std::cout << "ERROR: Unable to read audio file" << std::endl;
        return -1;
    }

    int numChannels = audioFile.getNumChannels();
    int numSamples = audioFile.getNumSamplesPerChannel();

    //array of maps containing sample count of each channels + average of the channels (samplesMap[numChannels])
    std::vector<std::map<float,int>> samplesMap;
    samplesMap.resize(numChannels+1);

    //initialize maps containing sample count at 0
    double minAmplitudeInterval = 1/pow(10,precision);
    for(int j = 0; j < numChannels + 1; j++)
    {
        for(int i = 0; i <= 1 * pow(10,precision); i++) {
            samplesMap[j][i * minAmplitudeInterval] = 0;
            samplesMap[j][-i * minAmplitudeInterval] = 0;
        }
    }

    float totalSamples; 
    //read sample count from all channels and calculate the average of the channels
    for(int i = 0; i < numSamples; i++)
    {  
        totalSamples = 0;
        for(int j = 0; j < numChannels; j++)
        {
            float value = roundoff(audioFile.samples[j][i], precision);
            totalSamples += value;
            samplesMap[j][value]++;
        }
        samplesMap[numChannels][roundoff(totalSamples/numChannels, precision)]++;
    }


    //calculate probability of each amplitude for each channel and the average of the channels
    std::vector<std::map<float,float>> samplesProb;
    samplesProb.resize(numChannels+1);
    for(int i = 0; i < numChannels+1; i++) 
    {
        for(auto itr = samplesMap[i].begin(); itr != samplesMap[i].end(); itr++)
        {
            samplesProb[i][(*itr).first] = (*itr).second / (float) numSamples;
        }
    }

    //calculate entropy for each channel and the average of the channels
    std::vector<double> entropies;
    entropies.resize(numChannels+1);

    for(int i = 0; i < numChannels+1; i++) 
    {   
        for(auto itr = samplesProb[i].begin(); itr != samplesProb[i].end(); itr++)
        {
            if( (*itr).second != 0)
                entropies[i] += - (*itr).second * log2((*itr).second);
        }
    }

    std::cout << "--------" << filePath << "--------" << std::endl;
    audioFile.printSummary();

    for(int i = 0; i < numChannels; i++)
        std::cout << "Entropy of channel "<< i + 1 << ": " << entropies[i] << std::endl;
  
    std::cout << "Entropy of Average(Mono): " << entropies[numChannels] << std::endl;

    writeResults(resultFile, samplesMap, entropies);
    writeMatlabVectorFiles(samplesMap);

    return 0;
}

float roundoff(float value, unsigned char prec)
{
  float pow_10 = pow(10.0f, (float)prec);
  return round(value * pow_10) / pow_10;
}

void writeResults(std::string filePath, std::vector<std::map<float,int>> samplesMap, std::vector<double> entropies)
{
    std::ofstream fileOut(filePath);
       if(!fileOut.is_open()) {
        std::cerr << "Failed to open the file '" << filePath << "'" << std::endl;
    }

    for(u_long i = 0; i < samplesMap.size()-1; i++)
    {
        fileOut << "\n------------Channel " << i+1 << "------------" << std::endl;

        for(auto itr = samplesMap[i].begin(); itr != samplesMap[i].end(); itr++)
        {
            fileOut << (*itr).first <<  ": " << (*itr).second << std::endl;             
        }
        fileOut << "\nEntropy: " << entropies[i] << std::endl;
    }

    fileOut << "\n------------Average(Mono)------------" << std::endl;

    for(auto itr = samplesMap[samplesMap.size()-1].begin(); itr != samplesMap[samplesMap.size()-1].end(); itr++)
    {
        fileOut << (*itr).first <<  ": " << (*itr).second << std::endl;             
    }
    
    fileOut << "\nEntropy: " << entropies[samplesMap.size()-1] << std::endl;
    
    fileOut.close();
}


void writeMatlabVectorFiles(const std::vector<std::map<float,int>> samplesMap){
    const std::map<float,int> channel1 = samplesMap[0];
    const std::map<float,int> channel2 = samplesMap[1];
    const std::map<float,int> monoChannel =  samplesMap[2];

    std::ofstream xAxisFile("matlab/xAxis.txt");
    std::ofstream channel1File("matlab/channel1.txt");
    std::ofstream channel2File("matlab/channel2.txt");
    std::ofstream monoChannelFile("matlab/monoChannel.txt");

    //write xAxisFile (amplitude values)
    for(auto itr = channel1.begin(); itr != channel1.end(); itr++) {
        xAxisFile << (*itr).first << std::endl;        
    }

    //write channel1File (amplitude values)
    for(auto itr = channel1.begin(); itr != channel1.end(); itr++) {
        channel1File << (*itr).second << std::endl;        
    }

    //write channel2File (amplitude values)
    for(auto itr = channel2.begin(); itr != channel2.end(); itr++) {
        channel2File << (*itr).second << std::endl;        
    }

    //write monoChannelFile (amplitude values)
    for(auto itr = monoChannel.begin(); itr != monoChannel.end(); itr++) {
        monoChannelFile << (*itr).second << std::endl;        
    }
    xAxisFile.close();
    channel1File.close();
    channel2File.close();
    monoChannelFile.close();
}
