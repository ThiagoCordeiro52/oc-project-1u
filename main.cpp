#include <systemc.h>
#include <fstream>
#include <vector>
#include <string>
#include "common/pc/pc.h"
#include "common/ula/ula.h"
#include "common/registers/registers.h"
#include "common/instruction-memory/instruction-memory.h"
#include "common/data-memory/data-memory.h"
#include "common/mux/mux.h"
#include "pipelines/1-fetch.h"
#include "pipelines/2-decode.h"
#include "pipelines/3-execute.h"
#include "pipelines/4-access.h"

int decode(std::string instruction) {
    int decodedInstruction = 0;
    int temporary = 0;

    std::string temp;
    std::stringstream line(instruction);
    std::vector<std::string> words;

    // Separando a instrução em palavras
    while (getline(line, temp, ' ')) {
        words.push_back(temp);
    }

    if (words.size() == 4) { 
        if (words[0] == "add")
            temporary = 0x20;
        else if (words[0] == "sub")
            temporary = 0x22;
    }

    return decodedInstruction;
}

int sc_main(int argc, char* argv[]) {
    ProgramCounter pc("PC");
    ALU alu("ALU");
    Register reg1("Reg1");
    Register reg2("Reg2");
    RegisterDatabase regDB("RegDB");
    InstructionMemory imem("IMem");
    Memory mem("Mem");
    MUX mux("MUX");
    Fetch fetch("fetch");
    Decode decode("decode");
    Execute execute("execute");
    Access access("access");

    sc_clock clock("clock", 10, SC_NS);

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

    // Pipeline 1
    fetch.clock(clock);
    fetch.pc_address(pc_address);
    fetch.imem_instruction_out(imem_instruction_out);

    // Pipeline 2
    decode.clock(clock);
    decode.imem_instruction_in(imem_instruction_out);
    decode.regDB_data_out(regDB_data_out);

    // Pipeline 3
    execute.clock(clock);
    execute.operand1(operand1);
    execute.operand2(operand2);
    execute.alu_control(alu_control);
    execute.alu_result(alu_result);
    execute.alu_zero(alu_zero);

    // Pipeline 4
    access.clock(clock);
    access.mem_data(mem_data);
    access.mem_clock(mem_clock);
    access.mem_write_enable(mem_write_enable);
    access.mem_read_enable(mem_read_enable);
    access.mem_address(mem_address);

    // Ler arquivo
    std::ifstream file_input("examples/raiz_quadrada.asm");
    std::vector<std::string> instructions;
    std::string line;
    while (std::getline(file_input, line)) {
        instructions.push_backK(line);
    }
    file_input.close();

    for (int i = 0; i < instructions.size(); ++i)
    {
        std::string instruction = instructions[i];
        int instruction_int = decode(instruction);
        imen.instruction_memory[i] = instruction_int;
    }


    sc_start();  // Descobrir como simular isso aqui

    return 0;
}
