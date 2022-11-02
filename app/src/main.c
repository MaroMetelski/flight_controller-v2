#include <kernel.h>
#include <device.h>
#include <drivers/gpio.h>
#include <drivers/pwm.h>
#include <logging/log.h>

#include "receiver/pwm_receiver.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

#define PWM3 DT_NODELABEL(pwm3)
static const struct device *pwm_in = DEVICE_DT_GET(PWM3);

void main(void)
{

    pwm_receiver_config_channel(0, pwm_in, 1);
    pwm_receiver_config_channel(1, pwm_in, 2);
    capture_all_channels();
    while (1) {
        // gpio_pin_toggle_dt(&led);
        k_sleep(K_MSEC(1000));
    }
}
