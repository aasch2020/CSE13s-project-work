#include "io.h"

#include <unistd.h>
#include <fcntl.h>

int read_bytes(int infile, uint8_t *buf, int nbytes){
	int read = 0;
	if (nbytes == 0){
		return 0;
	}
	
}
