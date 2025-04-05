#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <signal.h>

#include "../utils.h"
#include "BeveragePreferenceHandler.h"

using json = nlohmann::json;
using apache::thrift::server::TThreadedServer;
using apache::thrift::transport::TServerSocket;
using apache::thrift::transport::TFramedTransportFactory;
using apache::thrift::protocol::TBinaryProtocolFactory;

using namespace vending_machine;

// Signal handler code
void sigintHandler(int sig) {
    exit(EXIT_SUCCESS);
}

// Entry point of the service
int main(int argc, char **argv) {
    // 1: Notify the signal handler if interrupted
    signal(SIGINT, sigintHandler);
    // 1.1: Initialize logging
    init_logger();

    // 2: Read the config file for ports and addresses
    json config_json;
    if (load_config_file("config/service-config.json", &config_json) != 0) {
        exit(EXIT_FAILURE);
    }

    // 3: Get the service port from the config file
    int my_port = config_json["beverage-preference-service"]["port"];

    // 4: Configure the server with the appropriate processor and transport
    TThreadedServer server(
        std::make_shared<BeveragePreferenceServiceProcessor>(
            std::make_shared<BeveragePreferenceServiceHandler>()),
        std::make_shared<TServerSocket>("0.0.0.0", my_port),
        std::make_shared<TFramedTransportFactory>(),
        std::make_shared<TBinaryProtocolFactory>()
    );

    // 5: Start the server
    std::cout << "Starting the beverage preference server..." << std::endl;
    server.serve();
    return 0;
}
