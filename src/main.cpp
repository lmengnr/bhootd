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

  bool addr_provided = 0;

  if (vm.count("help")) {
    std::cout << "bhootd is a daemon that runs on nodes and sends CPU usage "
                 "data to an MQTT message broker."
              << std::endl
              << desc << std::endl;
    return 1;
  }
  if (vm.count("broker-addr")) {

    std::cout << "Address Provided is: " << vm["broker-addr"].as<std::string>()
              << std::endl;
    addr_provided = 1;
  }
  if (vm.count("node-id")) {
    std::cout << "ID of the Node is: " << vm["node-id"].as<std::string>()
              << std::endl;
  } else {
    std::cout << "No address provided" << std::endl << desc << std::endl;
    return 1;
  }

  // If there was no address then stop
  if (!addr_provided)
    return 1;

  CpuUsage orb(vm["node-id"].as<std::string>());
  std::stringstream json_out;
  std::string json_str = json_out.str();

  std::string address = vm["broker-addr"].as<std::string>();
  mqtt::async_client cli(address, "");

  std::cout << "\nConnecting..." << std::endl;
  cli.connect()->wait();
  std::cout << "  ...OK" << std::endl;

  mqtt::topic top(cli, "test", QOS);
  mqtt::token_ptr tok;

  try {

    while (1) {

      json_out.str(std::string());
      json_out << "{ \"node_id\": \"" << orb.node_id
               << "\", \"cpu_usage\": " << orb.get_curr_val() << " }";

      std::cout << json_out.str() << std::endl;
      json_str = json_out.str();

      tok = top.publish(json_str.c_str());

      tok->wait(); // Just wait for the last one to complete.

      sleep(1);
    }

    cli.disconnect()->wait();
    std::cout << "  ...OK" << std::endl;

  }

  catch (const mqtt::exception &exc) {
    std::cerr << exc.what() << std::endl;
    return 1;
  }
}
