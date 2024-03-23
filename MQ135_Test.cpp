
#include "mbed.h"
#include "mq135.hpp"

AnalogIn mq135Pin(A0); // Analog input

char text[5];
int LPG_Conc = 0;
int CO2_Conc = 0;
int NH3_Conc = 0;

int main() {
    // Read the raw ADC value from the sensor
    float raw_adc = mq135Pin.read() * 1023.0;

    // Initialize calibration
    printf("Calibrating...\r\n");
    Ro_MQ135 = SensorCalibration(raw_adc); // Calibrate sensor
    printf("Calibration is done...\r\n\r\n");

    while(1) {
        raw_adc = mq135Pin.read() * 1023.0;
        float rs_ro_ratio = ReadSensor(raw_adc) / Ro_MQ135; // Read sensor value
        CO2_Conc = fabs(GetGasPercentage(rs_ro_ratio, CO2));
        if (CO2_Conc > 10000)   CO2_Conc = 10000;
        NH3_Conc = fabs(GetGasPercentage(rs_ro_ratio, NH3));
        if (NH3_Conc > 10000)   NH3_Conc = 10000;


        // Print results
        printf("CO2: %05d ppm  |  NH3: %05d ppm\r\n", CO2_Conc, NH3_Conc);

        wait(1); // Delay for 1 second
    }
}
