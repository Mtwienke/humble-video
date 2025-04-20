dnl Override broken AC_C_BIGENDIAN
AC_DEFUN([AC_C_BIGENDIAN], [
  AC_MSG_CHECKING([for byte order])
  AC_MSG_RESULT([assuming little endian])
  AC_DEFINE(WORDS_BIGENDIAN, 0, [Define to 1 if your system is big endian])
])
