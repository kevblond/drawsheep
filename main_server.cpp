#include <Server.hpp>
#define PORT 20000
int main (int argc, char **argv) {
    Server server(PORT);
    server.start();
    return EXIT_SUCCESS;
}