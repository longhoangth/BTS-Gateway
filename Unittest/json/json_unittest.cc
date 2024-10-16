#include "json_test.h"
#include "register.h"
#include <limits.h>
#include <gtest/gtest.h>

uint16_t arr[] = {467, 51751, 86, 100, 9000, 10500, 0, 403, 0,
                0, 0, 0, 0, 0, 0, 3986, 3985, 3984, 3985, 3985,
                3984, 3988, 3984, 3984, 3978, 3985, 3984, 3940,
                0, 0, 0, 223, 224, 224, 222, 259, 246};

TEST(JsonStringDeviceComparisonTest, StringAreEqual) {
    std::string UpdateDevice = Create_device_integer_message(255, 2);

    std::cout << UpdateDevice << std::endl;
    
    EXPECT_EQ(json_string_test_update, UpdateDevice);
}

TEST(JsonObjectTest, ObjectAreEqual) {
    Json::Value root;
    root[JSON_KEY_1] = 53;
    root[JSON_KEY_2] = JSON_VALUE_2;
    root[JSON_KEY_3] = 255;

    std::cout << root << std::endl;

    EXPECT_EQ(root, parseJSON(json_string_test_update));
}

TEST(JsonModbusTest, ModbusData) {
    Json::Value root;
    float value_float;
    for(int i = 0; i < 37; i++) {
        root[JSON_KEY_1] = PIN_NUMBER;
        switch (i)
        {
        case CURRENT:
            value_float = arr[i]/1000;
            root[JSON_KEY_2] = modbus_register_dict_str[CURRENT];
            root[JSON_KEY_3] = value_float;
            break;
        case VOLTAGE:
            value_float = arr[i]/100;
            root[JSON_KEY_2] = modbus_register_dict_str[VOLTAGE];
            root[JSON_KEY_3] = value_float;
            break;
        case SOC:
            root[JSON_KEY_2] = modbus_register_dict_str[SOC];
            root[JSON_KEY_3] = arr[i];
            break;
        case SOH:
            root[JSON_KEY_2] = modbus_register_dict_str[SOH];
            root[JSON_KEY_3] = arr[i];
            break;
        case CAPACITY_REMAIN:
            value_float = arr[i]/1000;
            root[JSON_KEY_2] = modbus_register_dict_str[CAPACITY_REMAIN];
            root[JSON_KEY_3] = value_float;
            break;
        case CAPACITY_FULL:
            value_float = arr[i]/1000;
            root[JSON_KEY_2] = modbus_register_dict_str[CAPACITY_FULL];
            root[JSON_KEY_3] = value_float;
            break;
        case CYCLES:
            root[JSON_KEY_2] = modbus_register_dict_str[CYCLES];
            root[JSON_KEY_3] = arr[i];
            break;
        case VCELL_01:
            
            root[JSON_KEY_2] = modbus_register_dict_str[VCELL_01];
            root[JSON_KEY_3] = arr[i];
            break;
        case VCELL_02:
            
            root[JSON_KEY_2] = modbus_register_dict_str[VCELL_02];
            root[JSON_KEY_3] = arr[i];
            break;
        case VCELL_03:
            
            root[JSON_KEY_2] = modbus_register_dict_str[VCELL_03];
            root[JSON_KEY_3] = arr[i];
            break;
        case VCELL_04:
            
            root[JSON_KEY_2] = modbus_register_dict_str[VCELL_04];
            root[JSON_KEY_3] = arr[i];
            break;
        case VCELL_05:
            
            root[JSON_KEY_2] = modbus_register_dict_str[VCELL_05];
            root[JSON_KEY_3] = arr[i];
            break;
        case VCELL_06:
            
            root[JSON_KEY_2] = modbus_register_dict_str[VCELL_06];
            root[JSON_KEY_3] = arr[i];
            break;
        case VCELL_07:
            
            root[JSON_KEY_2] = modbus_register_dict_str[VCELL_07];
            root[JSON_KEY_3] = arr[i];
            break;
        case VCELL_08:
            
            root[JSON_KEY_2] = modbus_register_dict_str[VCELL_08];
            root[JSON_KEY_3] = arr[i];
            break;
        case VCELL_09:
            
            root[JSON_KEY_2] = modbus_register_dict_str[VCELL_09];
            root[JSON_KEY_3] = arr[i];
            break;
        case VCELL_10:
            
            root[JSON_KEY_2] = modbus_register_dict_str[VCELL_10];
            root[JSON_KEY_3] = arr[i];
            break;
        case VCELL_11:
            
            root[JSON_KEY_2] = modbus_register_dict_str[VCELL_11];
            root[JSON_KEY_3] = arr[i];
            break;
        case VCELL_12:
            
            root[JSON_KEY_2] = modbus_register_dict_str[VCELL_12];
            root[JSON_KEY_3] = arr[i];
            break;
        case VCELL_13:
            
            root[JSON_KEY_2] = modbus_register_dict_str[VCELL_13];
            root[JSON_KEY_3] = arr[i];
            break;
        case TCELL_01:
            value_float = arr[i]/10;
            root[JSON_KEY_2] = modbus_register_dict_str[TCELL_01];
            root[JSON_KEY_3] = value_float;
            break;
        case TCELL_02:
            value_float = arr[i]/10;
            root[JSON_KEY_2] = modbus_register_dict_str[TCELL_02];
            root[JSON_KEY_3] = value_float;
            break;
        case TCELL_03:
            value_float = arr[i]/10;
            root[JSON_KEY_2] = modbus_register_dict_str[TCELL_03];
            root[JSON_KEY_3] = value_float;
            break;
        case TCELL_04:
            value_float = arr[i]/10;
            root[JSON_KEY_2] = modbus_register_dict_str[TCELL_04];
            root[JSON_KEY_3] = value_float;
            break;
        case T_MOSFET:
            value_float = arr[i]/10;
            root[JSON_KEY_2] = modbus_register_dict_str[T_MOSFET];
            root[JSON_KEY_3] = value_float;
            break;
        case T_ENV:
            value_float = arr[i]/10;
            root[JSON_KEY_2] = modbus_register_dict_str[T_ENV];
            root[JSON_KEY_3] = value_float;
            break;
        default:
            break;
        }
        
        if(modbus_register_dict_str[i] == "")
            continue;

        std::cout << root << std::endl;
        ASSERT_EQ(root, Create_modbus_0x25_message(i, arr[i]));
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}