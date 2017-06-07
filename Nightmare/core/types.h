
/*
  
  Nightmareライブラリで使用する型の定義を行うヘッダーファイル

  iron_dice

 */

#ifndef __NM_TYPE_H__
#define __NM_TYPE_H__

namespace dream
{

// ----------------------------------------------------------------------
// 
// 基本型
// 
// ----------------------------------------------------------------------

// メモリ領域の量を表した型

using s8	= __int8;
using s16	= __int16;
using s32	= __int32;
using s64	= __int64;
using u8	= unsigned __int8;
using u16	= unsigned __int16;
using u32	= unsigned __int32;
using u64	= unsigned __int64;

using vs8	= volatile s8;
using vs16	= volatile s16;
using vs32	= volatile s32;
using vs64	= volatile s64;
using vu8	= volatile u8;
using vu16	= volatile u16;
using vu32	= volatile u32;
using vu64	= volatile u64;

using f32	= float;
using f64	= double;
using vf32	= volatile f32;
using vf64	= volatile f64;

// 基本型の型

using schar		= signed char;
using sshort	= signed short;
using sint		= signed int;
using slong		= signed long;
using uchar		= unsigned char;
using ushort	= unsigned short;
using uint		= unsigned int;
using ulong		= unsigned long;

using vschar    = volatile schar;
using vsshort   = volatile sshort;
using vsint		= volatile sint;
using vslong	= volatile slong;
using vuchar	= volatile uchar;
using vushort	= volatile ushort;
using vuint		= volatile uint;
using vulong	= volatile ulong;

// 独自の型

using byte		= u8;

} // namespace dream

#endif // __NM_TYPE_H__
