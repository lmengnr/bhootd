#include "json.hpp";
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using json = nlohmann::json;

u_int lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;

int main(int argc, char *argv[]) {

  u_int totalUser, totalUserLow, totalSys, totalIdle, total;
  double percent;

  std::ifstream filestat("/proc/stat");
  std::string stat_line;
  std::getline(filestat, stat_line);

  std::cout << stat_line << std::endl;

  std::string stat_line2 = stat_line.substr(5, stat_line.find(" 0 0"));

  // std::cout<< stat_line2 <<std::endl;

  std::stringstream statstream;
  statstream << stat_line2;

  std::string s1, s2, s3, s4;
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
}
