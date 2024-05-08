void testbench_process_instruction() {
    sc_clock clock("clock", 10, SC_NS);
    sc_signal<sc_uint<32>> address_in;
    sc_signal<sc_uint<32>> instruction_out;

    InstructionMemory inst_memory("inst_memory");
    inst_memory.clock(clock);
    inst_memory.address_in(address_in);
    inst_memory.instruction_out(instruction_out);

    for (int i = 0; i < INSTRUCTION_MEMORY_SIZE; ++i) {
        inst_memory.instruction_memory[i] = i; 
    }

    sc_trace_file *wf = sc_create_vcd_trace_file("instruction_memory_waveforms");
    sc_trace(wf, clock, "clock");
    sc_trace(wf, address_in, "address_in");
    sc_trace(wf, instruction_out, "instruction_out");

    const int num_tests = 5;
    int test_addresses[num_tests] = {0, 100, 200, 500, 1025}; 
    for (int i = 0; i < num_tests; ++i) {
        address_in = test_addresses[i];
        sc_start(10, SC_NS); 

        std::cout << sc_time_stamp() << " Read Instruction at Address " << test_addresses[i] << ": " << instruction_out.read() << std::endl;
    }

    sc_close_vcd_trace_file(wf);
}