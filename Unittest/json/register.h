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

#include <stdint.h>

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

#define PIN_NUMBER              1

static const char *modbus_register_dict_str[] = {
    "current",
    "voltage",
    "soc",
    "soh",
    "capacity_remain",
    "capacity_full",
    "",
    "cycles",
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
    "t_mosfet",
    "t_env"
};

enum modbus_register_dict {
    CURRENT = 0,
    VOLTAGE,
    SOC,
    SOH,
    CAPACITY_REMAIN,
    CAPACITY_FULL,
    CYCLES = 7,
    VCELL_01 = 15,
    VCELL_02,
    VCELL_03,
    VCELL_04,
    VCELL_05,
    VCELL_06,
    VCELL_07,
    VCELL_08,
    VCELL_09,
    VCELL_10,
    VCELL_11,
    VCELL_12,
    VCELL_13,
    TCELL_01 = 31,
    TCELL_02,
    TCELL_03,
    TCELL_04,
    T_MOSFET,
    T_ENV,
    VERSION = 150,
    S_N_BMS = 160,
    S_N_PACK = 170,
};

#endif /* REGISTER */
