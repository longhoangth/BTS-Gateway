#include "main.h"

ModBus          BtsModbus;
DebugLogger     BtsDebugLog;

int             modbus_address_salve;
uint8_t         value_control_device;
uint8_t         position_control_device;

uint8_t         flag_control_device;
uint8_t         flag_enable_pin[16] = {0};
uint16_t        CountTimeCheckConnectMQTT;
std::vector<uint8_t> flag_enable_device;

uint8_t         count_next_state;
fsmReadModbus_e state_read_modbus;

void Init(void);
int Get_SensorDevice(float arr[]);
int Get_StatusDevice(uint8_t arr[]);
int Set_ControlDevice(uint8_t position, uint8_t value);
int Get_DataPowerPin(int pinNum, uint16_t arr[]);
uint8_t Next_State(uint8_t stop_count, uint8_t reset_count, fsmReadModbus_e next_step);

void MQTT_Read_ModbusPin(uint8_t pinAddress);
void MQTT_Read_ModbusDevice(uint8_t deviceAddress);
void MQTT_Read_ModbusSensor(uint8_t deviceAddress);

void MQTT_Send_ModbusSensor(uint8_t deviceAddress, float data, uint8_t index);
void MQTT_Send_ModbusDevice(uint8_t deviceAddress, uint8_t data, uint8_t index);
void MQTT_Send_ModbusPin(uint8_t pinAddress, uint8_t position, uint16_t value);

#if ENA_LIB_MQTT
static std::string    message_payload_str;
std::string           message_topic_str;
std::string           field;
static const char     *message_payload_cstr;
static Mqtt           modbusMQTTclient;   // client for publish
static Mqtt           modbusMQTTclient1;  // client for subscribe & callbacks

void MQTT_Init();
#endif


#if ENA_LIB_MQTT
void mqtt_message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
  uint8_t address;
  #if ENA_LIB_JSON
  Json::Value     root;
  #endif

  message_payload_str = (char*) message->payload;
  message_topic_str = message->topic;
  BtsDebugLog.DebugLOG(MQTT_PROTOCOL, {
    "Received message",
    "Topic:" + message_topic_str,
    "Content:" + message_payload_str
  });

  #ifdef DEBUG_MQTT
  std::cout << message_topic_str << std::endl << message_payload_str << std::endl;
  #endif

  switch (Topic_converter(message_topic_str))
  {
    case MQTT_CONTROL:
      root = parseJSON(message_payload_str);
      address = root[JSON_KEY_4].asInt();
      if(address == MB_DEVICE_ADDRESS)
      {
        flag_control_device = 1;

        position_control_device = root[JSON_KEY_1].asInt();
        value_control_device = root[JSON_KEY_3].asInt();
        if(position_control_device >= DEVICE_OFFSET) {
          position_control_device -= DEVICE_OFFSET;
        } else {
          position_control_device -= SENSOR_OFFSET;
        }
      } 
      break;

    case MQTT_ENABLE_MODBUS:
      root = parseJSON(message_payload_str);
      address = root[JSON_KEY_4].asInt();
      if(address <= 16) 
      {
        flag_enable_pin[address] = 1;
      }
      else if(address >= 20 && address <= 60) 
      {
        flag_enable_device.push_back(address);
      }
      break;

    default:
        break;
  }
}
#endif

int main()
{
  Init();
  #if ENA_LIB_MQTT
  MQTT_Init();
  #endif
  #if ENA_LIB_LOG
  PLOG_NONE << "START";
  #endif
  sleep(1);
  while (1)
  {
    if (BtsModbus.CheckConnect() > 0)
    {
      if(flag_control_device == 1)
      {
          int return_code_control;
          BtsModbus.SetSlave(MB_DEVICE_ADDRESS);
          return_code_control = Set_ControlDevice(position_control_device, value_control_device);
          BtsDebugLog.DebugLOG(CONTROLLER, {
            "Position: " + std::to_string(position_control_device),
            "Value: " + std::to_string(value_control_device),
            "Return Code: " + std::to_string(return_code_control)
          });
          flag_control_device = 0;
      }
      else
      {
        switch(state_read_modbus)
        {
          case FSM_STATE_START:
            BtsModbus.SetSlave(MB_DEVICE_ADDRESS);
            count_next_state = 0;
            state_read_modbus = FSM_STATE_READ_SENSOR;
          break;

          case FSM_STATE_READ_SENSOR:
            if(Next_State(flag_enable_device.size(), 0, FSM_STATE_READ_STATUS))
            {
              BtsModbus.SetSlave(flag_enable_device.at(count_next_state-1));
              MQTT_Read_ModbusSensor(flag_enable_device.at(count_next_state-1));
            }
          break;

          case FSM_STATE_READ_STATUS:
            if(Next_State(flag_enable_device.size(), 0, FSM_STATE_READ_PIN))
            {
              BtsModbus.SetSlave(flag_enable_device.at(count_next_state-1));
              MQTT_Read_ModbusDevice(flag_enable_device.at(count_next_state-1));
            }
          break;

          case FSM_STATE_READ_PIN:
            if(Next_State(2, 0, FSM_STATE_READ_END))
            {
              MQTT_Read_ModbusPin(count_next_state);
              usleep(100000);
            }
          break;

          case FSM_STATE_READ_END:
            state_read_modbus = FSM_STATE_START;
            printf("\n------------------(End)------------------\n");
          break;
        }
      }
      BtsModbus.Close();
      usleep(1);
    }
    else
    {
      BtsModbus.Free();
      sleep(5);
      BtsModbus.Connect(PortModBusName, BaudRateModBus);
      BtsModbus.SetSlave(modbus_address_salve);
      BtsModbus.CheckConnect();
    }

    #if ENA_LIB_MQTT
    if(CountTimeCheckConnectMQTT >= 3000)
    {
      mosquitto_loop(modbusMQTTclient1.GetCLIENT(), 0, 1);
      CountTimeCheckConnectMQTT = 0;
    }
    CountTimeCheckConnectMQTT++;
    #endif
  }

  #if ENA_LIB_MQTT
  modbusMQTTclient.~Mqtt();
  modbusMQTTclient1.~Mqtt();
  #endif
  return 0;
}

/*------------------(Biennq)------------------*/
void Init(void)
{
  #if ENA_LIB_LOG
    // static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
    // static plog::RollingFileAppender<plog::TxtFormatter> fileAppender("Modbus.txt", 1024, 3);
    // plog::init(plog::error, "Modbus.txt");
    #if DEBUG_CONSOLE == 1 && DEBUG_FILE == 0
    static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init(plog::verbose, &consoleAppender);
    #elif DEBUG_CONSOLE == 0 && DEBUG_FILE == 1
    // static plog::RollingFileAppender<plog::TxtFormatter> fileAppender("Modbus.txt", 1024, 3);
    // plog::init(plog::error, &fileAppender);
    plog::init(plog::verbose, "Modbus.txt");
    #elif DEBUG_CONSOLE == 1 && DEBUG_FILE == 1
    static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
    static plog::RollingFileAppender<plog::TxtFormatter> fileAppender("Modbus.txt", 1024, 3);
    plog::init(plog::verbose, &fileAppender).addAppender(&consoleAppender);
    #endif

    PLOG_DEBUG << "Modbus Log Error!"; // short macro
  #endif
  flag_control_device = 0;
  modbus_address_salve = MB_DEVICE_ADDRESS;

  BtsModbus.Connect(PortModBusName, BaudRateModBus);
  BtsModbus.SetSlave(modbus_address_salve);
  BtsModbus.CheckConnect();

  // for testing an example gd32 device with address 20
  flag_enable_device.push_back(MB_DEVICE_ADDRESS);
  count_next_state = 0;
}

uint8_t Next_State(uint8_t stop_count, uint8_t reset_count, fsmReadModbus_e next_step)
{
   if(count_next_state < stop_count)
    {
      count_next_state++;
      return 1;
    }
    else
    {
      count_next_state = reset_count;
      state_read_modbus = next_step;
      return 0;
    }
}

int Get_SensorDevice(float arr[])
{
  int length;
  uint8_t count = 0;
  uint16_t tab_reg[20];
  data_format_float_uint16 data;

  length = BtsModbus.ReadRegister(MB_DEVICE_REG_READ_SENSOR_START, MB_DEVICE_REG_READ_SENSOR_END, tab_reg);
  if (length > 0)
  {
    for(uint8_t i = 0; i < length/2; i++)
    {
      data.bytes[1] = tab_reg[count];
      count++;
      data.bytes[0] = tab_reg[count];
      count++;
      arr[i] = data.data_float;
    }
    return length/2;
  }
  return RETRUN_ERROR;
}

int Get_StatusDevice(uint8_t arr[])
{
  int length;
  uint8_t count = 0;
  uint16_t tab_reg[20];
  
  length = BtsModbus.ReadRegister(MB_DEVICE_REG_READ_STATUS_START, MB_DEVICE_REG_READ_STATUS_END, tab_reg);
  if (length > 0)
  {
    for(uint8_t i = 0; i < length; i++)
    {
      arr[count] = ((tab_reg[i]>>8)&0xff);
      count++;
      arr[count] = (tab_reg[i]&0xff);
      count++;
    }
    return length*2;
  }
  return RETRUN_ERROR;
}

int Set_ControlDevice(uint8_t position, uint8_t value)
{
  int length;

  length = BtsModbus.WriteRegister(MB_DEVICE_REG_CONTROL, ByteToInt16(position, value));

  if (length > 0)
  {
    return length;
  }
  return RETRUN_ERROR;
}

int Get_DataPowerPin(int pinNum, uint16_t arr[])
{
  int length;
  length = BtsModbus.ReadRegister(MB_DEVICE_REG_READ_PIN_START, MB_DEVICE_REG_READ_PIN_END, arr);
  if (length > 0)
  {
    return length;
  }
  return RETRUN_ERROR;
}


/*------------------(Longht)------------------*/
#if ENA_LIB_MQTT
void MQTT_Init() 
{
  modbusMQTTclient.Init(CLIENT_ID_MODBUS, MQTT_HOST, MQTT_PORT);
  modbusMQTTclient1.Init(CLIENT_ID_MODBUS_1, MQTT_HOST, MQTT_PORT);
  modbusMQTTclient.Run();
  modbusMQTTclient1.Run();
  mosquitto_message_callback_set(modbusMQTTclient1.GetCLIENT(), mqtt_message_callback);
  modbusMQTTclient1.Subscribe(SUB_CONTROL_DEVICE);
  modbusMQTTclient1.Subscribe(SUB_ENABLE_MODBUS);
  modbusMQTTclient1.Subscribe(SUB_CONTROL);
}
#endif

void MQTT_Read_ModbusPin(uint8_t pinAddress)
{
  uint16_t data_pin[50];
  BtsModbus.SetSlave(pinAddress);
  int length = Get_DataPowerPin(pinAddress, data_pin);
  if (length > 0)
  {
    printf("\n------------------(Size pin: %d - Pin: %d)------------------\n", length, pinAddress);
    for (int i = 0; i < length; i++)
    {
      #if ENA_LIB_MQTT
      MQTT_Send_ModbusPin(pinAddress, i, data_pin[i]);
      #else
      printf("%d ", data_pin[i]);
      #endif
    }
  }
}

void MQTT_Read_ModbusDevice(uint8_t deviceAddress)
{
  uint8_t data_status_device[40];
  int length = Get_StatusDevice(data_status_device);
  if (length > 0)
  {
    printf("\n------------------(Size Status: %d)------------------\n", length);
    for (int i = 0; i < length; i++)
    {
      #if ENA_LIB_MQTT
      MQTT_Send_ModbusDevice(deviceAddress, data_status_device[i], i);
      #else
      printf("%d ", data_status_device[i]);
      #endif
    }
  }
}

void MQTT_Read_ModbusSensor(uint8_t deviceAddress)
{
  float data_sensor[10];
  int length = Get_SensorDevice(data_sensor);
  if (length > 0)
  {
    printf("\n------------------(Size sensor: %d)------------------\n", length);
    for (int i = 0; i < length; i++)
    {
      #if ENA_LIB_MQTT
      MQTT_Send_ModbusSensor(deviceAddress, data_sensor[i], i);
      #else
      printf("%f ", data_sensor[i]);
      #endif
    }
  }
}

void MQTT_Send_ModbusSensor(uint8_t deviceAddress, float data, uint8_t index) 
{
  #if ENA_LIB_MQTT
  try{
    message_payload_cstr = Create_sensor_float_message(deviceAddress, data, index);
  }
  catch (const std::exception& e) {
    #if ENA_LIB_LOG
    PLOG_INFO << "Error creating sensor data message!";
    PLOG_ERROR << e.what(); 
    #else
    std::cerr << "Error: " << e.what() << std::endl;
    #endif
  }
  modbusMQTTclient.Send( PUB_UPDATE_MODBUS, message_payload_cstr);
  #endif
}

void MQTT_Send_ModbusDevice(uint8_t deviceAddress, uint8_t data, uint8_t index)
{
  #if ENA_LIB_MQTT
    try{
    message_payload_cstr = Create_device_integer_message(deviceAddress, data, index);
  }
  catch (const std::exception& e) 
  {
    #if ENA_LIB_LOG
    PLOG_INFO << "Error creating device data message!";
    PLOG_ERROR << e.what();
    #else
    std::cerr << "Error: " << e.what() << std::endl;
    #endif
  }
  modbusMQTTclient.Send( PUB_UPDATE_MODBUS, message_payload_cstr);
  #endif
}

void MQTT_Send_ModbusPin(uint8_t pinAddress, uint8_t position, uint16_t value) 
{
  #if ENA_LIB_MQTT
  try{
    message_payload_cstr = Create_modbus_pin_data_message( pinAddress, position, value);
  }
  catch(const std::exception & e)
  {
    #if ENA_LIB_LOG
    PLOG_INFO << "Error creating PIN data message!";
    PLOG_ERROR << e.what();
    #else
    std::cerr << "Error: " << e.what() << std::endl;
    #endif
  }
  modbusMQTTclient.Send( PUB_UPDATE_MODBUS, message_payload_cstr);
  #endif
  
}