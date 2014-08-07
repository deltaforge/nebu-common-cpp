# Define basic library information
AC_PREREQ(2.61)
AC_INIT([libnebu-common], [0.1.0], [])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([1.11 foreign subdir-objects])
LT_PREREQ([2.2])

# Check for programs
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_LIBTOOL

# Check for libraries
PKG_CHECK_MODULES([TINYXML2], [tinyxml2])
AC_SUBST([TINYXML2_CFLAGS])
AC_SUBST([TINYXML2_LIBS])

# Define test configuration option
AC_ARG_ENABLE([tests],
	[	--enable-tests   Turn on test and coverage flags],
	[case "${enableval}" in
	  yes) tests=true ;;
	  no)  tests=false ;;
	  *) AC_MSG_ERROR([bad value ${enableval} for --enable-tests]) ;;
	esac],[tests=false])
AM_CONDITIONAL([TESTS_ENABLED], [test x$tests = xtrue])

# Set flags
AM_CPPFLAGS="-I\$(top_srcdir)/include"
AC_SUBST([AM_CPPFLAGS])

# Define Makefiles
AC_CONFIG_FILES([
	Makefile
	include/Makefile
	src/Makefile
	doc/doxygen.cfg
	doc/Makefile
	test/Makefile
	libnebu-common.pc
])

# Generate 'configure' 
AC_OUTPUT
