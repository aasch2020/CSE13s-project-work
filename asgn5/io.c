#include "io.h"
#include "defines.h"
//The above header files given in the resources repository by Professor Long (Professor Long 2021)
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

//This function uses an external variable bytes_read to track the total number of bytes read,
uint64_t bytes_read;
//This function takes an input file, a buffer of 8 bit integers, and a number of bytes to read.
//If there are no bytes to be read return zero.
//If there are bytes to be read, This function will call the read function to read a given number of bytes
//from the input file until either read returns zero, which denotes end of file,
//or the number of bytes read is equal to the desired number of bytes to read.
//It return the number of bytes it read.
//This function inspired by the pseudocode provided in section (Christian Ocon 2021)
int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int read_bytes = 0;
    if (nbytes == 0) {
        return 0;
    }
    int crr_bytes = 0;
    while (read_bytes <= nbytes) {
        crr_bytes = read(infile, buf + read_bytes, nbytes - read_bytes);
        read_bytes += crr_bytes;
        if (crr_bytes == 0) {
            break;
        }
    }
    bytes_read += read_bytes;
    return read_bytes;
}
//This function uses an external variable bytes_written to track the total number of bytes written,
uint64_t bytes_written;
//This function takes an output file, a buffer of 8 bit integers, and a number of bytes to writes.
//If there are no bytes to be written return zero.
//This function loops calls to the write function while the number of bytes written is less than or equal to number of bytes to be written
//or if write returns 0, which means there are no more bytes to write.
//This function inspired by the pseudocode provided in section (Christian Ocon 2021)
int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int written_bytes = 0;
    if (nbytes == 0) {
               return 0;
    }
    int crr_bytes = 0;
    while (written_bytes <= nbytes) {
        crr_bytes = write(outfile, buf + written_bytes, nbytes - written_bytes);

        if (crr_bytes == 0) {
            break;
        }
        written_bytes += crr_bytes;
    }
    bytes_written += written_bytes;
    return written_bytes;
}

//This function makes use of a static buffer, and integers, to read bytes for printing bit, and to track where in the buffer the function is each call.
static uint8_t buffer[BLOCK];
static int index = 0;
static int end = -1;
//This function takes an input file and an int pointer to bit.
//If the given buffer is empty, it reads bytes from the input into the buffer, and sets the end to the number of bytes written if the number is not BLOCK
//If the index is equal to the end as in there are no more bits to read, return false
//This then uses bitwise operators, by taking the and of the given byte in the buffer shifted over by the index modulo 8 and 1.
//This gets the bit from the given spot in buffer and sets it equal to the bit pointer
//It then increments the index by one
//If the index is equal to the block*8, which means it is at the end of a full buffer, reset index to zero so more bytes can be read.
//This function inspired by the pseudocode provided in section (Eugene Chou 2021)
//This function returns true if the bit is read, and false if there are no more bits to read.
bool read_bit(int infile, uint8_t *bit) {

    if (index == 0) {

        int num_bytes = read_bytes(infile, buffer, BLOCK);
        if (num_bytes < BLOCK) {
            end = num_bytes * 8;
        }
    }
    if (index == end) {
        return false;
    }
    *bit = ((buffer[index / 8] >> ((index % 8))) & 1);
    index += 1;

    if (index == (BLOCK * 8)) {
        index = 0;
    }
    return true;
}

//This function utilizes a static buffer and a static index, to track the spot in the buffer we are in.
static uint8_t writebuf[BLOCK];
static int writeindex = 0;

//this function takes an output file and a code c, to write the code to the output file, and returns void.
//This function steps through the given code, pushing each bit in the code to the buffer, it achieves this by 
//using bitwise operators to set the bit using bitwise shifts, and and or.
//it then adds to the static index
//If the buffer is full, it writes the buffer to the output file.
void write_code(int outfile, Code *c) {
    for (uint32_t i = 0; i < code_size(c); i++) {
        int bit = code_get_bit(c, i);
        if (bit == 1) {
            writebuf[writeindex / 8] = (writebuf[writeindex / 8] | (1 << (writeindex % 8)));
        } else if (bit == 0) {
            writebuf[writeindex / 8] = (writebuf[writeindex / 8] & (~(1 << (writeindex % 8))));
        }
        writeindex++;
        if (writeindex == BLOCK * 8) {
            write_bytes(outfile, writebuf, BLOCK);
            writeindex = 0;
        }
    }
}

//This function shares the buffer and index with write code, takes an output file, and returns zero.
//Sinze the above function only prints when the buffer is full, this code prints the buffer whenever specified, even if it is not full
//Before writing the buffer, it zeroes the bits in the last byte, which are not in the current buffer to print extraneous values from being written.
void flush_codes(int outfile) {
    if (writeindex > 0) {
        int indbytes = writeindex / 8;
        if ((writeindex % 8) != 0) {
            writebuf[writeindex / 8] = (writebuf[writeindex / 8] & ~(255 << (writeindex % 8)));
            indbytes++;
        }
        write_bytes(outfile, writebuf, indbytes);
    }
}
