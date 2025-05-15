#if 0
#pragma _class(QtSystemDetection)
#pragma sync_skip_header_check
#pragma sync_stop_processing
#endif

#ifndef UTILS_SYSTEMDETECTION_H_
#define UTILS_SYSTEMDETECTION_H_

/*
   The operating system, must be one of: (E_OS_x)

     DARWIN   - Any Darwin system (macOS, iOS, watchOS, tvOS)
     MACOS    - macOS
     IOS      - iOS
     WATCHOS  - watchOS
     TVOS     - tvOS
     WIN32    - Win32 (Windows 2000/XP/Vista/7 and Windows Server 2003/2008)
     CYGWIN   - Cygwin
     SOLARIS  - Sun Solaris
     HPUX     - HP-UX
     LINUX    - Linux [has variants]
     FREEBSD  - FreeBSD [has variants]
     NETBSD   - NetBSD
     OPENBSD  - OpenBSD
     INTERIX  - Interix
     AIX      - AIX
     HURD     - GNU Hurd
     QNX      - QNX [has variants]
     QNX6     - QNX RTP 6.1
     LYNX     - LynxOS
     BSD4     - Any BSD 4.4 system
     UNIX     - Any UNIX BSD/SYSV system
     ANDROID  - Android platform
     HAIKU    - Haiku
     WEBOS    - LG WebOS
     WASM     - WebAssembly

   The following operating systems have variants:
     LINUX    - both E_OS_LINUX and E_OS_ANDROID are defined when building for Android
              - only E_OS_LINUX is defined if building for other Linux systems
     MACOS    - both E_OS_BSD4 and E_OS_IOS are defined when building for iOS
              - both E_OS_BSD4 and E_OS_MACOS are defined when building for macOS
     FREEBSD  - E_OS_FREEBSD is defined only when building for FreeBSD with a BSD userland
              - E_OS_FREEBSD_KERNEL is always defined on FreeBSD, even if the userland is from GNU
*/

#if defined(__APPLE__) && (defined(__GNUC__) || defined(__xlC__) || defined(__xlc__))
#  include <TargetConditionals.h>
#  define E_OS_APPLE
#  if defined(TARGET_OS_MAC) && TARGET_OS_MAC
#    define E_OS_DARWIN
#    define E_OS_BSD4
#    if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
#      define E_PLATFORM_UIKIT
#      if defined(TARGET_OS_WATCH) && TARGET_OS_WATCH
#        define E_OS_WATCHOS
#      elif defined(TARGET_OS_TV) && TARGET_OS_TV
#        define E_OS_TVOS
#      else
#        // TARGET_OS_IOS is only available in newer SDKs,
#        // so assume any other iOS-based platform is iOS for now
#        define E_OS_IOS
#      endif
#    else
#      // TARGET_OS_OSX is only available in newer SDKs,
#      // so assume any non iOS-based platform is macOS for now
#      define E_OS_MACOS
#    endif
#  else
#    error "Qt has not been ported to this Apple platform - see http://www.qt.io/developers"
#  endif
#elif defined(__WEBOS__)
#  define E_OS_WEBOS
#  define E_OS_LINUX
#elif defined(__ANDROID__) || defined(ANDROID)
#  define E_OS_ANDROID
#  define E_OS_LINUX
#elif defined(__CYGWIN__)
#  define E_OS_CYGWIN
#elif !defined(SAG_COM) && (!defined(WINAPI_FAMILY) || WINAPI_FAMILY==WINAPI_FAMILY_DESKTOP_APP) && (defined(WIN64) || defined(_WIN64) || defined(__WIN64__))
#  define E_OS_WIN32
#  define E_OS_WIN64
#elif !defined(SAG_COM) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
#    define E_OS_WIN32
#elif defined(__sun) || defined(sun)
#  define E_OS_SOLARIS
#elif defined(hpux) || defined(__hpux)
#  define E_OS_HPUX
#elif defined(__EMSCRIPTEN__)
#  define E_OS_WASM
#elif defined(__linux__) || defined(__linux)
#  define E_OS_LINUX
#elif defined(__FreeBSD__) || defined(__DragonFly__) || defined(__FreeBSD_kernel__)
#  ifndef __FreeBSD_kernel__
#    define E_OS_FREEBSD
#  endif
#  define E_OS_FREEBSD_KERNEL
#  define E_OS_BSD4
#elif defined(__NetBSD__)
#  define E_OS_NETBSD
#  define E_OS_BSD4
#elif defined(__OpenBSD__)
#  define E_OS_OPENBSD
#  define E_OS_BSD4
#elif defined(__INTERIX)
#  define E_OS_INTERIX
#  define E_OS_BSD4
#elif defined(_AIX)
#  define E_OS_AIX
#elif defined(__Lynx__)
#  define E_OS_LYNX
#elif defined(__GNU__)
#  define E_OS_HURD
#elif defined(__QNXNTO__)
#  define E_OS_QNX
#elif defined(__INTEGRITY)
#  define E_OS_INTEGRITY
#elif defined(__rtems__)
#  define E_OS_RTEMS
#elif defined(VXWORKS) /* there is no "real" VxWorks define - this has to be set in the mkspec! */
#  define E_OS_VXWORKS
#elif defined(__HAIKU__)
#  define E_OS_HAIKU
#elif defined(__MAKEDEPEND__)
#else
#  error "Qt has not been ported to this OS - see http://www.qt-project.org/"
#endif

#if defined(E_OS_WIN32) || defined(E_OS_WIN64)
#  define E_OS_WINDOWS
#  define E_OS_WIN
// On Windows, pointers to dllimport'ed variables are not constant expressions,
// so to keep to certain initializations (like QMetaObject) constexpr, we need
// to use functions instead.
#  define E_NO_DATA_RELOCATION
#endif

#if defined(E_OS_WIN)
#  undef E_OS_UNIX
#elif !defined(E_OS_UNIX)
#  define E_OS_UNIX
#endif

// Compatibility synonyms
#ifdef E_OS_DARWIN
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  define E_OS_MAC // FIXME: Deprecate
#  ifdef __LP64__
#    define E_OS_DARWIN64
#    pragma clang deprecated(E_OS_DARWIN64, "use E_OS_DARWIN and E_POINTER_SIZE/E_PROCESSOR_* instead")
#    define E_OS_MAC64
#    pragma clang deprecated(E_OS_MAC64, "use E_OS_DARWIN and E_POINTER_SIZE/E_PROCESSOR_* instead")
#  else
#    define E_OS_DARWIN32
#    pragma clang deprecated(E_OS_DARWIN32, "use E_OS_DARWIN and E_POINTER_SIZE/E_PROCESSOR_* instead")
#    define E_OS_MAC32
#    pragma clang deprecated(E_OS_MAC32, "use E_OS_DARWIN and E_POINTER_SIZE/E_PROCESSOR_* instead")
#  endif
#  ifdef E_OS_MACOS
#    define E_OS_MACX
#    pragma clang deprecated(E_OS_MACX, "use E_OS_MACOS instead")
#    define E_OS_OSX
#    pragma clang deprecated(E_OS_OSX, "use E_OS_MACOS instead")
#  endif
#  pragma clang diagnostic pop
#endif

#ifdef E_OS_DARWIN
#  include <Availability.h>
#  include <AvailabilityMacros.h>

#  define E_DARWIN_PLATFORM_SDK_EQUAL_OR_ABOVE(macos, ios, tvos, watchos) \
    ((defined(__MAC_OS_X_VERSION_MAX_ALLOWED) && macos != __MAC_NA && __MAC_OS_X_VERSION_MAX_ALLOWED >= macos) || \
     (defined(__IPHONE_OS_VERSION_MAX_ALLOWED) && ios != __IPHONE_NA && __IPHONE_OS_VERSION_MAX_ALLOWED >= ios) || \
     (defined(__TV_OS_VERSION_MAX_ALLOWED) && tvos != __TVOS_NA && __TV_OS_VERSION_MAX_ALLOWED >= tvos) || \
     (defined(__WATCH_OS_VERSION_MAX_ALLOWED) && watchos != __WATCHOS_NA && __WATCH_OS_VERSION_MAX_ALLOWED >= watchos))

#  define E_DARWIN_DEPLOYMENT_TARGET_BELOW(macos, ios, tvos, watchos) \
    ((defined(__MAC_OS_X_VERSION_MIN_REQUIRED) && macos != __MAC_NA && __MAC_OS_X_VERSION_MIN_REQUIRED < macos) || \
     (defined(__IPHONE_OS_VERSION_MIN_REQUIRED) && ios != __IPHONE_NA && __IPHONE_OS_VERSION_MIN_REQUIRED < ios) || \
     (defined(__TV_OS_VERSION_MIN_REQUIRED) && tvos != __TVOS_NA && __TV_OS_VERSION_MIN_REQUIRED < tvos) || \
     (defined(__WATCH_OS_VERSION_MIN_REQUIRED) && watchos != __WATCHOS_NA && __WATCH_OS_VERSION_MIN_REQUIRED < watchos))

#  define E_MACOS_IOS_PLATFORM_SDK_EQUAL_OR_ABOVE(macos, ios) \
      E_DARWIN_PLATFORM_SDK_EQUAL_OR_ABOVE(macos, ios, __TVOS_NA, __WATCHOS_NA)
#  define E_MACOS_PLATFORM_SDK_EQUAL_OR_ABOVE(macos) \
      E_DARWIN_PLATFORM_SDK_EQUAL_OR_ABOVE(macos, __IPHONE_NA, __TVOS_NA, __WATCHOS_NA)
#  define E_IOS_PLATFORM_SDK_EQUAL_OR_ABOVE(ios) \
      E_DARWIN_PLATFORM_SDK_EQUAL_OR_ABOVE(__MAC_NA, ios, __TVOS_NA, __WATCHOS_NA)
#  define E_TVOS_PLATFORM_SDK_EQUAL_OR_ABOVE(tvos) \
      E_DARWIN_PLATFORM_SDK_EQUAL_OR_ABOVE(__MAC_NA, __IPHONE_NA, tvos, __WATCHOS_NA)
#  define E_WATCHOS_PLATFORM_SDK_EQUAL_OR_ABOVE(watchos) \
      E_DARWIN_PLATFORM_SDK_EQUAL_OR_ABOVE(__MAC_NA, __IPHONE_NA, __TVOS_NA, watchos)

#  define E_MACOS_IOS_DEPLOYMENT_TARGET_BELOW(macos, ios) \
      E_DARWIN_DEPLOYMENT_TARGET_BELOW(macos, ios, __TVOS_NA, __WATCHOS_NA)
#  define E_MACOS_DEPLOYMENT_TARGET_BELOW(macos) \
      E_DARWIN_DEPLOYMENT_TARGET_BELOW(macos, __IPHONE_NA, __TVOS_NA, __WATCHOS_NA)
#  define E_IOS_DEPLOYMENT_TARGET_BELOW(ios) \
      E_DARWIN_DEPLOYMENT_TARGET_BELOW(__MAC_NA, ios, __TVOS_NA, __WATCHOS_NA)
#  define E_TVOS_DEPLOYMENT_TARGET_BELOW(tvos) \
      E_DARWIN_DEPLOYMENT_TARGET_BELOW(__MAC_NA, __IPHONE_NA, tvos, __WATCHOS_NA)
#  define E_WATCHOS_DEPLOYMENT_TARGET_BELOW(watchos) \
      E_DARWIN_DEPLOYMENT_TARGET_BELOW(__MAC_NA, __IPHONE_NA, __TVOS_NA, watchos)

#else // !E_OS_DARWIN

#define E_DARWIN_PLATFORM_SDK_EQUAL_OR_ABOVE(macos, ios, tvos, watchos) (0)
#define E_MACOS_IOS_PLATFORM_SDK_EQUAL_OR_ABOVE(macos, ios) (0)
#define E_MACOS_PLATFORM_SDK_EQUAL_OR_ABOVE(macos) (0)
#define E_IOS_PLATFORM_SDK_EQUAL_OR_ABOVE(ios) (0)
#define E_TVOS_PLATFORM_SDK_EQUAL_OR_ABOVE(tvos) (0)
#define E_WATCHOS_PLATFORM_SDK_EQUAL_OR_ABOVE(watchos) (0)

#endif // E_OS_DARWIN

#ifdef __LSB_VERSION__
#  if __LSB_VERSION__ < 40
#    error "This version of the Linux Standard Base is unsupported"
#  endif
#ifndef E_LINUXBASE
#  define E_LINUXBASE
#endif
#endif

#if defined (__ELF__)
#  define E_OF_ELF
#endif
#if defined (__MACH__) && defined (__APPLE__)
#  define E_OF_MACH_O
#endif

#endif // UTILS_SYSTEMDETECTION_H_
