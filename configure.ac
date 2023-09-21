# ======================================================================
# This is the HepPDT configuration input file
# Process this file with autoconf to produce a configure script.
# ======================================================================


# ----------------------------------------------------------------------
# Identify the package and initialize the autotools:
# ----------------------------------------------------------------------

AC_PREREQ(2.59)
AC_INIT([HepPDT],[2.06.01],[https://savannah.cern.ch/projects/heppdt/],[HepPDT])
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE(1.9 foreign)
AC_CONFIG_SRCDIR([src/HepPDT/Constituent.cc])
AC_CONFIG_SRCDIR([src/HepPID/ParticleName.cc])
AC_CONFIG_HEADER([include/HepPDT/defs.h])

# ----------------------------------------------------------------------
# --enable-shared and --enable-static
# both shared and static libraries are built by default
# ----------------------------------------------------------------------

AC_ARG_ENABLE(shared,
   AC_HELP_STRING([--disable-shared],[do not build shared libraries]),
        [case "${enableval}" in
          yes) build_shared="yes";;
          no)  build_shared="no";;
          *)   build_shared="yes";;
        esac],
        [build_shared="yes"])
AC_ARG_ENABLE(static,
   AC_HELP_STRING([--disable-static],[do not build static libraries]),
        [case "${enableval}" in
          yes) build_static="yes";;
          no)  build_static="no";;
          *)   build_static="yes";;
        esac],
        [build_static="yes"])
AC_ARG_ENABLE(visual,
   AC_HELP_STRING([--enable-visual],[on by default when using Visual C++]),
        [case "${enableval}" in
          yes) build_visual="yes";;
          no)  build_visual="no";;
          *)   build_visual="no";;
        esac],
        [build_visual="no"])

AC_ARG_ENABLE(gmake,
   AC_HELP_STRING([--enable-gmake],[use gmake (default is make)]),
        [case "${enableval}" in
          yes) use_gmake="yes";;
          no)  use_gmake="no";;
          *)   use_gmake="no";;
        esac],
        [use_gmake="no"])

# ----------------------------------------------------------------------
# Check for needed programs:
# ----------------------------------------------------------------------
AC_PROG_CXX
AC_PROG_CC
AC_PROG_MAKE_SET
AC_PROG_RANLIB

# ----------------------------------------------------------------------
# Checks for libraries.
# ----------------------------------------------------------------------

# ----------------------------------------------------------------------
# Checks for header files.
# ----------------------------------------------------------------------
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([stdint.h])

# ----------------------------------------------------------------------
# Checks for typedefs, structures, and compiler characteristics.
# ----------------------------------------------------------------------
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_CHECK_TYPES([ptrdiff_t])

# ----------------------------------------------------------------------
# Checks for library functions.
# ----------------------------------------------------------------------
AC_CHECK_FUNCS([pow sqrt])

# ----------------------------------------------------------------------
# Capture post-install information:
# ----------------------------------------------------------------------

# ----------------------------------------------------------------------
# Supply boilerplate for HepPDT/defs.h source header:
# ----------------------------------------------------------------------

AH_TOP([#ifndef HEPPDT_LITE_DEFS_H
#define HEPPDT_LITE_DEFS_H])

## the undefs are converted by configure
AH_VERBATIM([PACKAGE],[/* Name of package */
#ifndef PACKAGE
#undef PACKAGE
#endif])
AH_VERBATIM([PACKAGE_BUGREPORT],[/* Define to the address where bug reports for this package should be sent. */
#ifndef PACKAGE_BUGREPORT
#undef PACKAGE_BUGREPORT
#endif])
AH_VERBATIM([PACKAGE_NAME],[/* Define to the full name of this package. */
#ifndef PACKAGE_NAME
#undef PACKAGE_NAME
#endif])
AH_VERBATIM([PACKAGE_STRING],[/* Define to the full name and version of this package. */
#ifndef PACKAGE_STRING
#undef PACKAGE_STRING
#endif])
AH_VERBATIM([PACKAGE_TARNAME],[/* Define to the one symbol short name of this package. */
#ifndef PACKAGE_TARNAME
#undef PACKAGE_TARNAME
#endif])
AH_VERBATIM([PACKAGE_VERSION],[/* Define to the version of this package. */
#ifndef PACKAGE_VERSION
#undef PACKAGE_VERSION
#endif])
AH_VERBATIM([VERSION],[/* Version number of package */
#ifndef VERSION
#undef VERSION
#endif])

AH_BOTTOM([#endif  // HEPPDT_LITE_DEFS_H])


# ----------------------------------------------------------------------
# Account for any user configuration options:
# ----------------------------------------------------------------------


# ----------------------------------------------------------------------
# OS dependent differences:
# ----------------------------------------------------------------------

# copy and diff
case "$target" in
*-*-win32*)
  COPY_P="copy -p";DIFF_Q="diff -q -b"
  ;;
*-*-cygwin*)
  COPY_P="copy -p";DIFF_Q="diff -q -b"
  ;;
*-*-solaris*)
  COPY_P="cp -p";DIFF_Q="diff -b"
  use_gmake="yes"
  ;;
*-*-linux*)
  COPY_P="cp -p";DIFF_Q="diff -q -b"
  ;;
*-*-darwin*) 
  COPY_P="cp -p";DIFF_Q="diff -q -b"
  ;;
*)
  COPY_P="cp -p";DIFF_Q="diff -q -b"
esac

AM_CONDITIONAL(USE_GMAKE, test x$use_gmake = xyes)

AC_SUBST(COPY_P)
AC_SUBST(DIFF_Q)


# ----------------------------------------------------------------------
# compiler dependent differences
# notice that the default is presumed to be some flavor of g++
# ----------------------------------------------------------------------
case "$CXX" in
cl)  
   AM_CXXFLAGS="-EHsc -nologo -GR -MD"
   AR="ar"; ARFLAGS="cru"
   MY_SHFLAGS=" "; MY_SHLINK=" /NOLOGO"; SHEXT=lib
   MY_SHNAME="/OUT:"; MY_LD=" "
   build_static="no"
   build_shared="yes"
   build_visual="yes"
   ;;
CC)  
   AM_CXXFLAGS="-O"
   MY_SHFLAGS="-KPIC -DPIC"; MY_SHLINK="-G"; SHEXT=so
   MY_SHNAME="-h"; MY_LD="-R"
   AM_LDFLAGS="-lsunmath"
   AR="CC"; ARFLAGS="-xar -o"
   build_shared="no"
   ;;
*) 
   AM_CXXFLAGS="-O -ansi -pedantic -Wall -D_GNU_SOURCE"
   case "$target" in
   *-*-linux*) 
      MY_SHFLAGS="-fPIC -DPIC"; MY_SHLINK="-shared"; SHEXT=so
      MY_SHNAME="-Wl,-soname,"; MY_LD="-Wl,--rpath -Wl,"
      AR="ar"; ARFLAGS="cru"
      ;;
   *-*-darwin*) 
      MY_SHFLAGS="-fPIC -DPIC"; MY_SHLINK="-dynamiclib -single_module"; SHEXT=dylib
      MY_SHNAME="-Wl,-install_name,"; MY_LD="-Wl,--rpath -Wl,"
      AR="ar"; ARFLAGS="cru"
      build_shared="no"
      ;;
   *) 
      MY_SHFLAGS="-fPIC -DPIC"; MY_SHLINK="-shared"; SHEXT=so
      MY_SHNAME="-Wl,-soname,"; MY_LD="-Wl,--rpath -Wl,"
      AR="ar"; ARFLAGS="cru"
   esac;;
esac

AC_SUBST(AM_CXXFLAGS)
AC_SUBST(AM_LDFLAGS)
AC_SUBST(MY_SHFLAGS)
AC_SUBST(MY_SHLINK)
AC_SUBST(MY_SHNAME)
AC_SUBST(MY_LD)
AC_SUBST(SHEXT)
AC_SUBST(AR)
AC_SUBST(ARFLAGS)

AM_CONDITIONAL(BUILD_SHARED, test x$build_shared = xyes)
AM_CONDITIONAL(BUILD_STATIC, test x$build_static = xyes)
AM_CONDITIONAL(BUILD_VISUAL, test x$build_visual = xyes)

# ----------------------------------------------------------------------
# Identify the files that 'configure' is to produce:
# ----------------------------------------------------------------------

# Makefiles:
AC_CONFIG_FILES([Makefile
                 include/HepPDT/Makefile
                 include/HepPID/Makefile
                 src/HepPDT/Makefile
                 src/HepPID/Makefile
                 doc/HepPDT/Makefile
                 doc/HepPID/Makefile
                 data/Makefile
                 tests/HepPID/Makefile
                 tests/HepPDT/Makefile
		 tests/HepPDT/testHepPDT.input
		 tests/HepPDT/listPythiaNames.cc
		 tests/HepPDT/listPDGNames.cc
		 tests/HepPDT/listEvtGenNames.cc
		 tests/HepPDT/testReadParticleTable.cc
		 tests/HepPDT/testReadEvtGen.cc
		 tests/HepPDT/testReadIsajet.cc
		 tests/HepPDT/testReadQQ.cc
                 examples/data/Makefile
                 examples/HepPID/Makefile
                 examples/HepPID/GNUmakefile.example
                 examples/HepPDT/Makefile
                 examples/HepPDT/GNUmakefile.example])

# Test driver program/script:
AC_CONFIG_FILES([tests/HepPDT/testPID.sh], [chmod +x tests/HepPDT/testPID.sh])
AC_CONFIG_FILES([tests/HepPDT/testHepPDT.sh], [chmod +x tests/HepPDT/testHepPDT.sh])
AC_CONFIG_FILES([tests/HepPDT/listPythiaNames.sh], [chmod +x tests/HepPDT/listPythiaNames.sh])
AC_CONFIG_FILES([tests/HepPDT/listPDGNames.sh], [chmod +x tests/HepPDT/listPDGNames.sh])
AC_CONFIG_FILES([tests/HepPDT/listEvtGenNames.sh], [chmod +x tests/HepPDT/listEvtGenNames.sh])
AC_CONFIG_FILES([tests/HepPDT/testReadEvtGen.sh], [chmod +x tests/HepPDT/testReadEvtGen.sh])
AC_CONFIG_FILES([tests/HepPDT/testReadParticleTable.sh], [chmod +x tests/HepPDT/testReadParticleTable.sh])
AC_CONFIG_FILES([tests/HepPDT/testReadIsajet.sh], [chmod +x tests/HepPDT/testReadIsajet.sh])
AC_CONFIG_FILES([tests/HepPDT/testReadQQ.sh], [chmod +x tests/HepPDT/testReadQQ.sh])
AC_CONFIG_FILES([tests/HepPID/testParticleIDMethods.sh], [chmod +x tests/HepPID/testParticleIDMethods.sh])
AC_CONFIG_FILES([tests/HepPID/listParticleNames.sh], [chmod +x tests/HepPID/listParticleNames.sh])
AC_CONFIG_FILES([tests/HepPID/listIsajetTranslation.sh], [chmod +x tests/HepPID/listIsajetTranslation.sh])
AC_CONFIG_FILES([tests/HepPID/listHerwigTranslation.sh], [chmod +x tests/HepPID/listHerwigTranslation.sh])
AC_CONFIG_FILES([tests/HepPID/listEvtGenTranslation.sh], [chmod +x tests/HepPID/listEvtGenTranslation.sh])
AC_CONFIG_FILES([tests/HepPID/listPythiaTranslation.sh], [chmod +x tests/HepPID/listPythiaTranslation.sh])
AC_CONFIG_FILES([tests/HepPID/listPDGTranslation.sh], [chmod +x tests/HepPID/listPDGTranslation.sh])
AC_CONFIG_FILES([tests/HepPID/listQQTranslation.sh], [chmod +x tests/HepPID/listQQTranslation.sh])

# ----------------------------------------------------------------------
# Finish up:
# ----------------------------------------------------------------------

AC_OUTPUT


# ======================================================================
