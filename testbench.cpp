// For eda:
// #include <systemc.h>
// #include "pc.cpp"
// #include "ula.cpp"
// #include "registers.cpp"
// #include "instructionMemory.cpp"
// #include "dataMemory.cpp"
// #include "mux.cpp"
// #include "1-fetch.cpp"
// #include "2-decode.cpp"
// #include "3-execute.cpp"
// #include "4-access.cpp"


#include <systemc.h>
#include "common/pc/pc.cpp"
#include "common/ula/ula.cpp"
#include "common/registers/registers.cpp"
#include "common/instruction-memory/instruction-memory.cpp"
#include "common/data-memory/data-memory.cpp"
#include "common/mux/mux.cpp"
#include "pipelines/1-fetch.cpp"
#include "pipelines/2-decode.cpp"
#include "pipelines/3-execute.cpp"
#include "pipelines/4-access.cpp"

SC_MODULE(Testbench) {

    ProgramCounter pc;
    ALU alu;
    Register reg1, reg2;
    RegisterDatabase regDB;
    InstructionMemory imem;
    Memory mem;
    MUX mux;
    Fetch fetch;
    Decode decode;
    Execute execute;
    Access access;

    // Signals
    sc_clock clock;
    sc_signal<bool> reset, enable, jump;
    sc_signal<sc_uint<32>> jumpAddress, pc_address;
    sc_signal<sc_uint<32>> operand1, operand2, alu_control, alu_result;
    sc_signal<bool> alu_zero;
    sc_signal<sc_logic> a, b, cin;
    sc_signal<sc_logic> sum, cout;
    sc_signal<sc_uint<32>> reg1_data_in, reg1_data_out;
    sc_signal<sc_uint<32>> regDB_reg_id, regDB_data_in, regDB_data_out;
    sc_signal<sc_uint<32>> imem_address_in, imem_instruction_out;
    sc_signal<bool> mem_clock, mem_write_enable, mem_read_enable;
    sc_signal<sc_uint<32>> mem_address, mem_data;
    sc_signal<sc_uint<32>> mux_operand1, mux_operand2, mux_operand3, mux_result;
    sc_signal<bool> mux_zero;

    SC_CTOR(Testbench) : pc("PC"), alu("ALU"), reg1("Reg1"), reg2("Reg2"),
                         regDB("RegDB"), imem("IMem"), mem("Mem"),
                         mux("MUX"), fetch("Fetch"), decode("Decode"),
                         execute("Execute"), access("Access"), clock("clock", 10, SC_NS) {

        // Connect components to signals
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

        regDB.reg_id(regDB_reg_id);
        regDB.data_in(regDB_data_in);
        regDB.data_out(regDB_data_out);

        imem.clock(clock);
        imem.address_in(imem_address_in);
        imem.instruction_out(imem_instruction_out);

        mem.clock(clock);
        mem.write_enable(mem_write_enable);
        mem.read_enable(mem_read_enable);
        mem.address(mem_address);
        mem.data(mem_data);

        mux.operand1(mux_operand1);
        mux.operand2(mux_operand2);
        mux.operand3(mux_operand3);
        mux.result(mux_result);
        mux.zero(mux_zero);

        // Connect pipeline stages
        fetch.clock(clock);
        fetch.input(pc_address);
        fetch.output(imem_instruction_out);

        decode.clock(clock);
        decode.instructionInput(imem_instruction_out);
        decode.dataInput1(regDB_data_out);
        decode.dataInput2(reg1_data_out);

        execute.clock(clock);
        execute.instructionInput(imem_instruction_out);
        execute.dataMuxInput(regDB_data_out);
        execute.memoryAddressLoadInput(mux_result);
        execute.muxAddressInput(pc_address);
        execute.memoryWriteInput(reg1_data_out);
        execute.jumpResultInput(alu_zero);
        execute.controlMemoryInput(enable);
        execute.jumpInput(jump);
        execute.writeInput(regDB_data_out);
        execute.loadMemoryInput(mem_read_enable);
        execute.JumpCmpIn(alu_zero);

        access.clock(clock);
        access.ulaInput(alu_result);
        access.dataInput(mem_data);
        access.muxAddressInput(mux_result);
        access.writeInput(mem_write_enable);
        access.memoryLoadInput(mem_read_enable);

        SC_THREAD(test);
    }

    void test() {
        reset = 1;
        enable = 1;
        jump = 0;
        jumpAddress = 0;
        wait(10, SC_NS);

        reset = 0;
        pc_address = 0x100;
        wait(10, SC_NS);
    }
};

int sc_main(int argc, char* argv[]) {
    Testbench tb("Testbench");
    sc_start(); 
    return 0;
}
