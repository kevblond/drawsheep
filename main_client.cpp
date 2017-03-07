#include <Client.hpp>
#include <cstdlib>
#include <iostream>

#define PORT 20000
int main (int argc, char **argv) {
    try {
        Client client(PORT);
        client.send_file("test");
        client.read_string();
    } catch (const char *s) {
        std::cerr << s << std::endl;
    }


    return EXIT_SUCCESS;
}