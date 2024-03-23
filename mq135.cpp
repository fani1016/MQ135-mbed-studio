#include "mq135.hpp"


float ResistanceCalculation(int raw_adc) {
    return (((float)RL_VALUE * (1023 - raw_adc) / raw_adc));
}

float SensorCalibration(int mq, int raw_adc) {
    float val = 0;

    for (int i = 0; i < 50; i++) { //take multiple samples and calculate the average value
        val += ResistanceCalculation(raw_adc);
        DELAY_ms(50);
    }
    val = val / 50;
    val = val/MQ135_RO_CLEAN_AIR_FACTOR;       //divided by RO_CLEAN_AIR_FACTOR yields the Ro  according to the chart in the datasheet

    return val;
}

float ReadSensor(int mq, int raw_adc) {
    float rs = 0;

    for (int i = 0; i < 25; i++) { // take multiple readings and average it.
        rs += ResistanceCalculation(raw_adc);
        DELAY_ms(50);
    }

    rs = rs / 25;

    return rs;
}

int GetPercentage(float rs_ro_ratio, GasCurve curve) {
    return (pow(10, (((log(rs_ro_ratio) - curve.y) / curve.slope) + curve.x)));
}

int GetGasPercentage(float rs_ro_ratio, GasType gas_id) {
    return GetPercentage(rs_ro_ratio, sensors[gas_id].curve);
}


