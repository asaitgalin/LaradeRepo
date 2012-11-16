

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __FileManagerServer_i_h__
#define __FileManagerServer_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IFSObject_FWD_DEFINED__
#define __IFSObject_FWD_DEFINED__
typedef interface IFSObject IFSObject;
#endif 	/* __IFSObject_FWD_DEFINED__ */


#ifndef __ICatalog_FWD_DEFINED__
#define __ICatalog_FWD_DEFINED__
typedef interface ICatalog ICatalog;
#endif 	/* __ICatalog_FWD_DEFINED__ */


#ifndef __IFileObject_FWD_DEFINED__
#define __IFileObject_FWD_DEFINED__
typedef interface IFileObject IFileObject;
#endif 	/* __IFileObject_FWD_DEFINED__ */


#ifndef __IFolderObject_FWD_DEFINED__
#define __IFolderObject_FWD_DEFINED__
typedef interface IFolderObject IFolderObject;
#endif 	/* __IFolderObject_FWD_DEFINED__ */


#ifndef __FileObject_FWD_DEFINED__
#define __FileObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class FileObject FileObject;
#else
typedef struct FileObject FileObject;
#endif /* __cplusplus */

#endif 	/* __FileObject_FWD_DEFINED__ */


#ifndef __FolderObject_FWD_DEFINED__
#define __FolderObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class FolderObject FolderObject;
#else
typedef struct FolderObject FolderObject;
#endif /* __cplusplus */

#endif 	/* __FolderObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IFSObject_INTERFACE_DEFINED__
#define __IFSObject_INTERFACE_DEFINED__

/* interface IFSObject */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IFSObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ECF461BA-2211-4956-8964-1597C9DC55F6")
    IFSObject : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ BSTR path) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetFullPath( 
            /* [retval][out] */ BSTR *path) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Open( 
            /* [retval][out] */ BOOL *isDir) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Copy( 
            /* [in] */ BSTR dest) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ BSTR dest) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Rename( 
            /* [in] */ BSTR newName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE isDir( 
            /* [retval][out] */ BOOL *bIsDir) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetCaption( 
            /* [retval][out] */ BSTR *caption) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFSObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFSObject * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFSObject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFSObject * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IFSObject * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IFSObject * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IFSObject * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IFSObject * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IFSObject * This,
            /* [in] */ BSTR path);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetFullPath )( 
            IFSObject * This,
            /* [retval][out] */ BSTR *path);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Open )( 
            IFSObject * This,
            /* [retval][out] */ BOOL *isDir);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Copy )( 
            IFSObject * This,
            /* [in] */ BSTR dest);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Delete )( 
            IFSObject * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Move )( 
            IFSObject * This,
            /* [in] */ BSTR dest);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Rename )( 
            IFSObject * This,
            /* [in] */ BSTR newName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *isDir )( 
            IFSObject * This,
            /* [retval][out] */ BOOL *bIsDir);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetCaption )( 
            IFSObject * This,
            /* [retval][out] */ BSTR *caption);
        
        END_INTERFACE
    } IFSObjectVtbl;

    interface IFSObject
    {
        CONST_VTBL struct IFSObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFSObject_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFSObject_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFSObject_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFSObject_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IFSObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IFSObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IFSObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IFSObject_Initialize(This,path)	\
    ( (This)->lpVtbl -> Initialize(This,path) ) 

#define IFSObject_GetFullPath(This,path)	\
    ( (This)->lpVtbl -> GetFullPath(This,path) ) 

#define IFSObject_Open(This,isDir)	\
    ( (This)->lpVtbl -> Open(This,isDir) ) 

#define IFSObject_Copy(This,dest)	\
    ( (This)->lpVtbl -> Copy(This,dest) ) 

#define IFSObject_Delete(This)	\
    ( (This)->lpVtbl -> Delete(This) ) 

#define IFSObject_Move(This,dest)	\
    ( (This)->lpVtbl -> Move(This,dest) ) 

#define IFSObject_Rename(This,newName)	\
    ( (This)->lpVtbl -> Rename(This,newName) ) 

#define IFSObject_isDir(This,bIsDir)	\
    ( (This)->lpVtbl -> isDir(This,bIsDir) ) 

#define IFSObject_GetCaption(This,caption)	\
    ( (This)->lpVtbl -> GetCaption(This,caption) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFSObject_INTERFACE_DEFINED__ */


#ifndef __ICatalog_INTERFACE_DEFINED__
#define __ICatalog_INTERFACE_DEFINED__

/* interface ICatalog */
/* [object][version][uuid] */ 


EXTERN_C const IID IID_ICatalog;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("50D54F4B-1970-4BE4-B3DE-2669C8ACC246")
    ICatalog : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ReloadFiles( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFilesCount( 
            /* [retval][out] */ LONG *filesCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFileName( 
            /* [in] */ LONG index,
            /* [retval][out] */ BSTR *fileName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFileSystemEntriesCount( 
            /* [retval][out] */ LONG *entriesCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFileSystemEntryName( 
            /* [in] */ LONG index,
            /* [retval][out] */ BSTR *entryName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDirectoriesCount( 
            /* [retval][out] */ LONG *directoriesCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDirectoryName( 
            /* [in] */ LONG index,
            /* [retval][out] */ BSTR *directoryName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFile( 
            /* [in] */ LONG index,
            /* [retval][out] */ IFSObject **file) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateFile( 
            /* [in] */ BSTR name) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateDirectory( 
            /* [in] */ BSTR name) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ BSTR path) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFullPath( 
            /* [retval][out] */ BSTR *path) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICatalogVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICatalog * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICatalog * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICatalog * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICatalog * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICatalog * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICatalog * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICatalog * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *ReloadFiles )( 
            ICatalog * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetFilesCount )( 
            ICatalog * This,
            /* [retval][out] */ LONG *filesCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetFileName )( 
            ICatalog * This,
            /* [in] */ LONG index,
            /* [retval][out] */ BSTR *fileName);
        
        HRESULT ( STDMETHODCALLTYPE *GetFileSystemEntriesCount )( 
            ICatalog * This,
            /* [retval][out] */ LONG *entriesCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetFileSystemEntryName )( 
            ICatalog * This,
            /* [in] */ LONG index,
            /* [retval][out] */ BSTR *entryName);
        
        HRESULT ( STDMETHODCALLTYPE *GetDirectoriesCount )( 
            ICatalog * This,
            /* [retval][out] */ LONG *directoriesCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetDirectoryName )( 
            ICatalog * This,
            /* [in] */ LONG index,
            /* [retval][out] */ BSTR *directoryName);
        
        HRESULT ( STDMETHODCALLTYPE *GetFile )( 
            ICatalog * This,
            /* [in] */ LONG index,
            /* [retval][out] */ IFSObject **file);
        
        HRESULT ( STDMETHODCALLTYPE *CreateFile )( 
            ICatalog * This,
            /* [in] */ BSTR name);
        
        HRESULT ( STDMETHODCALLTYPE *CreateDirectory )( 
            ICatalog * This,
            /* [in] */ BSTR name);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            ICatalog * This,
            /* [in] */ BSTR path);
        
        HRESULT ( STDMETHODCALLTYPE *GetFullPath )( 
            ICatalog * This,
            /* [retval][out] */ BSTR *path);
        
        END_INTERFACE
    } ICatalogVtbl;

    interface ICatalog
    {
        CONST_VTBL struct ICatalogVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICatalog_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICatalog_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICatalog_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICatalog_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICatalog_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICatalog_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICatalog_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ICatalog_ReloadFiles(This)	\
    ( (This)->lpVtbl -> ReloadFiles(This) ) 

#define ICatalog_GetFilesCount(This,filesCount)	\
    ( (This)->lpVtbl -> GetFilesCount(This,filesCount) ) 

#define ICatalog_GetFileName(This,index,fileName)	\
    ( (This)->lpVtbl -> GetFileName(This,index,fileName) ) 

#define ICatalog_GetFileSystemEntriesCount(This,entriesCount)	\
    ( (This)->lpVtbl -> GetFileSystemEntriesCount(This,entriesCount) ) 

#define ICatalog_GetFileSystemEntryName(This,index,entryName)	\
    ( (This)->lpVtbl -> GetFileSystemEntryName(This,index,entryName) ) 

#define ICatalog_GetDirectoriesCount(This,directoriesCount)	\
    ( (This)->lpVtbl -> GetDirectoriesCount(This,directoriesCount) ) 

#define ICatalog_GetDirectoryName(This,index,directoryName)	\
    ( (This)->lpVtbl -> GetDirectoryName(This,index,directoryName) ) 

#define ICatalog_GetFile(This,index,file)	\
    ( (This)->lpVtbl -> GetFile(This,index,file) ) 

#define ICatalog_CreateFile(This,name)	\
    ( (This)->lpVtbl -> CreateFile(This,name) ) 

#define ICatalog_CreateDirectory(This,name)	\
    ( (This)->lpVtbl -> CreateDirectory(This,name) ) 

#define ICatalog_Initialize(This,path)	\
    ( (This)->lpVtbl -> Initialize(This,path) ) 

#define ICatalog_GetFullPath(This,path)	\
    ( (This)->lpVtbl -> GetFullPath(This,path) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICatalog_INTERFACE_DEFINED__ */


#ifndef __IFileObject_INTERFACE_DEFINED__
#define __IFileObject_INTERFACE_DEFINED__

/* interface IFileObject */
/* [object][version][uuid] */ 


EXTERN_C const IID IID_IFileObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D3FFDFA7-D6D8-4FE5-A092-B4D0E475E726")
    IFileObject : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IFileObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFileObject * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFileObject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFileObject * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IFileObject * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IFileObject * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IFileObject * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IFileObject * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IFileObjectVtbl;

    interface IFileObject
    {
        CONST_VTBL struct IFileObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFileObject_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFileObject_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFileObject_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFileObject_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IFileObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IFileObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IFileObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFileObject_INTERFACE_DEFINED__ */


#ifndef __IFolderObject_INTERFACE_DEFINED__
#define __IFolderObject_INTERFACE_DEFINED__

/* interface IFolderObject */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IFolderObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4DC247C6-8261-48FC-9764-0949D9F6B493")
    IFolderObject : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IFolderObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFolderObject * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFolderObject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFolderObject * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IFolderObject * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IFolderObject * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IFolderObject * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IFolderObject * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IFolderObjectVtbl;

    interface IFolderObject
    {
        CONST_VTBL struct IFolderObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFolderObject_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFolderObject_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFolderObject_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFolderObject_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IFolderObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IFolderObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IFolderObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFolderObject_INTERFACE_DEFINED__ */



#ifndef __FileManagerServerLib_LIBRARY_DEFINED__
#define __FileManagerServerLib_LIBRARY_DEFINED__

/* library FileManagerServerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_FileManagerServerLib;

EXTERN_C const CLSID CLSID_FileObject;

#ifdef __cplusplus

class DECLSPEC_UUID("01018ECD-F895-4939-B909-AB2E117814F2")
FileObject;
#endif

EXTERN_C const CLSID CLSID_FolderObject;

#ifdef __cplusplus

class DECLSPEC_UUID("87F86C92-0F52-4468-BBD4-B6742F2AF96C")
FolderObject;
#endif
#endif /* __FileManagerServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


