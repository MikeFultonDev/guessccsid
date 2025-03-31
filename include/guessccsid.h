#ifndef __GUESSCCSID_H__ 
  #define __GUESSCCSID_H__ 1

  #include <stddef.h>

  enum guessccsid_result {
    CCSID_UNK=0,
    CCSID_BINARY,
    CCSID_EBCDIC,
    CCSID_ASCII,
    CCSID_UTF8,
    CCSID_UTF16,
    CCSID_EBCDIC_1047,
  };
  enum guessccsid_result guessccsid(const char* buffer, size_t len);

#endif