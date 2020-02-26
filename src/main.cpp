#include "main.hpp"

int main() {

  for (int i = 0; i < 10; i++) {
  };

  cpu_usage A("1");
  std::cout << "Node ID: " << A.node_id << std::endl;
  std::cout << "Current CPU Usage: " << A.get_curr_val() << std::endl;

  std::ifstream filestat("/proc/stat");
  std::string stat_line;
  std::getline(filestat, stat_line);

  std::cout << "Full CPU Stats" << std::endl;
  std::cout << stat_line << std::endl;
}
