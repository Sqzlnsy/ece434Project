PIDS_SUPPORT_01_20                                = 0x00
MONITOR_STATUS_SINCE_DTCS_CLEARED                 = 0x01
FREEZE_DTC                                        = 0x02
FUEL_SYSTEM_STATUS                                = 0x03
CALCULATED_ENGINE_LOAD                            = 0x04
ENGINE_COOLANT_TEMPERATURE                        = 0x05
SHORT_TERM_FUEL_TRIM_BANK_1                       = 0x06
LONG_TERM_FUEL_TRIM_BANK_1                        = 0x07
SHORT_TERM_FUEL_TRIM_BANK_2                       = 0x08
LONG_TERM_FUEL_TRIM_BANK_2                        = 0x09
FUEL_PRESSURE                                     = 0x0a
INTAKE_MANIFOLD_ABSOLUTE_PRESSURE                 = 0x0b
ENGINE_RPM                                        = 0x0c
VEHICLE_SPEED                                     = 0x0d
TIMING_ADVANCE                                    = 0x0e
AIR_INTAKE_TEMPERATURE                            = 0x0f
MAF_AIR_FLOW_RATE                                 = 0x10
THROTTLE_POSITION                                 = 0x11
COMMANDED_SECONDARY_AIR_STATUS                    = 0x12
OXYGEN_SENSORS_PRESENT_IN_2_BANKS                 = 0x13
OXYGEN_SENSOR_1_SHORT_TERM_FUEL_TRIM              = 0x14
OXYGEN_SENSOR_2_SHORT_TERM_FUEL_TRIM              = 0x15
OXYGEN_SENSOR_3_SHORT_TERM_FUEL_TRIM              = 0x16
OXYGEN_SENSOR_4_SHORT_TERM_FUEL_TRIM              = 0x17
OXYGEN_SENSOR_5_SHORT_TERM_FUEL_TRIM              = 0x18
OXYGEN_SENSOR_6_SHORT_TERM_FUEL_TRIM              = 0x19
OXYGEN_SENSOR_7_SHORT_TERM_FUEL_TRIM              = 0x1a
OXYGEN_SENSOR_8_SHORT_TERM_FUEL_TRIM              = 0x1b
OBD_STANDARDS_THIS_VEHICLE_CONFORMS_TO            = 0x1c
OXYGEN_SENSORS_PRESENT_IN_4_BANKS                 = 0x1d
AUXILIARY_INPUT_STATUS                            = 0x1e
RUN_TIME_SINCE_ENGINE_START                       = 0x1f
PIDS_SUPPORT_21_40                                = 0x20
DISTANCE_TRAVELED_WITH_MIL_ON                     = 0x21
FUEL_RAIL_PRESSURE                                = 0x22
FUEL_RAIL_GAUGE_PRESSURE                          = 0x23
OXYGEN_SENSOR_1_FUEL_AIR_EQUIVALENCE_RATIO        = 0x24
OXYGEN_SENSOR_2_FUEL_AIR_EQUIVALENCE_RATIO        = 0x25
OXYGEN_SENSOR_3_FUEL_AIR_EQUIVALENCE_RATIO        = 0x26
OXYGEN_SENSOR_4_FUEL_AIR_EQUIVALENCE_RATIO        = 0x27
OXYGEN_SENSOR_5_FUEL_AIR_EQUIVALENCE_RATIO        = 0x28
OXYGEN_SENSOR_6_FUEL_AIR_EQUIVALENCE_RATIO        = 0x29
OXYGEN_SENSOR_7_FUEL_AIR_EQUIVALENCE_RATIO        = 0x2a
OXYGEN_SENSOR_8_FUEL_AIR_EQUIVALENCE_RATIO        = 0x2b
COMMANDED_EGR                                     = 0x2c
EGR_ERROR                                         = 0x2d
COMMANDED_EVAPORATIVE_PURGE                       = 0x2e
FUEL_TANK_LEVEL_INPUT                             = 0x2f
WARM_UPS_SINCE_CODES_CLEARED                      = 0x30
DISTANCE_TRAVELED_SINCE_CODES_CLEARED             = 0x31
EVAP_SYSTEM_VAPOR_PRESSURE                        = 0x32
ABSOLULTE_BAROMETRIC_PRESSURE                     = 0x33
# /*OXYGEN_SENSOR_1_FUEL_AIR_EQUIVALENCE_RATIO        = 0x34
#   OXYGEN_SENSOR_2_FUEL_AIR_EQUIVALENCE_RATIO        = 0x35
#   OXYGEN_SENSOR_3_FUEL_AIR_EQUIVALENCE_RATIO        = 0x36
#   OXYGEN_SENSOR_4_FUEL_AIR_EQUIVALENCE_RATIO        = 0x37
#   OXYGEN_SENSOR_5_FUEL_AIR_EQUIVALENCE_RATIO        = 0x38
#   OXYGEN_SENSOR_6_FUEL_AIR_EQUIVALENCE_RATIO        = 0x39
#   OXYGEN_SENSOR_7_FUEL_AIR_EQUIVALENCE_RATIO        = 0x3a
#   OXYGEN_SENSOR_8_FUEL_AIR_EQUIVALENCE_RATIO        = 0x3b*/
CATALYST_TEMPERATURE_BANK_1_SENSOR_1              = 0x3c
CATALYST_TEMPERATURE_BANK_2_SENSOR_1              = 0x3d
CATALYST_TEMPERATURE_BANK_1_SENSOR_2              = 0x3e
CATALYST_TEMPERATURE_BANK_2_SENSOR_2              = 0x3f

PIDS_SUPPORT_41_60                                = 0x40
MONITOR_STATUS_THIS_DRIVE_CYCLE                   = 0x41
CONTROL_MODULE_VOLTAGE                            = 0x42
ABSOLUTE_LOAD_VALUE                               = 0x43
FUEL_AIR_COMMANDED_EQUIVALENCE_RATE               = 0x44
RELATIVE_THROTTLE_POSITION                        = 0x45
AMBIENT_AIR_TEMPERATURE                           = 0x46
ABSOLUTE_THROTTLE_POSITION_B                      = 0x47
ABSOLUTE_THROTTLE_POSITION_C                      = 0x48
ABSOLUTE_THROTTLE_POSITION_D                      = 0x49
ABSOLUTE_THROTTLE_POSITION_E                      = 0x4a
ABSOLUTE_THROTTLE_POSITION_F                      = 0x4b
COMMANDED_THROTTLE_ACTUATOR                       = 0x4c
TIME_RUN_WITH_MIL_ON                              = 0x4d
TIME_SINCE_TROUBLE_CODES_CLEARED                  = 0x4e
#                                                   = 0x4f
#                                                   = 0x50
FUEL_TYPE                                         = 0x51
ETHANOL_FUEL_PERCENTAGE                           = 0x52
ABSOLUTE_EVAP_SYSTEM_VAPOR_PRESSURE               = 0x53
# /*EVAP_SYSTEM_VAPOR_PRESSURE                        = 0x54,*/
# /*                                                  = 0x55,
#                                                     = 0x56,
#                                                     = 0x57,
#                                                     = 0x58,*/
FUEL_RAIL_ABSOLUTE_PRESSURE                       = 0x59
RELATIVE_ACCELERATOR_PEDAL_POSITTION              = 0x5a
HYBRID_BATTERY_PACK_REMAINING_LIFE                = 0x5b
ENGINE_OIL_TEMPERATURE                            = 0x5c
FUEL_INJECTION_TIMING                             = 0x5d
ENGINE_FUEL_RATE                                  = 0x5e
EMISSION_REQUIREMENT_TO_WHICH_VEHICLE_IS_DESIGNED = 0x5f

PID_INDEX = 2

def OBDII_reader(msg):
    try:
        A = msg.data[3]
    except IndexError:
        A = 'null'
    try:
        B = msg.data[4]
    except IndexError:
        B = 'null'
    try:
        C = msg.data[5]
    except IndexError:
        C = 'null'
    try:
        D = msg.data[6]
    except IndexError:
        D = 'null'

    pid=msg.data[PID_INDEX] 
    if pid > 0x5f:
        print("Unknown PID:"+pid)
        return   
    #else:
    #   return ((A * 256.0 + B) / 4.0)
    if msg.data[PID_INDEX] in [PID_SUPPORT_01_20, MONITOR_STATUS_SINCE_DTCS_CLEARED, 
                               FREEZE_DTC, PID_SUPPORT_21_40, PID_SUPPORT_41_60, 
                               MONITOR_STATUS_THIS_DRIVE_CYCLE]:
        # return value can lose precision
        return (A << 24) | (B << 16) | (C << 8) | D
    elif msg.data[PID_INDEX] in [FUEL_SYSTEM_STATUS, RUN_TIME_SINCE_ENGINE_START, 
                                 DISTANCE_TRAVELED_WITH_MIL_ON, DISTANCE_TRAVELED_SINCE_CODES_CLEARED, 
                                 TIME_RUN_WITH_MIL_ON, TIME_SINCE_TROUBLE_CODES_CLEARED]:
        return A * 256.0 + B
    elif msg.data[PID_INDEX] in [CALCULATED_ENGINE_LOAD, THROTTLE_POSITION, COMMANDED_EGR, 
                                 COMMANDED_EVAPORATIVE_PURGE, FUEL_TANK_LEVEL_INPUT, 
                                 RELATIVE_THROTTLE_POSITION, ABSOLUTE_THROTTLE_POSITION_B, 
                                 ABSOLUTE_THROTTLE_POSITION_C, ABSOLUTE_THROTTLE_POSITION_D, 
                                 ABSOLUTE_THROTTLE_POSITION_E, ABSOLUTE_THROTTLE_POSITION_F, 
                                 COMMANDED_THROTTLE_ACTUATOR, ETHANOL_FUEL_PERCENTAGE, 
                                 RELATIVE_ACCELERATOR_PEDAL_POSITTION, HYBRID_BATTERY_PACK_REMAINING_LIFE]:
        return A / 2.55
    elif msg.data[PID_INDEX] in [COMMANDED_SECONDARY_AIR_STATUS, OBD_STANDARDS_THIS_VEHICLE_CONFORMS_TO, 
                                 OXYGEN_SENSORS_PRESENT_IN_2_BANKS, OXYGEN_SENSORS_PRESENT_IN_4_BANKS, 
                                 AUXILIARY_INPUT_STATUS, FUEL_TYPE, 
                                 EMISSION_REQUIREMENT_TO_WHICH_VEHICLE_IS_DESIGNED]:
        return A
    elif msg.data[PID_INDEX] in [OXYGEN_SENSOR_1_SHORT_TERM_FUEL_TRIM, 
                                OXYGEN_SENSOR_2_SHORT_TERM_FUEL_TRIM, 
                                OXYGEN_SENSOR_3_SHORT_TERM_FUEL_TRIM, 
                                OXYGEN_SENSOR_4_SHORT_TERM_FUEL_TRIM, 
                                OXYGEN_SENSOR_5_SHORT_TERM_FUEL_TRIM, 
                                OXYGEN_SENSOR_6_SHORT_TERM_FUEL_TRIM, 
                                OXYGEN_SENSOR_7_SHORT_TERM_FUEL_TRIM, 
                                OXYGEN_SENSOR_8_SHORT_TERM_FUEL_TRIM]:
        return ((B / 1.28) - 100.0)
    
    elif msg.data[PID_INDEX] in [ENGINE_COOLANT_TEMPERATURE, 
                                  AIR_INTAKE_TEMPERATURE, 
                                  AMBIENT_AIR_TEMPERATURE, 
                                  ENGINE_OIL_TEMPERATURE]:
        return (A - 40.0)
    
    elif msg.data[PID_INDEX] in [SHORT_TERM_FUEL_TRIM_BANK_1, 
                                  LONG_TERM_FUEL_TRIM_BANK_1, 
                                  SHORT_TERM_FUEL_TRIM_BANK_2, 
                                  LONG_TERM_FUEL_TRIM_BANK_2, 
                                  EGR_ERROR]:
        return ((A / 1.28) - 100.0)
    
    elif msg.data[PID_INDEX] == FUEL_PRESSURE:
        return (A * 3.0)
    
    elif msg.data[PID_INDEX] in [INTAKE_MANIFOLD_ABSOLUTE_PRESSURE, 
                                  VEHICLE_SPEED, 
                                  WARM_UPS_SINCE_CODES_CLEARED, 
                                  ABSOLULTE_BAROMETRIC_PRESSURE]:
        return (A)
    
    elif msg.data[PID_INDEX] == ENGINE_RPM:
        return ((A * 256.0 + B) / 4.0)
    
    elif msg.data[PID_INDEX] == TIMING_ADVANCE:
        return ((A / 2.0) - 64.0)
    
    elif msg.data[PID_INDEX] == MAF_AIR_FLOW_RATE:
        return ((A * 256.0 + B) / 100.0)
    
    elif msg.data[PID_INDEX] == FUEL_RAIL_PRESSURE:
        return ((A * 256.0 + B) * 0.079)
    elif msg.data[PID_INDEX] in [FUEL_RAIL_GAUGE_PRESSURE, FUEL_RAIL_ABSOLUTE_PRESSURE]:
        return ((A * 256.0 + B) * 10.0)
    elif msg.data[PID_INDEX] in [OXYGEN_SENSOR_1_FUEL_AIR_EQUIVALENCE_RATIO, 
                                OXYGEN_SENSOR_2_FUEL_AIR_EQUIVALENCE_RATIO,
                                OXYGEN_SENSOR_3_FUEL_AIR_EQUIVALENCE_RATIO,
                                OXYGEN_SENSOR_4_FUEL_AIR_EQUIVALENCE_RATIO,
                                OXYGEN_SENSOR_5_FUEL_AIR_EQUIVALENCE_RATIO,
                                OXYGEN_SENSOR_6_FUEL_AIR_EQUIVALENCE_RATIO,
                                OXYGEN_SENSOR_7_FUEL_AIR_EQUIVALENCE_RATIO,
                                OXYGEN_SENSOR_8_FUEL_AIR_EQUIVALENCE_RATIO,
                                0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b]:
        return (((A * 256.0 + B) * 2.0) / 65536.0)
    elif msg.data[PID_INDEX] == EVAP_SYSTEM_VAPOR_PRESSURE:
        return (((int16_t)(A * 256.0 + B)) / 4.0)
    elif msg.data[PID_INDEX] in [CATALYST_TEMPERATURE_BANK_1_SENSOR_1, 
                                CATALYST_TEMPERATURE_BANK_2_SENSOR_1,
                                CATALYST_TEMPERATURE_BANK_1_SENSOR_2,
                                CATALYST_TEMPERATURE_BANK_2_SENSOR_2]:
        return (((A * 256.0 + B) / 10.0) - 40.0)
    elif msg.data[PID_INDEX] == CONTROL_MODULE_VOLTAGE:
        return ((A * 256.0 + B) / 1000.0)
    elif msg.data[PID_INDEX] == ABSOLUTE_LOAD_VALUE:
        return ((A * 256.0 + B) / 2.55)
    elif msg.data[PID_INDEX] == FUEL_AIR_COMMANDED_EQUIVALENCE_RATE:
        return (2.0 * (A * 256.0 + B) / 65536.0)
    elif msg.data[PID_INDEX] == ABSOLUTE_EVAP_SYSTEM_VAPOR_PRESSURE:
        return ((A * 256.0 + B) / 200.0)
    elif msg.data[PID_INDEX] == 0x54:
        return ((A * 256.0 + B) - 32767.0)
    elif msg.data[PID_INDEX] == FUEL_INJECTION_TIMING:
        return (((A * 256.0 + B) / 128.0) - 210.0)
    elif msg.data[PID_INDEX] == ENGINE_FUEL_RATE:
            return ((A * 256.0 + B) / 20.0)
    else:
        return (A << 24 | B << 16 | C << 8 | D)
