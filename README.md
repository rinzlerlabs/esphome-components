# esphome-components

A set of custom ESPHome Components

## Components

### `priority_gpio`

A GPIO binary output with a **configurable setup priority**, allowing deterministic pin initialization order during ESP32 boot. This is useful when certain GPIO pins must be driven high or low before others during startup (e.g., enabling a power rail before a reset line is released).

#### Installation

```yaml
external_components:
  - source: github://rinzlerlabs/esphome-components@priority-gpio
    components: [priority_gpio]
```

#### Configuration

Used as an output platform — add entries under the `output:` key:

```yaml
output:
  - platform: priority_gpio
    id: power_enable
    pin: GPIO5
    priority: 1200.0    # Higher = runs earlier in boot

  - platform: priority_gpio
    id: reset_line
    pin:
      number: GPIO4
      inverted: true
    priority: 1100.0     # Runs after power_enable
```

#### Configuration Variables

| Variable | Required | Default | Description |
|---|---|---|---|
| `id` | **Yes** | — | Unique identifier for this output |
| `pin` | **Yes** | — | GPIO pin to control ([Pin Schema](https://esphome.io/guides/configuration-types.html#pin-schema)) |
| `priority` | No | `800.0` | Setup priority. **Higher values run earlier** during boot. Standard ESPHome priorities: `BUS` = 1000, `IO` = 900, `HARDWARE` = 800, `DATA` = 600, `PROCESSOR` = 400, `BLUETOOTH` = 350, `AFTER_BLUETOOTH` = 300, `WIFI`/`ETHERNET` = 250, `BEFORE_CONNECTION` = 220, `AFTER_WIFI` = 200, `AFTER_CONNECTION` = 100, `LATE` = -100 |
| `inverted` | No | `false` | Invert the output logic |
| `power_supply` | No | — | ID of a [Power Supply](https://esphome.io/components/power_supply.html) to automatically enable |

#### How Priority Works

ESPHome initializes components in descending order of their setup priority value. By assigning different `priority` values to each `priority_gpio` output, you control exactly which pins get configured first:

```yaml
output:
  # Step 1: Enable main power (priority 1100 - highest, runs before everything)
  - platform: priority_gpio
    id: main_power
    pin: GPIO5
    priority: 1200.0

  # Step 2: Enable 3.3V rail (priority 1100 - runs after main power, but before the bus setup code)
  - platform: priority_gpio
    id: rail_3v3
    pin: GPIO18
    priority: 1100.0
```
