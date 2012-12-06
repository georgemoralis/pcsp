#ifndef TYPES_H_
#define TYPES_H_

typedef long long s64;
typedef int s32;
typedef short s16;
typedef char s8;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef float f32;

#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("TODO - " #x))

#ifdef __GNUC__
#define __forceinline inline __attribute__((always_inline))
#endif

typedef u64 insn_count_t;

#if defined(WIN32) || defined(__WINS__) || defined(__MINGW32__) || defined(_MSC_VER)
#define inline __inline
#define snprintf _snprintf
#endif

class NonCopyable 
{
private:
    NonCopyable(const NonCopyable &);
    const NonCopyable &operator =(const NonCopyable &);
public:
    NonCopyable() {}
    ~NonCopyable() {}
};

#endif /* TYPES_H_ */