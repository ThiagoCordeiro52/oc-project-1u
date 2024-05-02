#include <systemc.h>

#define MEMORY_SIZE 1024 

SC_MODULE(Memory) {
    sc_in<bool> clock;
    sc_in<bool> write_enable;
    sc_in<bool> read_enable;
    sc_in<sc_uint<32>> address;
    sc_inout<sc_uint<32>> data;

    sc_uint<32> memory[MEMORY_SIZE];

    void memory_process() {
        if (write_enable.read() == true) {
            memory[address.read()] = data.read();
        } else if (read_enable.read() == true) {
            data.write(memory[address.read()]);
        }
    }

    SC_CTOR(Memory) {
        for (int i = 0; i < MEMORY_SIZE; ++i) {
            memory[i] = 0;
        }

        SC_METHOD(memory_process);
        sensitive << clock.pos();
    }
};