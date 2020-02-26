#include "json.hpp";
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using json = nlohmann::json;

class cpu_usage {

public:
  double currValue;
  std::string node_id;

  cpu_usage() {
    currValue = get_curr_val();
    getHostname(node_id);
  }

private:
  u_int lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;

  double get_curr_val() {
    u_int totalUser, totalUserLow, totalSys, totalIdle, total;
    double percent;

    std::ifstream filestat("/proc/stat");
    std::string stat_line;
    std::getline(filestat, stat_line);

    std::string stat_line2 = stat_line.substr(5, stat_line.find(" 0 0"));

    std::stringstream statstream;
    statstream << stat_line2;

    statstream >> totalUser;
    statstream >> totalUserLow;
    statstream >> totalSys;
    statstream >> totalIdle;
    statstream >> total;

    if (totalUser < lastTotalUser || totalUserLow < lastTotalUserLow ||
        totalSys < lastTotalSys || totalIdle < lastTotalIdle) {
      // Overflow detection. Just skip this value.
      percent = -1.0;
    } else {
      total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) +
              (totalSys - lastTotalSys);
      percent = total;
      total += (totalIdle - lastTotalIdle);
      percent /= total;
      percent *= 100;
    }

    return percent;
  }

  void getHostname(std::string &hostname) {

    std::ifstream name("/etc/hostname");
    std::getline(name, hostname);
  }
};


int main() {

  for (int i=0; i <10; i++){

  };
  
  cpu_usage A;
  std::cout << "Node ID: " << A.node_id << std::endl;
  std::cout << "Current CPU Usage: " << A.currValue << std::endl;

  std::ifstream filestat("/proc/stat");
  std::string stat_line;
  std::getline(filestat, stat_line);

  std::cout<< "Full CPU Stats" <<std::endl;
  std::cout<< stat_line <<std::endl;

}
