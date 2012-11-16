

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Fri Jan 13 19:32:30 2012
 */
/* Compiler settings for FileManagerServer.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IFSObject,0xECF461BA,0x2211,0x4956,0x89,0x64,0x15,0x97,0xC9,0xDC,0x55,0xF6);


MIDL_DEFINE_GUID(IID, IID_ICatalog,0x50D54F4B,0x1970,0x4BE4,0xB3,0xDE,0x26,0x69,0xC8,0xAC,0xC2,0x46);


MIDL_DEFINE_GUID(IID, IID_IFileObject,0xD3FFDFA7,0xD6D8,0x4FE5,0xA0,0x92,0xB4,0xD0,0xE4,0x75,0xE7,0x26);


MIDL_DEFINE_GUID(IID, IID_IFolderObject,0x4DC247C6,0x8261,0x48FC,0x97,0x64,0x09,0x49,0xD9,0xF6,0xB4,0x93);


MIDL_DEFINE_GUID(IID, LIBID_FileManagerServerLib,0xD101A9CA,0x88D3,0x4E7F,0xB2,0x52,0x6E,0xE5,0x84,0x2C,0xE6,0x55);


MIDL_DEFINE_GUID(CLSID, CLSID_FileObject,0x01018ECD,0xF895,0x4939,0xB9,0x09,0xAB,0x2E,0x11,0x78,0x14,0xF2);


MIDL_DEFINE_GUID(CLSID, CLSID_FolderObject,0x87F86C92,0x0F52,0x4468,0xBB,0xD4,0xB6,0x74,0x2F,0x2A,0xF9,0x6C);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



