#include "main.hpp"
#include <boost/program_options.hpp>

int main(int argc, char **argv) {

  namespace po = boost::program_options;

  po::options_description desc("Allowed Options");
  desc.add_options()("help", "Print help messages")(
      "broker-addr", po::value<std::string>(),
      "usage: ./excutable <broker address>")("skip", "display stats");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);

  if (vm.count("help")) {
    std::cout << "Basic help message" << std::endl << desc << std::endl;
    return 1;
  }
  if (vm.count("broker-addr")) {
    // address provided so skip ahead
    std::cout << "Address Provided is: " << vm["broker-addr"].as<std::string>()
              << std::endl;

  } else if (vm.count("skip")) {
    // start displaying stats
    // This option is just temporary. Remove this later
  } else {
    std::cout << "No address provided" << std::endl << desc << std::endl;
    return 1;
  }

  while (1) {

    cpu_usage A("1");
    std::cout << "Node ID: " << A.node_id << std::endl;
    std::cout << "Current CPU Usage: " << A.get_curr_val() << std::endl;

    std::ifstream filestat("/proc/stat");
    std::string stat_line;
    std::getline(filestat, stat_line);

    std::cout << "Full CPU Stats" << std::endl;
    std::cout << stat_line << std::endl;

    sleep(1);
  }
}
