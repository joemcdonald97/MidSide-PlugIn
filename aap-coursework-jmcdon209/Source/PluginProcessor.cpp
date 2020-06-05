/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MsutilityAudioProcessor::MsutilityAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    // Adds the StereoWidth parameter to the AudioProcessor
StereoWidth = new AudioParameterFloat("StereoWidth", "StereoWidth", NormalisableRange<float>(0.0f, 2.0f), 1.0f);
addParameter(StereoWidth);
    
Input = new AudioParameterChoice("Input", "Input", {"Stereo", "MidSide"},  0);
addParameter(Input);

Output = new AudioParameterChoice("Output", "Output", {"Stereo", "MidSide"},  0);
addParameter(Output);

swapSides = new AudioParameterBool("swapSides", "Swap Sides", false);
addParameter(swapSides);
    
cutoffParam = new AudioParameterFloat("cutoffParam", "Cutoff Frequency Hz", 50.0f, 2000.0f, 1000.0f);
addParameter(cutoffParam);
  
BassWidth = new AudioParameterFloat("BassWidth", "BassWidth", NormalisableRange<float>(0.0f, 2.0f), 1.0f);
addParameter(BassWidth);
    
outputLevel = new AudioParameterFloat("outputLevel", "Output Level", NormalisableRange<float>(0.0f, 2.0f), 1.0f);
addParameter(outputLevel);
    
}

MsutilityAudioProcessor::~MsutilityAudioProcessor()
{
}

//==============================================================================
const String MsutilityAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MsutilityAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MsutilityAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MsutilityAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MsutilityAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MsutilityAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MsutilityAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MsutilityAudioProcessor::setCurrentProgram (int index)
{
}

const String MsutilityAudioProcessor::getProgramName (int index)
{
    return {};
}

void MsutilityAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MsutilityAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    // Maximilian needs to know what the sampling rate is, number of channels, and number of samples per block
    maxiSettings::setup(sampleRate, getNumInputChannels(), samplesPerBlock);
    
}

void MsutilityAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MsutilityAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MsutilityAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
 

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    
    for (int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
   
    
    
    
    // channelDataL and channelDataR are pointers to arrays of length numSamples which // contain the audio for one channel. You repeat this for each channel

    
    float w = StereoWidth->get();
    auto choice1 = Input->getIndex();
    auto choice2 = Output->getIndex();
    
    auto cutoff = cutoffParam->get() / 10000.0f; // Needs to be in range of 0-1 for maxiFilter cutoff
    auto bw = BassWidth->get();
    
    float outputL = outputLevel->get();
    
    auto SwapSides = swapSides->get();
   
        
    {
        
        auto* channelDataLeft = buffer.getWritePointer(0);
        auto* channelDataRight = buffer.getWritePointer(1);
        
        auto outL = 0.0f;
        auto outR = 0.0f;
        auto bassoutL = 0.0f;
        auto bassoutR = 0.0f;
        
        for (int i = 0; i < buffer.getNumSamples(); i++)
    
         
    
        {
           
            // ..do something to the data.
         
     
            if (choice1 == 0 && choice2 == 0) // stereo in stereo out
                
            {
                
                // stereo to ms
                float xSide = (0.5f * (channelDataLeft[i] - channelDataRight[i]));
                float xMid = (0.5f * (channelDataLeft[i]+ channelDataRight[i]));
                
                
                
                
                // Stereo Width
                
                auto Side  = w * (xSide);
                auto Mid = (2-w) * (xMid);
                
                
                // ms to stereo
                auto DataLeft= (Mid+Side);
                auto DataRight= (Mid-Side);

                // split left and right into high and low freqs
                bassoutL = maxiLP[0].lopass(DataLeft, cutoff);
                bassoutR = maxiLP[1].lopass(DataRight, cutoff);
                outL = maxiHP[0].hipass(DataLeft, cutoff);
                outR = maxiHP[1].hipass(DataRight, cutoff);
                
                // bass stereo to ms
                float lSide = (0.5f * (bassoutL - bassoutR));
                float lMid = (0.5f * (bassoutL + bassoutR));
                
                //stereo width to low freqs
                auto SideBW  = bw * (lSide);
                auto MidBW = (2-bw) * (lMid);
                
                // convert bass ms back to stereo
                
                auto lDataLeft= (MidBW + SideBW);
                auto lDataRight= 1.25f * (MidBW - SideBW);
                
                if (SwapSides)
                
                {
                    channelDataLeft[i] = outputL* (lDataRight + outR);
                    channelDataRight[i] =outputL* (lDataLeft + outL) ;
                }
                
               
                else
                
                {
                // output
                channelDataLeft[i] = outputL* (lDataLeft + outL);
                channelDataRight[i] = outputL* (lDataRight + outR);
                }
                
                
            }
            
            else if (choice1 == 0 && choice2 == 1) // stereo in ms out
                
            {
              
                  // Stereo to MS
                auto xSide = 0.5f * (channelDataLeft[i] - channelDataRight[i]);
                auto xMid = 0.5f * (channelDataLeft[i] + channelDataRight[i]);
                
                // Stereo Width
                auto Side  = w * (xSide);
                auto Mid = (2-w) * (xMid);
           
                // MS Out
                 auto DataLeft = 2* Mid;
                 auto DataRight = 2* Side;
                
                // split left and right into high and low freqs
                bassoutL = maxiLP[0].lopass(DataLeft, cutoff);
                bassoutR = maxiLP[1].lopass(DataRight, cutoff);
                outL = maxiHP[0].hipass(DataLeft, cutoff);
                outR = maxiHP[1].hipass(DataRight, cutoff);
                
                // bass stereo to ms
                float lSide = (0.5f * (bassoutL - bassoutR));
                float lMid = (0.5f * (bassoutL + bassoutR));
                
                //stereo width to low freqs
                auto SideBW  = bw * (lSide);
                auto MidBW = (2-bw) * (lMid);
                
                // combine stereo width bass freqs with high freqs
            
               auto lefto= (MidBW + outL);
               auto righto= (SideBW - outR);
                
                if (SwapSides)
                    
                {
                    // output with level
                    channelDataLeft[i] = outputL* (righto);
                    channelDataRight[i] = outputL* (lefto) ;
                }
                
                
                else
                    
                {
                    // output with level
                    channelDataLeft[i] = outputL* (lefto);
                    channelDataRight[i] = outputL* (righto);
                }
            
                
            
                
            }
            
           else if (choice1 == 1 && choice2 == 1) // ms in ms out
                
            {
                
                // MS in
                
                auto xSide = channelDataRight[i];
                auto xMid = channelDataLeft[i] ;
                
                //Stereo Width
                auto Side  = w * (xSide);
                auto Mid = (2-w) * (xMid);
                
                // MS out
              auto  DataLeft= Mid;
              auto  DataRight= Side;
                
                // split left and right into high and low freqs
                bassoutL = maxiLP[0].lopass(DataLeft, cutoff);
                bassoutR = maxiLP[1].lopass(DataRight, cutoff);
                outL = maxiHP[0].hipass(DataLeft, cutoff);
                outR = maxiHP[1].hipass(DataRight, cutoff);
                
                // bass stereo to ms
                float lSide = (0.5f * (bassoutL - bassoutR));
                float lMid = (0.5f * (bassoutL + bassoutR));
                
                //stereo width to low freqs
                auto SideBW  = bw * (lSide);
                auto MidBW = (2-bw) * (lMid);
                
                // combine stereo width bass freqs with high freqs
                
                auto lefto= (MidBW + outL);
                auto righto= (SideBW - outR);
                
                if (SwapSides)
                    
                {
                    // output with level
                    channelDataLeft[i] = outputL* (righto);
                    channelDataRight[i] = outputL* (lefto) ;
                }
                
                
                else
                    
                {
                    // output with level
                    channelDataLeft[i] = outputL* (lefto);
                    channelDataRight[i] = outputL* (righto);
                }
                
                
            }
            
            
           else if (choice1 == 1 && choice2 == 0) // MS in Stereo out
                
            {
          
                
                // MS in
                auto xSide = channelDataRight[i];
                auto xMid = channelDataLeft[i] ;
                
                // Stereo Width
                
                auto Side  = w * (xSide);
                auto Mid = (2-w) * (xMid);
                
                // Stereo Out
                auto DataLeft= (Mid+Side);
                auto DataRight= (Mid-Side);
                
                // split left and right into high and low freqs
                bassoutL = maxiLP[0].lopass(DataLeft, cutoff);
                bassoutR = maxiLP[1].lopass(DataRight, cutoff);
                outL = maxiHP[0].hipass(DataLeft, cutoff);
                outR = maxiHP[1].hipass(DataRight, cutoff);
                
                // bass stereo to ms
                float lSide = (0.5f * (bassoutL - bassoutR));
                float lMid = (0.5f * (bassoutL + bassoutR));
                
                //stereo width to low freqs
                auto SideBW  = bw * (lSide);
                auto MidBW = (2-bw) * (lMid);
                
                // convert bass ms back to stereo
                
                auto lDataLeft= (MidBW + SideBW);
                auto lDataRight= 1.25f * (MidBW - SideBW);
                
                
                if (SwapSides)
                    
                {
                    channelDataLeft[i] = outputL* (lDataRight + outR);
                    channelDataRight[i] =outputL* (lDataLeft + outL) ;
                }
                
                
                else
                    
                {
                    // output
                    channelDataLeft[i] = outputL* (lDataLeft + outL);
                    channelDataRight[i] = outputL* (lDataRight + outR);
                }
                
                

                
            }
            
                    
                }
            
        
        }
    }


//==============================================================================
bool MsutilityAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MsutilityAudioProcessor::createEditor()
{
    return new GenericAudioProcessorEditor(this);
}

//==============================================================================
void MsutilityAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    // You should use this method to store your parameters in the memory block.
    MemoryOutputStream stream(destData, true);
    stream.writeFloat(*StereoWidth);
    stream.writeFloat(*cutoffParam/ 10000.0f);
    stream.writeFloat(*BassWidth);
    stream.writeFloat(*outputLevel);
    stream.writeBool(*swapSides);
    stream.writeInt(*Input);
    stream.writeInt(*Output);
    
    
    
}

void MsutilityAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    MemoryInputStream stream(data, static_cast<size_t> (sizeInBytes), false);
    StereoWidth->setValueNotifyingHost(stream.readFloat());
    cutoffParam->setValueNotifyingHost(stream.readFloat()*4.5f);
    BassWidth->setValueNotifyingHost(stream.readFloat());
    outputLevel->setValueNotifyingHost(stream.readFloat());
    swapSides->setValueNotifyingHost(stream.readBool());
    Input->setValueNotifyingHost(stream.readInt());
    Output->setValueNotifyingHost(stream.readInt());
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MsutilityAudioProcessor();
}
