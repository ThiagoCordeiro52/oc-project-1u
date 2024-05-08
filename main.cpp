#include <systemc.h>
#include "common/pc/pc.cpp"
#include "common/ula/ula.cpp"
#include "common/registers/registers.cpp"
#include "common/instruction-memory/instruction-memory.cpp"
#include "common/data-memory/data-memory.cpp"
#include "common/mux/mux.cpp"

int sc_main(int argc, char* argv[]) {
    ProgramCounter pc("PC");
    ALU alu("ALU");
    Register reg1("Reg1");
    Register reg2("Reg2");
    RegisterDatabase regDB("RegDB");
    InstructionMemory imem("IMem");
    Memory mem("Mem");
    MUX mux("MUX");

    // signals
    sc_clock clock("clock", 10, SC_NS);  // 10 ns period
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

    mem.clock(mem_clock);
    mem.write_enable(mem_write_enable);
    mem.read_enable(mem_read_enable);
    mem.address(mem_address);
    mem.data(mem_data);

    mux.operand1(mux_operand1);
    mux.operand2(mux_operand2);
    mux.operand3(mux_operand3);
    mux.result(mux_result);
    mux.zero(mux_zero);

    // Start simulation
    sc_start();

    return 0;
}
