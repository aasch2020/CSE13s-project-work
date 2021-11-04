#include "io.h"
#include "defines.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
uint64_t bytes_read;

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

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int written_bytes = 0;
    if (nbytes == 0) {
        return 0;
    }
    int crr_bytes = 0;
    while (written_bytes <= nbytes) {
        crr_bytes = write(outfile, buf, nbytes - written_bytes);
        written_bytes += crr_bytes;
        if (crr_bytes == 0) {
            break;
        }
    }
    return written_bytes;
}
static uint8_t buffer[BLOCK];
static int index = 0; //where in teh buffffffffff
static int end = -1; //the last valid byte the last avalid thie byte
bool read_bit(int infile, uint8_t *bit) {

    if (index == 0) {

        int num_bytes = read_bytes(infile, buffer, BLOCK);
        if (num_bytes < BLOCK) {
            end = num_bytes * 8;
        }
    }
    if (index == end - 1) {
        return false;
    }
    *bit = ((buffer[index / 8] >> ((index % 8))) & 1);
    index += 1;

    if (index == (BLOCK * 8)) {
        index = 0;
    }
    return true;
}
