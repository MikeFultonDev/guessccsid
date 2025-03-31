
/*
 * _OPEN_SYS_FILE_EXT needs to be defined to be able to get at the 
 * special conversion attributes in fcntl
 */
#ifdef __MVS__
  #define _OPEN_SYS_FILE_EXT 1
#endif

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "guessccsid.h"

#ifdef __MVS__
static int disableautocvt(int fd) {
  struct f_cnvrt req = {SETCVTOFF, 0, 0};
  return fcntl(fd, F_CONTROL_CVT, &req);
}
#endif

int main(int argc, char* argv[])
{

  if (argc < 2) {
    fprintf(stderr, "Usage: guessccsid <file>\n");
    return 4;
  }
  const char* file_name = argv[1];
  FILE* fp = fopen(file_name, "rb");
  if (!fp) {
    fprintf(stderr, "Unable to open file %s for read\n", file_name);
    return 8;
  }
  #ifdef __MVS__
    if (!isatty(fileno(fp))) {
      disableautocvt(fileno(fp));
    }
  #endif  
  if (fseek(fp, 0L, SEEK_END)) {
    fprintf(stderr, "Unable to seek to end of file %s to determine size\n", file_name);
    return 12;
  }
  size_t size = ftell(fp);
  if (size < 0) {
    fprintf(stderr, "Size of file %s could not be determined\n", file_name);
    return 16;
  }
  rewind(fp);

  char* buffer = malloc(size);
  if (!buffer) {
    fprintf(stderr, "Unable to allocate buffer of %zu bytes for file %s - file too large?\n", size, file_name);
    return 20;
  }
  if (fread(buffer, 1, size, fp) != size) {
    fprintf(stderr, "Unable to read file %s into buffer\n", file_name);
    return 24;
  }

  enum guessccsid_result result = guessccsid(buffer, size);

  printf("guess:%s\n", ccsid_guess_toa(result));

  return 0;
}