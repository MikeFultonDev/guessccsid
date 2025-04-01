#include "guessccsid.h"
#include <stdbool.h>
#include <stdio.h>

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
      case 0x0A:
        /*
         * This is probably an ASCII newline.
         */
        if (result == CCSID_UNK) {
          result = CCSID_ASCII;
        }
        break;       
      case 0x15:
        /*
         * This is probably an EBCDIC newline.
         */
        if (result == CCSID_UNK) {
          result = CCSID_EBCDIC;
        }
        break;
      case 0x0E:
        /*
         * This is probably an ASCII or EBCDIC Shift-Out (indicating DBCS)
         */
        if (result != CCSID_BINARY) {
          if (result == CCSID_UNK) {
            result = CCSID_DBCS;
          } else if (result == CCSID_EBCDIC) {
            result = CCSID_DBCS_EBCDIC;
          } else if (result == CCSID_ASCII) {
            result = CCSID_DBCS_ASCII;
          }
          /*
          * Skip over characters until Shift-In is encountered 
          */
          while (i < len && (buffer[++i] != 0x0F));
        }
        break;

      default: {
        /*
         * If UTF8 characters are at the very start of the buffer, the buffer guess will
         * not be ASCII yet and the 'guess' will end up being EBCDIC.
         */
        if ((c & 0xC0) == 0xC0) {
          /*
           * First byte of UTF8 2-byte character?
           * Only if no EBCDIC seen (these are letters A to I in EBCDIC)
           */

          if (result == CCSID_ASCII || result == CCSID_UNK) {
            if ((i+1 < len) && ((buffer[i+1] & 0x80) == 0x80)) {
              ++i;
              result = CCSID_UTF8;
            } else {
              /*
               * This is not valid UTF8 - it could be ASCII, or it could be binary.
               */
              result = CCSID_BINARY;
            }
          } else {
            result = CCSID_EBCDIC;
          }
        } else if ((c & 0xE0) == 0xE0) {
          /*
           * First byte of UTF8 3-byte character?
           * Only if no EBCDIC seen (these are letters S to Z in EBCDIC)
           */
          if (result == CCSID_ASCII || result == CCSID_UNK) {
            if ((i+2 < len) && ((buffer[i+1] & 0x80) == 0x80) && ((buffer[i+2] & 0x80) == 0x80)) {
              i+=2;
              result = CCSID_UTF8;
            } else {
              /*
               * This is not valid UTF8 - it could be ASCII, or it could be binary.
               */
              result = CCSID_BINARY;
            }
          } else {
            result = CCSID_EBCDIC;
          }          
        } else if ((c & 0xF0) == 0xF0) {
          /*
          * First byte of UTF8 4-byte character?
          * Only if no EBCDIC seen (these are letters 0 to 9 in EBCDIC)
          */
          if (result == CCSID_ASCII || result == CCSID_UNK) {
            if ((i+3 < len) && ((buffer[i+1] & 0x80) == 0x80) && ((buffer[i+2] & 0x80) == 0x80) && ((buffer[i+3] & 0x80) == 0x80)) {
              i+=3;
              result = CCSID_UTF8;
            } else {
              /*
              * This is not valid UTF8 - it could be ASCII, or it could be binary.
              */
              result = CCSID_BINARY;
            }
          } else {
            result = CCSID_EBCDIC;
          }          
        }
        break;
      }
    }
  }

  return result;
}

const char* ccsid_guess_toa(enum guessccsid_result result)
{
  switch(result) {
    case CCSID_UNK: return "CCSID_UNK";
    case CCSID_BINARY: return "CCSID_BINARY";
    case CCSID_EBCDIC: return "CCSID_EBCDIC";
    case CCSID_ASCII: return "CCSID_ASCII";
    case CCSID_UTF8: return "CCSID_UTF8";
    case CCSID_UTF16: return "CCSID_UTF16";
    case CCSID_DBCS: return "CCSID_DBCS";
    case CCSID_DBCS_ASCII: return "CCSID_DBCS_ASCII";
    case CCSID_DBCS_EBCDIC: return "CCSID_DBCS_EBCDIC";
    case CCSID_EBCDIC_1047: return "CCSID_EBCDIC_1047";
    default: return "unknown ccsid";
  }
}