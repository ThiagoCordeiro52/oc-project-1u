#include <systemc.h>

// Include all your processor components
#include "ProgramCounter.h"
#include "ALU.h"
#include "Register.h"
#include "RegisterDatabase.h"
#include "InstructionMemory.h"
#include "Memory.h"
#include "MUX.h"

int sc_main(int argc, char* argv[]) {
    ProgramCounter pc("PC");
    ALU alu("ALU");
    Register reg1("Reg1");
    Register reg2("Reg2");
    RegisterDatabase regDB("RegDB");
    InstructionMemory imem("IMem");
    Memory mem("Mem");
    MUX mux("MUX");

    pc.clock(clock);
    pc.reset(reset);
    pc.enable(enable);
    pc.jump(jump);
    pc.jumpAddress(jumpAddress);
    pc.address(pc_address);

    alu.operand1(operand1);
    alu.operand2(operand2);
    alu.alu_control(alu_control);
    alu.result(alu_result);
    alu.zero(alu_zero);

    reg1.clock(clock);
    reg1.reset(reset);
    reg1.enable(enable);
    reg1.data_in(reg1_data_in);
    reg1.data_out(reg1_data_out);


    return 0;
}
