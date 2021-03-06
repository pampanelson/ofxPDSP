
// Controls.h
// ofxPDSP
// Nicola Pisanti, MIT License, 2016

#ifndef OFXPDSPMIDI_PDSPMIDICONTROLS_H_INCLUDED
#define OFXPDSPMIDI_PDSPMIDICONTROLS_H_INCLUDED

#ifndef __ANDROID__

#include "ofxMidi.h"
#include "../DSP/control/SequencerValueOutput.h"
#include <chrono>
#include "helper/MidiCCBuffers.h"
#include "helper/Controller.h"
#include "MidiIn.h"

/*!
@brief utility class to parse control change data from a pdsp::midi::Input and convert it to a bank of patchable modules with optional slewed output. By default outputs are slewed to 50ms. 
*/

namespace pdsp{ namespace midi {

class Controls : public pdsp::Controller {
    
public:
    Controls();
    Controls(int maxCC);
    /*!
    @brief sets the slew times of the CCs
    @param[in] slewTimeMs new slew time in milliseconds
    */
    void setCCSlew(float slewTimeMs);

    /*!
    @brief sets the max CC number parsed, and resizes the out_cc vector
    @param[in] slewTimeMs new slew time in milliseconds
    */
    void setMaxCCNum(int ccNum);


    /*!
    @brief returns the number of the max returned CC
    @param[in] slewTimeMs new slew time in milliseconds
    */
    int  getMaxCCNum();

    /*!
    @brief returns a control value corrisponding to the given cc number, the output is mapped to the 0.0f-1.0f range.
    @param[in] cc the cc number for the output
    */    
    pdsp::SequencerValueOutput & out( int cc );
    
/*!
    @cond HIDDEN_SYMBOLS
*/
    std::vector<pdsp::SequencerValueOutput>    outs_cc; // this has to become private in later versions
    
    void processMidi(const pdsp::midi::Input &midiInProcessor, const int &bufferSize ) noexcept override;   
/*!
    @endcond 
*/
private: 
    float slewTime;
    pdsp::helper::MidiCCBuffers midiCC;
        
};

}} // end namespaces

#endif

#endif //OFXPDSPMIDI_PDSPMIDICONTROLS_H_INCLUDED
