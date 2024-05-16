#include <systemc.h>

SC_MODULE(Buffer) {
    sc_in<bool> clock;
    sc_in<sc_uint<32>> data_in;
    sc_out<sc_uint<32>> data_out;

    sc_fifo<sc_uint<32>> buffer;

    SC_CTOR(Buffer) : buffer("buffer", 8) {
        SC_METHOD(write_to_buffer);
        sensitive << clock.pos();

        SC_METHOD(read_from_buffer);
        sensitive << clock.pos();
    }

    void write_to_buffer() {
        if (buffer.num_free() > 0) {
            buffer.write(data_in.read());
        } else {
            SC_REPORT_ERROR("Buffer overflow");
        }
    }

    void read_from_buffer() {
        if (buffer.num_available() > 0) {
            data_out.write(buffer.read());
        } else {
            SC_REPORT_ERROR("Buffer underflow");
        }
    }
};