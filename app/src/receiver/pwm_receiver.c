#include <device.h>
#include <drivers/pwm.h>
#include <logging/log.h>
#include <kernel.h>
#include <stdint.h>

LOG_MODULE_REGISTER(pwm_receiver, LOG_LEVEL_DBG);

#define PWM_RECEIVER_MAX_CHANNELS 6
#define PWM_RECEIVER_CAPTURE_TIMEOUT_MS 1000

struct pwm_receiver_channel_data {
    uint64_t duty_cycle;
    uint64_t period;
};

struct pwm_receiver_channel {
    const struct device *dev;
    uint8_t dev_channel;
    bool configured;
    struct pwm_receiver_channel_data data;
};

struct pwm_receiver_channel channels[PWM_RECEIVER_MAX_CHANNELS];

int pwm_receiver_config_channel(uint8_t channel, const struct device *dev, uint8_t dev_channel)
{
    if (channel >= PWM_RECEIVER_MAX_CHANNELS || !dev) {
        return -EINVAL;
    }
    channels[channel].dev = dev;
    channels[channel].dev_channel = dev_channel;
    channels[channel].configured = true;
    return 0;
}

static void capture_channel(uint8_t channel)
{
    struct pwm_receiver_channel current_channel = channels[channel];
    if (!current_channel.configured) {
        return;
    }
    pwm_capture_usec(
        current_channel.dev,
        current_channel.dev_channel,
        PWM_CAPTURE_TYPE_BOTH,
        &current_channel.data.period,
        &current_channel.data.duty_cycle,
        K_MSEC(PWM_RECEIVER_CAPTURE_TIMEOUT_MS)
    );
    LOG_DBG(
        "channel %d; duty_cycle %llu; period %llu",
        channel,
        current_channel.data.duty_cycle,
        current_channel.data.period
    );
}

void capture_all_channels(void)
{
    for (int i = 0; i < PWM_RECEIVER_MAX_CHANNELS; i++) {
        capture_channel(i);
    }
}
