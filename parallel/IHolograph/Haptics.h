#pragma once


NAMESPACE_PARALLEL_BEGIN


namespace SpatialInputUtilities::Haptics {
	
// Creates a continuous haptic feedback on the given SpatialInteractionSource.
static inline void SendContinuousBuzzForDuration(
    const SpatialSource& source,
    const TimeSpan& playDuration,
    float intensity = 1.0f)
{
    if (const SpatialInteractionController controller = source.Controller())
    {
        if (const SimpleHapticsController hapticsController = controller.SimpleHapticsController())
        {
            // Find the continuous buzz haptic feedback.
            static const uint16 ContinuousBuzzWaveform = Holo::BuzzContinuous();
            const IVectorView<SimpleHapticsControllerFeedback> supportedFeedback = hapticsController.SupportedFeedback();
            auto continuousBuzz = std::find_if(
                begin(supportedFeedback),
                end(supportedFeedback),
                [](SimpleHapticsControllerFeedback const& sf) { return sf.Waveform() == ContinuousBuzzWaveform; });

            // Apply controller haptics
            if (continuousBuzz != end(supportedFeedback))
            {
                hapticsController.SendHapticFeedbackForDuration(*continuousBuzz, intensity, playDuration);
            }
        }
    }
}

}


NAMESPACE_PARALLEL_END
