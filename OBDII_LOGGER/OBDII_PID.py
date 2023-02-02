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
    A=msg.data[3]
    B=msg.data[4]
    pid=msg.data[PID_INDEX] 
    if pid > 0x5f:
        print("Unknown PID:"+pid)
        return   
    else:
        return ((A * 256.0 + B) / 4.0)
    # match msg.data[PID_INDEX]:
    #     case PIDS_SUPPORT_01_20: // raw
    #     case MONITOR_STATUS_SINCE_DTCS_CLEARED: // raw
    #     case FREEZE_DTC: // raw
    #     case PIDS_SUPPORT_21_40: // raw
    #     case PIDS_SUPPORT_41_60: // raw
    #     case MONITOR_STATUS_THIS_DRIVE_CYCLE: // raw
    #     #return value can lose precision!
    #         return ((uint32_t)A << 24 | (uint32_t)B << 16 | (uint32_t)C << 8 | (uint32_t)D)

    #     case FUEL_SYSTEM_STATUS: // raw
    #     case RUN_TIME_SINCE_ENGINE_START:
    #     case DISTANCE_TRAVELED_WITH_MIL_ON:
    #     case DISTANCE_TRAVELED_SINCE_CODES_CLEARED:
    #     case TIME_RUN_WITH_MIL_ON:
    #     case TIME_SINCE_TROUBLE_CODES_CLEARED:
    #         return (A * 256.0 + B)

    #     case CALCULATED_ENGINE_LOAD:
    #     case THROTTLE_POSITION:
    #     case COMMANDED_EGR:
    #     case COMMANDED_EVAPORATIVE_PURGE:
    #     case FUEL_TANK_LEVEL_INPUT:
    #     case RELATIVE_THROTTLE_POSITION:
    #     case ABSOLUTE_THROTTLE_POSITION_B:
    #     case ABSOLUTE_THROTTLE_POSITION_C:
    #     case ABSOLUTE_THROTTLE_POSITION_D:
    #     case ABSOLUTE_THROTTLE_POSITION_E:
    #     case ABSOLUTE_THROTTLE_POSITION_F:
    #     case COMMANDED_THROTTLE_ACTUATOR:
    #     case ETHANOL_FUEL_PERCENTAGE:
    #     case RELATIVE_ACCELERATOR_PEDAL_POSITTION:
    #     case HYBRID_BATTERY_PACK_REMAINING_LIFE:
    #         return (A / 2.55)

    #     case COMMANDED_SECONDARY_AIR_STATUS: // raw
    #     case OBD_STANDARDS_THIS_VEHICLE_CONFORMS_TO: // raw
    #     case OXYGEN_SENSORS_PRESENT_IN_2_BANKS: // raw
    #     case OXYGEN_SENSORS_PRESENT_IN_4_BANKS: // raw
    #     case AUXILIARY_INPUT_STATUS: // raw
    #     case FUEL_TYPE: // raw
    #     case EMISSION_REQUIREMENT_TO_WHICH_VEHICLE_IS_DESIGNED: // raw
    #         return (A)

    #     case OXYGEN_SENSOR_1_SHORT_TERM_FUEL_TRIM:
    #     case OXYGEN_SENSOR_2_SHORT_TERM_FUEL_TRIM:
    #     case OXYGEN_SENSOR_3_SHORT_TERM_FUEL_TRIM:
    #     case OXYGEN_SENSOR_4_SHORT_TERM_FUEL_TRIM:
    #     case OXYGEN_SENSOR_5_SHORT_TERM_FUEL_TRIM:
    #     case OXYGEN_SENSOR_6_SHORT_TERM_FUEL_TRIM:
    #     case OXYGEN_SENSOR_7_SHORT_TERM_FUEL_TRIM:
    #     case OXYGEN_SENSOR_8_SHORT_TERM_FUEL_TRIM:
    #         return ((B / 1.28) - 100.0)
    #     break

    #     case ENGINE_COOLANT_TEMPERATURE:
    #     case AIR_INTAKE_TEMPERATURE:
    #     case AMBIENT_AIR_TEMPERATURE:
    #     case ENGINE_OIL_TEMPERATURE:
    #         return (A - 40.0)

    #     case SHORT_TERM_FUEL_TRIM_BANK_1:
    #     case LONG_TERM_FUEL_TRIM_BANK_1:
    #     case SHORT_TERM_FUEL_TRIM_BANK_2:
    #     case LONG_TERM_FUEL_TRIM_BANK_2:
    #     case EGR_ERROR:
    #         return ((A / 1.28) - 100.0)

    #     case FUEL_PRESSURE:
    #         return (A * 3.0)

    #     case INTAKE_MANIFOLD_ABSOLUTE_PRESSURE:
    #     case VEHICLE_SPEED:
    #     case WARM_UPS_SINCE_CODES_CLEARED:
    #     case ABSOLULTE_BAROMETRIC_PRESSURE:
    #         return (A)

    #     case ENGINE_RPM:
    #         return ((A * 256.0 + B) / 4.0)

    #     case TIMING_ADVANCE:
    #         return ((A / 2.0) - 64.0)

    #     case MAF_AIR_FLOW_RATE:
    #         return ((A * 256.0 + B) / 100.0)

    #     case FUEL_RAIL_PRESSURE:
    #         return ((A * 256.0 + B) * 0.079)

    #     case FUEL_RAIL_GAUGE_PRESSURE:
    #     case FUEL_RAIL_ABSOLUTE_PRESSURE:
    #         return ((A * 256.0 + B) * 10.0)

    #     case OXYGEN_SENSOR_1_FUEL_AIR_EQUIVALENCE_RATIO:
    #     case OXYGEN_SENSOR_2_FUEL_AIR_EQUIVALENCE_RATIO:
    #     case OXYGEN_SENSOR_3_FUEL_AIR_EQUIVALENCE_RATIO:
    #     case OXYGEN_SENSOR_4_FUEL_AIR_EQUIVALENCE_RATIO:
    #     case OXYGEN_SENSOR_5_FUEL_AIR_EQUIVALENCE_RATIO:
    #     case OXYGEN_SENSOR_6_FUEL_AIR_EQUIVALENCE_RATIO:
    #     case OXYGEN_SENSOR_7_FUEL_AIR_EQUIVALENCE_RATIO:
    #     case OXYGEN_SENSOR_8_FUEL_AIR_EQUIVALENCE_RATIO:
    #     case 0x34:
    #     case 0x35:
    #     case 0x36:
    #     case 0x37:
    #     case 0x38:
    #     case 0x39:
    #     case 0x3a:
    #     case 0x3b:
    #         return (((A * 256.0 + B) * 2.0) / 65536.0)

    #     case EVAP_SYSTEM_VAPOR_PRESSURE:
    #         return (((int16_t)(A * 256.0 + B)) / 4.0)

    #     case CATALYST_TEMPERATURE_BANK_1_SENSOR_1:
    #     case CATALYST_TEMPERATURE_BANK_2_SENSOR_1:
    #     case CATALYST_TEMPERATURE_BANK_1_SENSOR_2:
    #     case CATALYST_TEMPERATURE_BANK_2_SENSOR_2:
    #         return (((A * 256.0 + B) / 10.0) - 40.0)

    #     case CONTROL_MODULE_VOLTAGE:
    #         return ((A * 256.0 + B) / 1000.0)

    #     case ABSOLUTE_LOAD_VALUE:
    #         return ((A * 256.0 + B) / 2.55)

    #     case FUEL_AIR_COMMANDED_EQUIVALENCE_RATE:
    #         return (2.0 * (A * 256.0 + B) / 65536.0)

    #     case ABSOLUTE_EVAP_SYSTEM_VAPOR_PRESSURE:
    #         return ((A * 256.0 + B) / 200.0)

    #     case 0x54:
    #         return ((A * 256.0 + B) - 32767.0)

    #     case FUEL_INJECTION_TIMING:
    #         return (((A * 256.0 + B) / 128.0) - 210.0)

    #     case ENGINE_FUEL_RATE:
    #         return ((A * 256.0 + B) / 20.0)

    #     case _:
    #         return ((uint32_t)A << 24 | (uint32_t)B << 16 | (uint32_t)C << 8 | (uint32_t)D)