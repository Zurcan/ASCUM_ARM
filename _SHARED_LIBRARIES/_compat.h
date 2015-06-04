#ifndef __compat
#define __compat

#ifdef __arm__arm__
  #define __flash const
  #define  _gen_int8 unsigned int
#endif
#ifdef __AVR__AVR__
  #define __packed
  #define  _gen_int8 unsigned char
#endif
#ifdef __ATOM__ATOM__
  #define __flash const
  #define  _gen_int8 unsigned char
#endif


#endif
