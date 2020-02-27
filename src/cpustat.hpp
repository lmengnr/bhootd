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

class cpu_usage {

public:
  double get_curr_val();
  const std::string node_id;

  cpu_usage(std::string id) : node_id(id) {
    currValue = get_curr_val();
    std::cout << "CurrValue = " << currValue << std::endl;
  }

private:
  double currValue;
  uint32_t lastTotalUser = 0;
  uint32_t lastTotalUserLow = 0;
  uint32_t lastTotalSys = 0;
  uint32_t lastTotalIdle = 0;
};
