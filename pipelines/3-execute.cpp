#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(Execute) {
    sc_in_clk clock;
    sc_in<sc_uint<32>> instructionInput, dataMuxInput;
    sc_in<sc_uint<32>> memoryAddressLoadInput, muxAddressInput, memoryWriteInput;
    sc_in<bool> jumpResultInput, controlMemoryInput, jumpInput, writeInput, loadMemoryInput, JumpCmpIn;

    sc_out<sc_uint<32>> instructionOutput, dataMuxOutput;
    sc_out<sc_uint<32>> memoryAddressLoadOutput, muxAddressRegOutput, memoryWriteAddressOutput;
    sc_out<bool> jumpResultOutput, controlMemoryWrite, jumpOutput, regWriteOutput, memoryLoadOutput, jumpCompareOutput;

    void next();

    SC_CTOR(Execute) {
        SC_METHOD(next);
        sensitive << clock.pos();
    }
};

void Execute::next() {

    instructionOutput.write(instructionInput.read());
    dataMuxOutput.write(dataMuxInput.read());
    memoryAddressLoadOutput.write(memoryAddressLoadInput.read());
    muxAddressRegOutput.write(muxAddressInput.read());
    memoryWriteAddressOutput.write(memoryWriteInput.read());

    controlMemoryWrite.write(controlMemoryInput.read());
    jumpOutput.write(jumpInput.read());
    regWriteOutput.write(writeInput.read());
    memoryLoadOutput.write(loadMemoryInput.read());
    jumpCompareOutput.write(JumpCmpIn.read());
    jumpResultOutput.write(jumpResultInput.read());
}