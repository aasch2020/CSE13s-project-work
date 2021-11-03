#include "io.h"

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
        crr_bytes = read(infile, buf, nbytes - read_bytes);
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
