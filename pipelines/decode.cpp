#include "systemc.h"
#include "sysc/utils/sc_vector.h"

SC_MODULE(decode) {
    sc_in<sc_uint<32>> input, dataInput, dataInput2;
    sc_in<sc_uint<32>> memoryAddress, ulaAddress, memoryRegAddress, memoryAdressInput;
    sc_in<bool> ulaInput, memoryWriteInput, jump, writeRegisterInput, memoryInput, jumpcInput, jumpNegIn;
    sc_in_clk clock;

    sc_out<sc_uint<32>> output, dataOutput, dataOutput2;
    sc_out<sc_uint<5>> memoryAddressOutput, ulaRegisterOutput, memoryLoadOutput, memoryWriteOutput;
    sc_out<bool> ulaOpOutput, memoryWriteOutput, jumpOutput, writeOutput, memoryLoadOutput, jumpcOutput, jumpNegOut;

    // methods
    void next();

    SC_CTOR(decode)
    {
        SC_METHOD(next);
        sensitive << clock.pos();
    }
};

void decode::next()
{
    output.write(input.read());
    dataOutput.write(dataInput.read());
    dataOutput2.write(dataInput2.read());
    AddrMemLoadFonteOut.write(memoryAddress.read().range(25, 21));
    ulaRegisterOutput.write(ulaAddress.read().range(15, 11));
    memoryLoadOutput.write(memoryRegAddress.read().range(20, 16));
    AddrMemWriteOut.write(memoryAdressInput.read().range(20, 16));

    ulaOpOutput.write(ulaInput.read());
    memoryWriteOutput.write(memoryWriteInput.read());
    jumpOutput.write(jump.read());
    writeOutput.write(writeRegisterInput.read());
    memoryLoadOutput.write(memoryInput.read());
    jumpcOutput.write(jumpcInput.read());
    jumpNegOut.write(jumpNegIn.read());
}