void testbench_process_Memory() {
    sc_clock clock("clock", 10, SC_NS);
    sc_signal<bool> write_enable;
    sc_signal<bool> read_enable;
    sc_signal<sc_uint<32>> address;
    sc_signal<sc_uint<32>> data;

    Memory memory("memory");
    memory.clock(clock);
    memory.write_enable(write_enable);
    memory.read_enable(read_enable);
    memory.address(address);
    memory.data(data);

    sc_trace_file *wf = sc_create_vcd_trace_file("memory_waveforms");
    sc_trace(wf, clock, "clock");
    sc_trace(wf, write_enable, "write_enable");
    sc_trace(wf, read_enable, "read_enable");
    sc_trace(wf, address, "address");
    sc_trace(wf, data, "data");

    write_enable = 0;
    read_enable = 0;

    for (int i = 0; i < MEMORY_SIZE; ++i) {
        address = i;
        data = i * 10; 
        write_enable = 1;
        sc_start(10, SC_NS);
        write_enable = 0;
        sc_start(10, SC_NS);
    }

    for (int i = 0; i < MEMORY_SIZE; ++i) {
        address = i;
        read_enable = 1;
        sc_start(10, SC_NS);
        read_enable = 0;
        sc_start(10, SC_NS);
        std::cout << sc_time_stamp() << " Read Data at Address " << i << ": " << data << std::endl;
    }

    sc_close_vcd_trace_file(wf);
}