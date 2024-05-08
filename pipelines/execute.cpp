#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(execute) {
    sc_in_clk clock;
    sc_in<sc_uint<32>> input, muxInput;
    sc_in<sc_uint<5>> memoryAddressInput, muxRegisterInput, memoryWriteInput;
    sc_in<bool> jumpResultInput, memoryWriteInputControl, jumpInput, writeInputRegister, memoryLoadInput, jumpCmpInput;

    sc_out<sc_uint<32>> output, muxOutput;
    sc_out<sc_uint<5>> memoryLoadOutput, muxOutput, memoryWriteOutput;
    sc_out<bool> jumpResultOutput, memoryWriteOutput, jumpOutput, writeOutput, memoryLoadOutput, jumpcOutput;
    void next();

    SC_CTOR(execute)
    {
        SC_METHOD(next);
        sensitive << clock.pos();
    }
};

void execute::next() {

    output.write(input.read());
    muxOutput.write(muxInput.read());
    memoryLoadOutput.write(memoryAddressInput.read());
    muxOutput.write(muxRegisterInput.read());
    memoryWriteOutput.write(memoryWriteInput.read());

    memoryWriteOutput.write(memoryWriteInputControl.read());
    jumpOutput.write(jumpInput.read());
    writeOutput.write(writeInputRegister.read());
    memoryLoadOutput.write(memoryLoadInput.read());
    jumpcOutput.write(jumpCmpInput.read());
    jumpResultOutput.write(jumpResultInput.read());
}