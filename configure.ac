#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([redis_ae_example], [1.0], [lizhenghn@gmail.com])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([deps/ae/ae.c])
AM_INIT_AUTOMAKE(redis_ae_example,1.0)
AC_PROG_LIBTOOL

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([pthread], [main])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h netdb.h netinet/in.h stdint.h stdlib.h string.h sys/socket.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_MKTIME
AC_CHECK_FUNCS([bzero gethostbyname gettimeofday memset mkdir select socket strchr strerror])

dnl Check if we're a little-endian or a big-endian system, needed by hash code
AC_DEFUN([AC_C_ENDIAN],
[AC_CACHE_CHECK(for endianness, ac_cv_c_endian,
[
  AC_RUN_IFELSE(
    [AC_LANG_PROGRAM([], [dnl
        long val = 1;
        char *c = (char *) &val;
        exit(*c == 1);
    ])
  ],[
    ac_cv_c_endian=big
  ],[
    ac_cv_c_endian=little
  ])
])
if test $ac_cv_c_endian = big; then
  AC_DEFINE(ENDIAN_BIG, 1, [machine is bigendian])
fi
if test $ac_cv_c_endian = little; then
  AC_DEFINE(ENDIAN_LITTLE, 1, [machine is littleendian])
fi
])

AC_C_ENDIAN


AC_CONFIG_FILES([Makefile
                deps/Makefile
                deps/ae/Makefile
                examples/Makefile
               ])

AC_OUTPUT
