#include "main.hpp"
#include <boost/program_options.hpp>

/////////////////////////////////////////////////////////////////////////////////

const std::string DFLT_SERVER_ADDRESS{"tcp://localhost:1883"};

const std::string TOPIC{"test"};
const int QOS = 1;

const char *PAYLOADS[] = {"Hello World!", "Hi there!", "Is anyone listening?",
                          "Someone is always listening.", nullptr};

const auto TIMEOUT = std::chrono::seconds(10);

/////////////////////////////////////////////////////////////////////////////////

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
    std::cout << "bhootd is a daemon that runs on nodes and sends CPU usage "
                 "data to an MQTT message broker."
              << std::endl
              << desc << std::endl;
    return 1;
  }
  if (vm.count("broker-addr")) {
    // address provided so skip ahead
    std::cout << "Address Provided is: " << vm["broker-addr"].as<std::string>()
              << std::endl;

    std::string address = vm["broker-addr"].as<std::string>();
    mqtt::async_client cli(address, "");

    try {
      std::cout << "\nConnecting..." << std::endl;
      cli.connect()->wait();
      std::cout << "  ...OK" << std::endl;

      mqtt::topic top(cli, "test", QOS);
      mqtt::token_ptr tok;

      size_t i = 0;
      while (PAYLOADS[i]) {
        tok = top.publish(PAYLOADS[i++]);
      }
      tok->wait(); // Just wait for the last one to complete.
      std::cout << "OK" << std::endl;

      tok = top.publish("working");

      cli.disconnect()->wait();
      std::cout << "  ...OK" << std::endl;

    }

    catch (const mqtt::exception &exc) {
      std::cerr << exc.what() << std::endl;
      return 1;
    }

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
    json_out << "{ \"node_id\": \"" << orb.node_id
             << "\", \"cpu_usage\": " << orb.get_curr_val() << " }";

    std::cout << json_out.str() << std::endl;

    sleep(1);
  }
}
