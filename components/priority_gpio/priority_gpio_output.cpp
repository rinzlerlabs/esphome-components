#include "priority_gpio_output.h"
#include "esphome/core/log.h"

namespace esphome {
namespace priority_gpio {

static const char *const TAG = "priority_gpio.output";

void PriorityGPIOBinaryOutput::dump_config() {
  ESP_LOGCONFIG(TAG, "Priority GPIO Binary Output:");
  LOG_PIN("  Pin: ", this->pin_);
  ESP_LOGCONFIG(TAG, "  Setup Priority: %.1f", this->priority_);
  LOG_BINARY_OUTPUT(this);
}

}  // namespace priority_gpio
}  // namespace esphome
