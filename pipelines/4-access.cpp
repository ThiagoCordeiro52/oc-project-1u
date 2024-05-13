#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(access) {
    sc_in_clk clock;
    sc_in<sc_uint<32>> ulaInput, dataInput;
    sc_in<sc_uint<5>> muxAddressInput;
    sc_in<bool> writeInput, memoryLoadInput;

    sc_out<sc_uint<32>> ulaOutput, dataOutput;
    sc_out<sc_uint<5>> muxAddressOutput;
    sc_out<bool> writeOutput, memoryLoadOutput;

    void next();

    SC_CTOR(access) {
        SC_METHOD(next);
        sensitive << clock.pos();
    }
};

void access::next() {
    ulaOutput.write(ulaInput.read());
    dataOutput.write(dataInput.read());
    muxAddressOutput.write(muxAddressInput.read());

    writeOutput.write(writeInput.read());
    memoryLoadOutput.write(memoryLoadInput.read());
}