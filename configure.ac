# Process this file with autoconf to produce a configure script.
AC_INIT([dpmsnotify],[0.0.0])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([dpmsnotify.c])
# Make builds less verbose.  Shuts off Makefile portability checks.
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

# Check for compiler and install
AC_PROG_CC
AC_PROG_INSTALL

# Check for xcb and xcb-dpms
PKG_CHECK_MODULES([XCB],[xcb])
PKG_CHECK_MODULES([XCB_DPMS],[xcb-dpms])

AC_SUBST([XCB_CFLAGS])
AC_SUBST([XCB_LIBS])

AC_SUBST([XCB_DPMS_CFLAGS])
AC_SUBST([XCB_DPMS_LIBS])

# generate
AC_CONFIG_FILES([
Makefile
])
AC_OUTPUT
