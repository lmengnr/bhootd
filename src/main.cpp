#include "main.hpp"
#include <boost/program_options.hpp>

int main(int argc, char **argv) {

  namespace po = boost::program_options;

  po::options_description desc("Allowed Options");
  desc.add_options()("help", "Print help messages")(
      "broker-addr", po::value<std::string>(),
      "<IP address of broker e.g. 127.0.0.1>")(
      "node-id", po::value<std::string>(), "ID of this node")("see-stats",
                                                              "display stats");

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

  } else if (vm.count("see-stats")) {
    // start displaying stats
  }
  if (vm.count("node-id")) {
    std::cout << "ID of the Node is: " << vm["node-id"].as<std::string>()
              << std::endl;
  } else {
    std::cout << "No address provided" << std::endl << desc << std::endl;
    return 1;
  }

  CpuUsage orb(vm["node-id"].as<std::string>());
  std::stringstream json_out;

  while (1) {

    json_out.str(std::string());
    json_out << "{ \"node_id\": " << orb.node_id
             << ", \"cpu_usage\": " << orb.get_curr_val() << " }";

    std::cout << json_out.str() << std::endl;

    sleep(1);
  }
}
