#include "main.hpp"
#include <boost/program_options.hpp>

int main(int argc, char **argv) {

  namespace po = boost::program_options;

  //  ------------- Some setups for MQTT async publisher ------------
  const std::string DFLT_SERVER_ADDRESS{"tcp://localhost:1883"};
  const auto TIMEOUT = std::chrono::seconds(10);
  // ----------------------------------------------------------------

  // Reading passed arguments with boost program options

  po::options_description desc("Allowed Options");
  desc.add_options()("help", "Print help messages")(
      "broker-addr", po::value<std::string>(),
      "<IP address of broker e.g. 127.0.0.1>")(
      "node-id", po::value<std::string>(),
      "ID of this node")("see-stats", "display stats on terminal");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);

  bool addr_provided = 0;
  bool simple_output = 0;

  if (vm.count("see-stats")) {
    std::cout << "Show stats provided" << std::endl;
    simple_output = 1;
  }

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
  } else if (addr_provided == 0 && simple_output == 0) {
    std::cout << "No address provided" << std::endl << desc << std::endl;
    return 1;
  }

  // ------------ if the option of 'see-stats' is passed then display the stats
  // on the terminal ----------------------------------------------------------
  if (simple_output) {
    CpuUsage simple_stats("none");
    std::stringstream simple_json;

    while (1) {
      simple_json.str(std::string());
      simple_json << "{ \"node_id\": \""
                  << "none"
                  << "\", \"cpu_usage\": " << simple_stats.get_curr_val()
                  << " }";

      std::cout << simple_json.str() << std::endl;

      sleep(1);
    }
    return 0;
  }
  // ------------------------------------------------------------------------
  // -------- End of the simple output implementation block -----------------

  // Defining CpuUsage object "orb" which will transmit our data
  CpuUsage orb(vm["node-id"].as<std::string>());

  // The strings and string stream which will hold our data
  std::stringstream json_out;
  std::string json_str = json_out.str();
  std::string address = vm["broker-addr"].as<std::string>();
  std::string usage;

  // MQTT publisher setup
  mqtt::async_client cli(address, "");

  std::cout << "\nConnecting..." << std::endl;
  cli.connect()->wait();
  std::cout << "  ...OK" << std::endl;

  const int QOS = orb.get_QOS();
  orb.TOPIC = "cpu/json";
  const std::string topic = orb.TOPIC;    // Topic string
  const std::string topic2 = "cpu/usage"; // You can also just define it here

  mqtt::topic top(cli, topic, QOS); // topic setup
  mqtt::topic top2(cli, topic2, QOS);

  mqtt::token_ptr tok;
  mqtt::token_ptr tok2;

  // -------------------- Publishing Block ---------------------------
  // -----------------------------------------------------------------
  try {

    while (1) {

      json_out.str(std::string());
      json_out << "{ \"node_id\": \"" << orb.node_id
               << "\", \"cpu_usage\": " << orb.get_curr_val() << " }";

      usage = std::to_string(orb.get_curr_val());

      std::cout << json_out.str() << std::endl;
      json_str = json_out.str();

      tok = top.publish(json_str.c_str());
      tok2 = top2.publish(usage.c_str());

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
  // ----------------------------------------------------------------
  // ---------------- End of Publishing block -----------------------

  return 0;
}
