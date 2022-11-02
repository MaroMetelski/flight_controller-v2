#ifndef _SRC_RECEIVER_PWM_RECEIVER_H
#define _SRC_RECEIVER_PWM_RECEIVER_H

#include <stdint.h>
#include <device.h>

/** Configure PWM device and channel to use by specific pwm_receiver channel.
 *
 * PWM capture functionality seems still quite dependent on underlying driver, so
 * allow to configure the channels manually.
 * This can be done by board-specific middle layer.
 */
int pwm_receiver_config_channel(uint8_t channel, const struct device *dev, uint8_t dev_channel);
void capture_all_channels(void);

#endif  // _SRC_RECEIVER_PWM_RECEIVER_H
