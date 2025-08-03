

#include "quantum.h"
#include "i2c_master.h"
#include "custom60.h"

// PCF8575 registers
#define PCF8575_INPUT_REG 0x00
#define PCF8575_OUTPUT_REG 0x02

// Matrix state
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t raw_matrix[MATRIX_ROWS];

#define I2C_TIMEOUT 100

// Helper to read from a PCF8575 expander
static uint16_t pcf8575_read_port(uint8_t addr) {
    uint8_t data[2];
    if (i2c_receive(addr << 1, data, 2, I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
        return 0xFFFF; // Return all high on error
    }
    return (data[1] << 8) | data[0];
}

// Helper to write to a PCF8575 expander
static void pcf8575_write_port(uint8_t addr, uint16_t data) {
    uint8_t buffer[2] = {data & 0xFF, (data >> 8) & 0xFF};
    i2c_transmit(addr << 1, buffer, 2, I2C_TIMEOUT);
}

// Initialize I2C and PCF8575 expanders
void matrix_init_custom(void) {
    // Initialize I2C
    i2c_init();

    // Initialize PCF8575 devices
    // Set all pins as inputs with pull-ups (0xFFFF)
    pcf8575_write_port(PCF8575_MAIN_ADDR, 0xFFFF);
    pcf8575_write_port(PCF8575_NUMPAD_ADDR, 0xFFFF);

    // Initialize matrix state
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i]     = 0;
        raw_matrix[i] = 0;
    }

// Set up interrupt pins if connected
#ifdef PCF8575_MAIN_INT_PIN
    setPinInputHigh(PCF8575_MAIN_INT_PIN);
#endif
#ifdef PCF8575_NUMPAD_INT_PIN
    setPinInputHigh(PCF8575_NUMPAD_INT_PIN);
#endif
}

// Scan matrix using both PCF8575 expanders
// The physical matrix is split:
// - Main expander (8x8): Mapped to logical matrix columns 0-7
// - Numpad expander (5x4): Mapped to logical matrix columns 8-11
bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    // Optional: Check interrupt pins before scanning
    bool should_scan = true;
#ifdef PCF8575_MAIN_INT_PIN
    should_scan = !readPin(PCF8575_MAIN_INT_PIN);
#endif
#ifdef PCF8575_NUMPAD_INT_PIN
    should_scan |= !readPin(PCF8575_NUMPAD_INT_PIN);
#endif

    if (should_scan) {
        // Clear raw matrix state
        for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
            raw_matrix[i] = 0;
        }

        // --- Scan main keyboard (8x8 matrix on PCF8575_MAIN_ADDR) ---
        // It uses P10-P17 as rows and P0-P7 as columns, but we only need 5 rows
        // for our logical matrix.
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            // Map to physical row
            uint8_t physical_row = 8 + row;  // P10-P14 (only using first 5 of the 8 rows)
            
            // Drive current row LOW on main PCF8575 (bits 8-15 = P10-P17)
            uint16_t main_row_mask = 0xFFFF & ~(1 << physical_row);
            pcf8575_write_port(PCF8575_MAIN_ADDR, main_row_mask);
            wait_us(30); // Delay for signal to settle

            // Read columns from main PCF8575 (bits 0-7 = P0-P7)
            uint16_t main_data = pcf8575_read_port(PCF8575_MAIN_ADDR);

            // Process main keyboard columns 0-7, map to logical columns 0-7
            for (uint8_t col = 0; col < 8; col++) {
                if (!(main_data & (1 << col))) {
                    raw_matrix[row] |= (1UL << col);
                }
            }
            
            // For logical columns 12-17, we currently have no physical pins
            // so we just leave those bits unset (no keys will be detected there)
        }

        // --- Scan numpad (5x4 matrix on PCF8575_NUMPAD_ADDR) ---
        // It uses P4,P5,P6,P7,P10 as rows and P0-P3 as columns.
        // We will map these to columns 14-17 in the logical matrix for the numpad
        const uint8_t numpad_row_pins[] = {4, 5, 6, 7, 8}; // P4,P5,P6,P7,P10
        
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            // Get the physical row pin number
            uint8_t physical_row = numpad_row_pins[row];

            // Drive current numpad row LOW
            uint16_t numpad_row_mask = 0xFFFF & ~(1 << physical_row);
            pcf8575_write_port(PCF8575_NUMPAD_ADDR, numpad_row_mask);
            wait_us(30); // Delay

            // Read numpad columns (bits 0-3 = P0-P3)
            uint16_t numpad_data = pcf8575_read_port(PCF8575_NUMPAD_ADDR);

            // Process numpad columns 0-3, map to logical columns 14-17
            // This leaves logical columns 8-13 unused (they'll be all zeros)
            for (uint8_t numpad_col = 0; numpad_col < 4; numpad_col++) {
                if (!(numpad_data & (1 << numpad_col))) {
                    raw_matrix[row] |= (1UL << (14 + numpad_col));
                }
            }
        }

        // Set all pins high again (idle state)
        pcf8575_write_port(PCF8575_MAIN_ADDR, 0xFFFF);
        pcf8575_write_port(PCF8575_NUMPAD_ADDR, 0xFFFF);
    }

    // Check for changes and update current_matrix
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (current_matrix[i] != raw_matrix[i]) {
            current_matrix[i] = raw_matrix[i];
            changed = true;
        }
    }

    return changed;
}
