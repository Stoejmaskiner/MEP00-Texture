/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <../shared-code/stoej_juce_utils.h>

//==============================================================================
/**
*/
class MEP00TextureAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    MEP00TextureAudioProcessor();
    ~MEP00TextureAudioProcessor() override;

    // the apvts is used to store parameters and plugin state
    juce::AudioProcessorValueTreeState apvts{
        *this, nullptr, "Parameters", []()
        {

            juce::AudioProcessorValueTreeState::ParameterLayout layout;

            layout.add(
                stoej::UniqueParamBool("mode", "simple / gritty", true),
                stoej::UniqueParamFloat(
                    "amount", "amount",
                    juce::NormalisableRange<float>(0.0f, 1.0f),
                    0.5f),
                stoej::UniqueParamBool("filter_enable", "toggle filter", true),
                stoej::UniqueParamFloat(
                    "filter_LP_cutoff", "LP cutoff",
                    juce::NormalisableRange<float>(20.0f, 18000.0f, 0.0f, 0.3f),
                    12000.0f),
                stoej::UniqueParamFloat(
                    "filter_HP_cutoff", "HP cutoff",
                    juce::NormalisableRange<float>(5.0f, 16000.0f, 0.3f),
                    60.0f),
                stoej::UniqueParamFloat(
                    "post_gain", "post gain",
                    juce::NormalisableRange<float>(0.0f, 2.0f, 0.0f, 0.5f),
                    1.0f
                )

            );
            return layout;
        }()
    };

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MEP00TextureAudioProcessor)
};
