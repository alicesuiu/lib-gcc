typedef char SINT8;
typedef unsigned char UINT8;
typedef unsigned UINT32;
typedef signed SINT32;

#if __GNUC__ || defined LINUX || defined SUNOS
typedef unsigned long long UINT64;
typedef signed long long SINT64;
#else
typedef unsigned __int64 UINT64;
typedef signed __int64 SINT64;
#endif

#define USItype UINT32;
#define SItype SINT32;
#define UDItype UINT64;
#define DItype SINT64;

typedef		 int QItype	__attribute__ ((mode (QI)));
typedef unsigned int UQItype	__attribute__ ((mode (QI)));
typedef		 int HItype	__attribute__ ((mode (HI)));
typedef unsigned int UHItype	__attribute__ ((mode (HI)));
#if MIN_UNITS_PER_WORD > 1
/* These typedefs are usually forbidden on dsp's with UNITS_PER_WORD 1.  */
typedef 	 int SItype	__attribute__ ((mode (SI)));
typedef unsigned int USItype	__attribute__ ((mode (SI)));
#if __SIZEOF_LONG_LONG__ > 4
/* These typedefs are usually forbidden on archs with UNITS_PER_WORD 2.  */
typedef		 int DItype	__attribute__ ((mode (DI)));
typedef unsigned int UDItype	__attribute__ ((mode (DI)));
#if MIN_UNITS_PER_WORD > 4
/* These typedefs are usually forbidden on archs with UNITS_PER_WORD 4.  */
typedef		 int TItype	__attribute__ ((mode (TI)));
typedef unsigned int UTItype	__attribute__ ((mode (TI)));
#endif
#endif
#endif

#if LIBGCC2_HAS_HF_MODE
typedef		float HFtype	__attribute__ ((mode (HF)));
typedef _Complex float HCtype	__attribute__ ((mode (HC)));
#endif
#if LIBGCC2_HAS_SF_MODE
typedef 	float SFtype	__attribute__ ((mode (SF)));
typedef _Complex float SCtype	__attribute__ ((mode (SC)));
#endif
#if LIBGCC2_HAS_DF_MODE
typedef		float DFtype	__attribute__ ((mode (DF)));
typedef _Complex float DCtype	__attribute__ ((mode (DC)));
#endif
#if LIBGCC2_HAS_XF_MODE
typedef		float XFtype	__attribute__ ((mode (XF)));
typedef _Complex float XCtype	__attribute__ ((mode (XC)));
#endif
#if LIBGCC2_HAS_TF_MODE
typedef		float TFtype	__attribute__ ((mode (TF)));
typedef _Complex float TCtype	__attribute__ ((mode (TC)));
#endif


#if LIBGCC2_UNITS_PER_WORD == 8
#define W_TYPE_SIZE (8 * __CHAR_BIT__)
#define Wtype	DItype
#define UWtype	UDItype
#define HWtype	DItype
#define UHWtype	UDItype
#define DWtype	TItype
#define UDWtype	UTItype
#ifdef LIBGCC2_GNU_PREFIX
#define __NW(a,b)	__gnu_ ## a ## di ## b
#define __NDW(a,b)	__gnu_ ## a ## ti ## b
#else
#define __NW(a,b)	__ ## a ## di ## b
#define __NDW(a,b)	__ ## a ## ti ## b
#endif
#define COMPAT_SIMODE_TRAPPING_ARITHMETIC
#elif LIBGCC2_UNITS_PER_WORD == 4
#define W_TYPE_SIZE (4 * __CHAR_BIT__)
#define Wtype	SItype
#define UWtype	USItype
#define HWtype	SItype
#define UHWtype	USItype
#define DWtype	DItype
#define UDWtype	UDItype
#ifdef LIBGCC2_GNU_PREFIX
#define __NW(a,b)	__gnu_ ## a ## si ## b
#define __NDW(a,b)	__gnu_ ## a ## di ## b
#else
#define __NW(a,b)	__ ## a ## si ## b
#define __NDW(a,b)	__ ## a ## di ## b
#endif
#elif LIBGCC2_UNITS_PER_WORD == 2
#define W_TYPE_SIZE (2 * __CHAR_BIT__)
#define Wtype	HItype
#define UWtype	UHItype
#define HWtype	HItype
#define UHWtype	UHItype
#define DWtype	SItype
#define UDWtype	USItype
#ifdef LIBGCC2_GNU_PREFIX
#define __NW(a,b)	__gnu_ ## a ## hi ## b
#define __NDW(a,b)	__gnu_ ## a ## si ## b
#else
#define __NW(a,b)	__ ## a ## hi ## b
#define __NDW(a,b)	__ ## a ## si ## b
#endif
#else
#define W_TYPE_SIZE __CHAR_BIT__
#define Wtype	QItype
#define UWtype  UQItype
#define HWtype	QItype
#define UHWtype	UQItype
#define DWtype	HItype
#define UDWtype	UHItype
#ifdef LIBGCC2_GNU_PREFIX
#define __NW(a,b)	__gnu_ ## a ## qi ## b
#define __NDW(a,b)	__gnu_ ## a ## hi ## b
#else
#define __NW(a,b)	__ ## a ## qi ## b
#define __NDW(a,b)	__ ## a ## hi ## b
#endif
#endif

/* DWstructs are pairs of Wtype values in the order determined by
   __BYTE_ORDER__.  */

#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
  struct DWstruct {Wtype high, low;};
#else
  struct DWstruct {Wtype low, high;};
#endif

typedef union
{
  struct DWstruct s;
  DWtype ll;
} DWunion;