#include <systemc.h>
#include <fstream>
#include <vector>
#include <string>
#include "common/pc/pc.hpp"
#include "common/ula/ula.hpp"
#include "common/registers/registers.hpp"
#include "common/instruction-memory/instruction-memory.hpp"
#include "common/data-memory/data-memory.hpp"
#include "common/mux/mux.hpp"
#include "pipelines/1-fetch.hpp"
#include "pipelines/2-decode.hpp"
#include "pipelines/3-execute.hpp"
#include "pipelines/4-access.hpp"

int readInstruction(std::string instruction)
{
    int decodedInstruction = 0;
    int temporary = 0;

    std::string temp;
    std::stringstream line(instruction);
    std::vector<std::string> words;

    // Separando a instrução em palavras
    while (getline(line, temp, ' '))
    {
        words.push_back(temp);
    }

    if (words.size() == 4)
    {
        if (words[0] == "add")
            temporary = 0x20;
        else if (words[0] == "sub")
            temporary = 0x22;
    }

    return decodedInstruction;
}

int sc_main(int argc, char *argv[])
{
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
    sc_signal<sc_uint<32>> operand1, operand2, operand3, alu_control, alu_result;
    sc_signal<sc_uint<32>> mux_operand1, mux_operand2, mux_operand3, mux_result;
    sc_signal<bool> alu_zero, regWriteOutput;
    sc_signal<sc_uint<32>> imem_add_in, imem_instruction_out;
    sc_signal<sc_uint<32>> regDB_data_out, reg1_data_out;
    sc_signal<sc_uint<32>> mem_data;
    sc_signal<bool> mem_read_enable, mem_write_enable;

    // Connect clock and reset
    pc.clock(clock);
    pc.reset(reset);
    pc.enable(enable);
    pc.jump(jump);
    pc.jumpAddress(jumpAddress);
    pc.address(pc_address);

    fetch.clock(clock);
    fetch.input(pc_address);
    fetch.output(imem_add_in);

    decode.clock(clock);
    decode.instructionInput(imem_instruction_out);
    decode.dataInput1(regDB_data_out);
    decode.dataInput2(reg1_data_out);
    decode.memoryAddressLoadInput(mux_result);
    decode.ulaAddressInput(mux_result);
    decode.memoryLoadAddressIn(pc_address);
    decode.memoryWriteAddressIn(reg1_data_out);
    decode.ulaOperatorIn(alu_zero);

    // Connect Decode module outputs to corresponding signals
    decode.instructionOutput(imem_instruction_out);
    decode.dataOutput1(regDB_data_out);
    decode.dataOutput2(reg1_data_out);
    decode.memoryLoadAddressOutput(mux_result);
    decode.ulaAddressOutput(mux_result);
    decode.memoryLoadAddressRegOutput(pc_address);
    decode.memoryWriteAddressOutput(reg1_data_out);
    decode.ulaOperatorOutput(alu_zero);
    decode.controlMemoryWriteOutput(enable);
    decode.jumpOutput(jump);
    decode.regWriteOutput(regWriteOutput);
    decode.memoryLoadOutput(mem_read_enable);
    decode.jumpCompareOutput(alu_zero);

    execute.clock(clock);
    execute.instructionInput(imem_instruction_out);
    execute.dataMuxInput(regDB_data_out);
    execute.memoryAddressLoadInput(mux_result);
    execute.muxAddressInput(pc_address);
    execute.memoryWriteInput(reg1_data_out);
    execute.jumpResultInput(alu_zero);
    execute.controlMemoryInput(enable);
    execute.jumpInput(jump);
    execute.writeInput(regWriteOutput);
    execute.loadMemoryInput(mem_read_enable);
    execute.JumpCmpIn(alu_zero);

    execute.instructionOutput(imem_instruction_out);
    execute.dataMuxOutput(regDB_data_out);
    execute.memoryAddressLoadOutput(mux_result);
    execute.muxAddressRegOutput(pc_address);
    execute.memoryWriteAddressOutput(reg1_data_out);
    execute.jumpResultOutput(alu_zero);
    execute.controlMemoryWrite(enable);
    execute.jumpOutput(jump);
    execute.regWriteOutput(regWriteOutput);
    execute.memoryLoadOutput(mem_read_enable);
    execute.jumpCompareOutput(alu_zero);

    access.clock(clock);
    access.ulaInput(alu_result);
    access.dataInput(mem_data);
    access.muxAddressInput(mux_result);
    access.writeInput(mem_write_enable);
    access.memoryLoadInput(mem_read_enable);
    access.ulaOutput(alu_result);
    access.dataOutput(mem_data);
    access.muxAddressOutput(mux_result);
    access.writeOutput(mem_write_enable);
    access.memoryLoadOutput(mem_read_enable);

    // Ler arquivo
    std::ifstream file_input("examples/raiz_quadrada.asm");
    std::vector<std::string> instructions;
    std::string line;
    while (std::getline(file_input, line))
    {
        instructions.push_back(line);
    }
    file_input.close();

    for (int i = 0; i < instructions.size(); ++i)
    {
        std::string instruction = instructions[i];
        int instruction_int = readInstruction(instruction);
        imem.instruction_memory[i] = instruction_int;
    }

    sc_start(); // Descobrir como simular isso aqui

    return 0;
}
