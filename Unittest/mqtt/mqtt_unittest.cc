#include <gtest/gtest.h>
#include "mqtt.h"
#include <unistd.h>

static std::string message_payload_str;
static std::string message_topic;

mqtt mqtt_client(CLIENT_ID, MQTT_HOST, MQTT_PORT, 60);

class MyTestEventListener : public ::testing::EmptyTestEventListener {
 public:
  virtual void OnTestProgramStart(const ::testing::UnitTest& unit_test) {
    // This method is called before the entire test run starts.
  }

  virtual void OnTestSuiteStart(const ::testing::TestSuite& test_suite) {
    // This method is called before each test case starts.
    mosquitto_loop(mqtt_client.getCLIENT(), 0, 1);
  }

  virtual void OnTestStart(const ::testing::TestInfo& test_info) {
    // This method is called before each test starts.
  }
};

// Define test cases and tests here...
TEST(TestMQTT, Init) {
    std::cout << "Testing initialization..." << std::endl;
    ASSERT_EQ(MOSQ_ERR_SUCCESS_STR, mqtt_client.run());
    ASSERT_EQ(MOSQ_ERR_SUCCESS_STR, mqtt_client.subscribe(SUBCRIBE_TOPIC));
}
void RunTests() {
  ::testing::InitGoogleTest();
  RUN_ALL_TESTS();
}

void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message) {
    message_payload_str = (char*) message->payload;
    message_topic = message->topic;
    std::cout << message_topic << std::endl << message_payload_str << std::endl;
}

TEST(TestMQTT, Callback) {
    std::cout << "Testing callback function" << std::endl;
    ASSERT_EQ("test", message_topic);
    ASSERT_EQ("hello", message_payload_str);

    message_topic.clear();
    message_payload_str.clear();
}

int main(int argc, char** argv) {
  // ...
  mqtt_client.run();
  mqtt_client.subscribe(SUBCRIBE_TOPIC);
  mosquitto_message_callback_set(mqtt_client.getCLIENT(), message_callback);

  sleep(3);
  // Call RunTests() to run the tests
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::GTEST_FLAG(filter) = "TestMQTT.Init";
  RunTests();
  
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::GTEST_FLAG(filter) = "TestMQTT.Callback";
    // Create a listener for test events
    MyTestEventListener listener;

    // Register the listener to receive notifications for test events
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();
    listeners.Append(&listener);
  while(1) {
    mosquitto_loop(mqtt_client.getCLIENT(), 0, 1);
    std::cout << "Wait 10 seconds before testing callback" << std::endl;
    sleep(10);
    RunTests();
    
  }
  
  return 0;
}
