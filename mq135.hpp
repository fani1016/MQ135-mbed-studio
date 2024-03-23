#ifndef MQ135_HPP
#define MQ135_HPP

#include <cmath>

#define RL_VALUE (10) //define the load resistance on the board, in kilo ohms
#define RO_CLEAN_AIR_FACTOR (9.83)  //(Sensor resistance in clean air)/RO, which is derived from the chart in datasheet
#define MQ135_RO_CLEAN_AIR_FACTOR (3.67)  //(Sensor resistance in clean air)/RO, which is derived from the chart in datasheet

struct GasCurve {
    float x;
    float y;
    float slope;
};

enum GasType {
    LPG = 0,
    CO2,
    NH3
};

struct GasSensor {
    GasCurve curve;
    float ro_clean_air_factor;
};

GasSensor sensors[] = {
    {{2.3, 0.20, -0.45}, 9.83},    // LPG
    {{1, 0.06, -0.123}, 3.67},     // CO2
    {{1, 0.68, -0.58}, 3.67}       // NH3
};

float LPGCurve[3]  = {2.3,0.20,-0.45};   //two points from LPG curve are taken point1:(200,1.6) point2(10000,0.26)
                                                    //take log of each point (lg200, lg 1.6)=(2.3,0.20)  (lg10000,lg0.26)=(4,-0.58)
                                                    //find the slope using these points. take point1 as reference
                                                    //data format:{ x, y, slope};
float Co2Curve[3]  = {1,0.06,-0.123};
float NH3Curve[3] ={1,0.68,-0.58};

float Ro_MQ135 = 10; // Ro is initialized to 10 kilo ohms

int GetGasPercentage(float rs_ro_ratio, GasType gas_id);
int GetPercentage(float rs_ro_ratio, GasCurve curve);
float ReadSensor(int mq, int raw_adc);
float SensorCalibration(int mq, int raw_adc);
float ResistanceCalculation(int raw_adc);

#endif // MQ135_HPP
