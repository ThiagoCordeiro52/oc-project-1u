#include <systemc.h>
#include "buffer.cpp"

void testbench_process() {
    sc_clock clock("clock", 1, SC_NS);
    sc_signal<sc_uint<32>> data_in;
    sc_signal<sc_uint<32>> data_out;

    Buffer my_buffer("my_buffer");
    my_buffer.clock(clock);
    my_buffer.data_in(data_in);
    my_buffer.data_out(data_out);

    data_in = 10;

    sc_start(10, SC_NS);

    std::cout << "Data out: " << data_out << std::endl;
}

int sc_main(int argc, char* argv[]) {
    testbench_process();
    return 0;
}