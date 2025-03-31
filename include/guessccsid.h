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
    CCSID_DBCS,
    CCSID_DBCS_ASCII,
    CCSID_DBCS_EBCDIC,
    CCSID_EBCDIC_1047,
  };
  enum guessccsid_result guessccsid(const char* buffer, size_t len);
  const char* ccsid_guess_toa(enum guessccsid_result result);

#endif
