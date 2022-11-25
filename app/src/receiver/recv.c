#include <zephyr/drivers/pwm.h>
#include <zephyr/devicetree/pwms.h>

#define DT_DRV_COMPAT receiver_pwms

#define PWM_RECEIVER_NODE DT_DRV_INST(0)

struct pwm_dt_spec recv_pwm = PWM_DT_SPEC_GET(PWM_RECEIVER_NODE);
