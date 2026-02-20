#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/output/binary_output.h"

namespace esphome {
namespace priority_gpio {

/// A GPIO binary output with configurable setup priority for deterministic boot ordering.
class PriorityGPIOBinaryOutput : public output::BinaryOutput, public Component {
 public:
  void set_pin(GPIOPin *pin) { this->pin_ = pin; }

  /// Set the setup priority. Higher values run earlier during boot.
  void set_priority(float priority) { this->priority_ = priority; }

  /// Set the initial state of the pin on boot (true = HIGH, false = LOW).
  void set_initial_state(bool initial_state) { this->initial_state_ = initial_state; }

  void setup() override {
    this->pin_->setup();
    if (this->initial_state_) {
      this->turn_on();
    } else {
      this->turn_off();
    }
  }

  void dump_config() override;

  /// Returns the user-configured priority (default: HARDWARE = 800.0).
  float get_setup_priority() const override { return this->priority_; }

 protected:
  void write_state(bool state) override { this->pin_->digital_write(state); }

  GPIOPin *pin_;
  float priority_{800.0f};  // Default: setup_priority::HARDWARE
  bool initial_state_{false};
};

}  // namespace priority_gpio
}  // namespace esphome
