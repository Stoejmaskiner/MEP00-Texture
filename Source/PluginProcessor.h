/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "utils/stoej_juce_utils.h"
#include "dsp/generators/stoej_white_noise.h"
#include "dsp/procesors/mfx/stoej_multiplicative_noise.h"
#include "PluginParameters.h"


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
            using namespace Parameters;

            layout.add(
                stoej::UniqueParamBool( enable_grit),
                stoej::UniqueParamFloat(noise_density),
                stoej::UniqueParamFloat(noise_mix),
                stoej::UniqueParamFloat(filter_lp_cutoff),
                stoej::UniqueParamFloat(filter_hp_cutoff),
                stoej::UniqueParamFloat(noise_width),
                stoej::UniqueParamFloat(output_level)
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
    using Gain = juce::dsp::Gain<float>;
    using DryWet = juce::dsp::DryWetMixer<float>;
    using Filter = juce::dsp::StateVariableFilter::Filter<float>;
    
    size_t max_size;
    float sample_rate;

    stoej::WhiteNoise<float> white_noise_;
    stoej::MultiplicativeNoise<float> multiplicative_noise_;
    
    /*
    stoej::RingModNoiseA rm_noise_a_;
    stoej::RingModNoiseB rm_noise_b_;
    Filter noise_hp_;
    Filter noise_lp_;
    DryWet mixer_;
    Gain post_gain_;
    */

    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MEP00TextureAudioProcessor)
};
