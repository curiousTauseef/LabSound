// Copyright (c) 2003-2013 Nick Porcino, All rights reserved.
// License is MIT: http://opensource.org/licenses/MIT

#ifndef LabSound_ADSRNode_h_impl
#define LabSound_ADSRNode_h_impl

#include "../Modules/webaudio/AudioContext.h"
#include "../platform/audio/AudioBus.h"
#include "../Modules/webaudio/AudioParam.h"
#include "../Modules/webaudio/AudioScheduledSourceNode.h"
#include "../Modules/webaudio/AudioBasicProcessorNode.h"
#include "../Modules/webaudio/AudioBasicInspectorNode.h"
#include "../WTF/wtf/RefPtr.h"
#include "../Modules/webaudio/GainNode.h"

namespace LabSound {
    using namespace WebCore;

    class ADSRNode : public WebCore::AudioBasicProcessorNode
    {
    public:
        static WTF::PassRefPtr<ADSRNode> create(WebCore::AudioContext* context, float sampleRate)
        {
            return adoptRef(new ADSRNode(context, sampleRate));
        }

        // If noteOn is called before noteOff has finished, a pop can occur. Polling
        // finished and avoiding noteOn while finished is true can avoid the popping.
        //
		void noteOn();
		void noteOff();
        bool finished(); // if a noteOff has been issued, finished will be true after the release period

		void set(float aT, float aL, float d, float s, float r);

        AudioParam* attackTime() const;
		AudioParam* attackLevel() const;
		AudioParam* decayTime() const;
		AudioParam* sustainLevel() const;
		AudioParam* releaseTime() const;

    private:
        ADSRNode(WebCore::AudioContext*, float sampleRate);
        virtual ~ADSRNode();

        class AdsrNodeInternal;
        AdsrNodeInternal* data;
    };
    
}

#endif