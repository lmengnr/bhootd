#pragma once

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void getHostname(std::string &hostname) {

  std::ifstream name("/etc/hostname");
  std::getline(name, hostname);
}

class CpuUsage {

public:
  double get_curr_val() const;
  const std::string node_id;
  int get_QOS() const { return QOS; };
  std::string TOPIC{"cpu/json"};

  CpuUsage(std::string id) : node_id(id) {}

private:
  uint32_t lastTotalUser = 0;
  uint32_t lastTotalUserLow = 0;
  uint32_t lastTotalSys = 0;
  uint32_t lastTotalIdle = 0;

  const int QOS = 1;
};
