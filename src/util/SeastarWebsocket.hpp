#include <seastar/core/app-template.hh>
#include <seastar/core/thread.hh>
#include <seastar/http/client.hh>
#include <seastar/http/websocket.hh>
#include <seastar/net/dpdk.hh>

using namespace seastar;
using namespace net;

namespace bpo = boost::program_options;

constexpr uint16_t PORT = 443;
constexpr const char * HOST = "wss://market-data.example.com";

class WebsocketClient
{
public:
    WebsocketClient(dpdk::eal_config eal_cfg, std::string & host, uint16_t port, std::string & path)
        : _eal(std::move(eal_cfg))
        , _client(ipv4_addr{host, port})
        , host_(host)
        , port_(port)
        , path_(path)
    {
    }

private:
    void run()
    {
        app_template app;

        // DPDK configuration
        dpdk::eal_config eal_cfg;
        eal_cfg.physical_port = 0; // Use first DPDK port
        eal_cfg.hugepages = "2048"; // Number of 2MB hugepages
        eal_cfg.core_mask = "0x1"; // Use core 0 for networking

        app.add_options()("dpdk-pmd", bpo::value<bool>()->default_value(true), "Enable DPDK PMD")(
            "network-stack", bpo::value<std::string>()->default_value("dpdk"), "Network stack");

        return app.run(
            argc,
            argv,
            [&]
            {
                return seastar::async(
                    [&]
                    {
                        ws_client client(std::move(eal_cfg));
                        client.connect_and_stream().get();
                    });
            });
    }

    future<> connect_and_stream()
    {
        return _client.connect().then(
            [this](connected_socket fd)
            {
                return do_with(
                    websocket::connection(std::move(fd)),
                    [this](auto & conn)
                    {
                        _conn = std::move(conn);

                        // WebSocket handshake
                        return _conn.handshake(host, "/stream")
                            .then(
                                [this]
                                {
                                    // Send subscription request
                                    return _conn.send(path_);
                                })
                            .then(
                                [this]
                                {
                                    // Start receive loop
                                    return receive_loop();
                                });
                    });
            });
    }

    future<> receive_loop()
    {
        return _conn.receive().then(
            [this](auto msg)
            {
                // Process market data
                std::cout << "Received update: " << msg << "\n";

                // Keep receiving
                return receive_loop();
            });
    }


    uint16_t port_;
    std::string host_;
    std::string path_;
    dpdk::eal _eal;
    http::client _client;
    http::experimental::websocket::connection _conn;
};