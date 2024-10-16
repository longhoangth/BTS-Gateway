/**
 * @file register.h
 * @author long (longzil193@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#ifndef _REGISTER_H_
#define _REGISTER_H_

#include "main.h"

#define CURRENT_UNIT            "A"
#define CURRENT_HOUR_UNIT       "Ah"
#define VOLTAGE_UNIT            "V"
#define PERCENTAGE_UNIT         "%"
#define DEGREES_UNIT            "°C"
#define INTEGER_UNIT            "int"
#define STRING_UNIT             "str"
#define POWER_UNIT              "W"
#define TIME_UNIT               "tm"

#define FLOAT_FACTOR_10         "f10"
#define FLOAT_FACTOR_100S       "f100s"
#define FLOAT_FACTOR_100        "f100"
#define FLOAT_FACTOR_1000       "f1000"
#define CHARACTER_FACTOR        "char2"
#define UNSIGNED_INTEGER_FACTOR "uint"

#define ADDRESS_COUNT_1         1
#define ADDRESS_COUNT_10        10

#define VCELL 1

static const char *modbus_register_dict_str[] = {
    "current",
    "voltage",
    "soc",
    "soh",
    "remain_cap",
    "full_cap",
    "",
    "bat_cycle",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "vcell_1",
    "vcell_2",
    "vcell_3",
    "vcell_4",
    "vcell_5",
    "vcell_6",
    "vcell_7",
    "vcell_8",
    "vcell_9",
    "vcell_10",
    "vcell_11",
    "vcell_12",
    "vcell_13",
    "",
    "",
    "",
    "tcell_1",
    "tcell_2",
    "tcell_3",
    "tcell_4",
    "mos_t",
    "env_t"
};

enum modbus_register_dict {
    MODBUS_PIN_CURRENT = 0,
    MODBUS_PIN_VOLTAGE,
    MODBUS_PIN_SOC,
    MODBUS_PIN_SOH,
    MODBUS_PIN_CAPACITY_REMAIN,
    MODBUS_PIN_CAPACITY_FULL,
    MODBUS_PIN_CYCLES = 7,
    MODBUS_PIN_VCELL_01 = 15,
    MODBUS_PIN_VCELL_02,
    MODBUS_PIN_VCELL_03,
    MODBUS_PIN_VCELL_04,
    MODBUS_PIN_VCELL_05,
    MODBUS_PIN_VCELL_06,
    MODBUS_PIN_VCELL_07,
    MODBUS_PIN_VCELL_08,
    MODBUS_PIN_VCELL_09,
    MODBUS_PIN_VCELL_10,
    MODBUS_PIN_VCELL_11,
    MODBUS_PIN_VCELL_12,
    MODBUS_PIN_VCELL_13,
    MODBUS_PIN_TCELL_01 = 31,
    MODBUS_PIN_TCELL_02,
    MODBUS_PIN_TCELL_03,
    MODBUS_PIN_TCELL_04,
    MODBUS_PIN_T_MOSFET,
    MODBUS_PIN_T_ENV,
    MODBUS_PIN_VERSION = 150,
    MODBUS_PIN_S_N_BMS = 160,
    MODBUS_PIN_S_N_PACK = 170,
};

#endif /* REGISTER */
