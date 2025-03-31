#include "guessccsid.h"
#include <stdbool.h>

enum guessccsid_result guessccsid(const char* buffer, size_t len)
{
  enum guessccsid_result result = CCSID_UNK;
  bool done = false;
  for (int i=0; i<len && !done; ++i) {
    char c = buffer[i];
    switch (c) {
      case 0:
        /*
         * If embedded NULLs hit, mark as binary and break out of loop
         */
        result = CCSID_BINARY;
        done = true;
        break;
      case 0x40:
        /*
         * This is an EBCDIC blank. If unknown, move it to EBCDIC.
         */
        if (result == CCSID_UNK) {
          result = CCSID_EBCDIC;
        }
        break;
    }
  }

  return result;
}