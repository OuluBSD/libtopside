#include "IHolograph.h"

NAMESPACE_PARALLEL_BEGIN

/*namespace SpatialInputUtilities::Haptics {
	
// Creates a continuous haptic feedback on the given SpatialInteractionSource.
static inline void SendContinuousBuzzForDuration(
    const SpatialSource& source,
    const TimeSpan& play_duration,
    float intensity = 1.0f)
{
    if (const SpatialInteractionController controller = source.Controller())
    {
        if (const SimpleHapticsController haptics_controller = controller.SimpleHapticsController())
        {
            // Find the continuous buzz haptic feedback.
            static const uint16 ContinuousBuzzWaveform = Holo::BuzzContinuous();
            const IVectorView<SimpleHapticsControllerFeedback> supported_feedback = haptics_controller.SupportedFeedback();
            auto continuous_buzz = std::find_if(
                begin(supported_feedback),
                end(supported_feedback),
                [](const SimpleHapticsControllerFeedback& sf) { return sf.Waveform() == ContinuousBuzzWaveform; });

            // Apply controller haptics
            if (continuous_buzz != end(supported_feedback)) {
                haptics_controller.SendHapticFeedbackForDuration(*continuous_buzz, intensity, play_duration);
            }
        }
    }
}

}*/

NAMESPACE_PARALLEL_END
