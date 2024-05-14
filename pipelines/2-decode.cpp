#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(decode) { // Ok
    sc_in_clk clock;
    sc_in<sc_uint<32>> instructionInput, dataInput1, dataInput2;
    sc_in<sc_uint<32>> memoryAddressLoadInput, ulaAddressInput, memoryLoadAddressIn, memoryWriteAddressIn;
    sc_in<bool> ulaOperatorIn, controlMemoryInput, jumpInput, writeInput, loadMemoryInput, jumpCompareInput, jumpNegInput;

    sc_out<sc_uint<32>> instructionOutput, dataOutput1, dataOutput2;
    sc_out<sc_uint<5>> memoryLoadAddressOutput, ulaAddressOutput, memoryLoadAddressRegOutput, memoryWriteAddressOutput;
    sc_out<bool> ulaOperatorOutput, controlMemoryWriteOutput, jumpOutput, regWriteOutput, memoryLoadOutput, jumpCompareOutput, jumpNegOutput;

    void next();

    SC_CTOR(decode)
    {
        SC_METHOD(next);
        sensitive << clock.pos();
    }
};

void decode::next() {

    instructionOutput.write(instructionInput.read());
    dataOutput1.write(dataInput1.read());
    dataOutput2.write(dataInput2.read());
    memoryLoadAddressOutput.write(memoryAddressLoadInput.read().range(25, 21));
    ulaAddressOutput.write(ulaAddressInput.read().range(15, 11));
    memoryLoadAddressRegOutput.write(memoryLoadAddressIn.read().range(20, 16));
    AddrMemWriteOut.write(memoryWriteAddressIn.read().range(20, 16));

    ulaOperatorOutput.write(ulaOperatorIn.read());
    controlMemoryWriteOutput.write(controlMemoryInput.read());
    jumpOutput.write(jumpInput.read());
    regWriteOutput.write(writeInput.read());
    memoryLoadOutput.write(loadMemoryInput.read());
    jumpCompareOutput.write(jumpCompareInput.read());
    jumpNegOutput.write(jumpNegInput.read());
}