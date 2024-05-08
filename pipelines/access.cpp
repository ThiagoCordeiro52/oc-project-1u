#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(access) {
    sc_in_clk clock;
    sc_in<sc_uint<32>> ulaInput, memoryInput;
    sc_in<sc_uint<5>> memoryInput;
    sc_in<bool> writeRegInput, memoryLoadInput;

    sc_out<sc_uint<32>> ulaOutput, memoryOutput;
    sc_out<sc_uint<5>> muxOutput;
    sc_out<bool> writeOutput, memoryLoadOutput;
    void next();

    SC_CTOR(access)
    {
        SC_METHOD(next);
        sensitive << clock.pos();
    }
};

void access::next() {
    ulaOutput.write(ulaInput.read());
    memoryOutput.write(memoryInput.read());
    muxOutput.write(memoryInput.read());

    writeOutput.write(writeRegInput.read());
    memoryLoadOutput.write(memoryLoadInput.read());
}