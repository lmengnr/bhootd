#pragma once
#include "mqtt/async_client.h"

const std::string DFLT_SERVER_ADDRESS{"tcp://localhost:1883"};

const std::string TOPIC{"test"};
const int QOS = 1;

const char *PAYLOADS[] = {"Hello World!", "Hi there!", "Is anyone listening?",
                          "Someone is always listening.", nullptr};

const auto TIMEOUT = std::chrono::seconds(10);