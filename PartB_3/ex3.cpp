#include <iostream>
#include <fstream>
#include "AudioFile.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Need two arguments" << endl;
    }
    else
    {
        AudioFile<double> audioFileIn;
        AudioFile<double> audioFileOut;

        audioFileIn.load(argv[1]);

        int sampleRate = audioFileIn.getSampleRate();
        int bitDepth = audioFileIn.getBitDepth();

        int numSamples = audioFileIn.getNumSamplesPerChannel();
        double lengthInSeconds = audioFileIn.getLengthInSeconds();

        int numChannels = audioFileIn.getNumChannels();
        bool isMono = audioFileIn.isMono();
        bool isStereo = audioFileIn.isStereo();

        // or, just use this quick shortcut to print a summary to the console
        audioFileIn.printSummary();

        // 1. Create an AudioBuffer
        // (BTW, AudioBuffer is just a vector of vectors)

        AudioFile<double>::AudioBuffer buffer;

        // 2. Set to (e.g.) two channels
        buffer.resize(numChannels);

        // 3. Set number of samples per channel

        for (int i = 0; i < numChannels; i++)
        {
            buffer[i].resize(numSamples);
        }

        // 4. do something here to fill the buffer with samples, e.g.

        for (int i = 0; i < numSamples; i++)
        {
            for (int channel = 0; channel < numChannels; channel++)
                buffer[channel][i] = audioFileIn.samples[channel][i];
        }

        audioFileOut.setBitDepth(bitDepth);
        audioFileOut.setSampleRate(sampleRate);

        // 5. Put into the AudioFile object
        bool ok = audioFileOut.setAudioBuffer(buffer);
        audioFileOut.save(argv[2]);
        audioFileOut.printSummary();
    }
}