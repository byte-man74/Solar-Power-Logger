# Voltage and Current Monitor

This Arduino code, using a LiquidCrystal display, monitors input voltage and power. The circuit connects the LCD and a 10K resistor to specific Arduino pins. Key parameters:

- **Voltage Configuration:**
  - `input_voltage`
  - `r1` and `r2` (resistor values)

- **Current Configuration:**
  - `input_current`

## Functions

- `update_input_voltage()`: Reads and updates input voltage.
- `update_input_current()`: Placeholder for updating input current.

## Main Loop

1. **Voltage Display:**
   - Reads and displays input voltage.
   - 2-second delay.

2. **Current Display:**
   - Placeholder.
   - Displays current.
   - 2-second delay.

3. **Power Display:**
   - Calculates power.
   - Displays power.
   - 3-second delay.

The loop continuously monitors and displays voltage, current, and power on the LCD. Note: Current display functionality is a placeholder.
