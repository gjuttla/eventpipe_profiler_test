// Copyright (c) .NET Foundation and contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "CorProfiler.h"
#include "corhlpr.h"
#include "CComPtr.h"
#include "profiler_pal.h"
#include <string>
#include <assert.h>

using std::shared_ptr;
using std::vector;
using std::mutex;
using std::lock_guard;
using std::wstring;
using std::map;

CorProfiler::CorProfiler() :
    _refCount(0),
    _failures(),
    _pCorProfilerInfo()
{

}

CorProfiler::~CorProfiler()
{
    if (this->_pCorProfilerInfo != nullptr)
    {
        this->_pCorProfilerInfo->Release();
        this->_pCorProfilerInfo = nullptr;
    }
}

HRESULT STDMETHODCALLTYPE CorProfiler::Initialize(IUnknown *pICorProfilerInfoUnk)
{
    HRESULT hr = S_OK;
    if (FAILED(hr = pICorProfilerInfoUnk->QueryInterface(__uuidof(ICorProfilerInfo), (void **)&_pCorProfilerInfo)))
    {
        printf("FAIL: failed to QI for ICorProfilerInfo.\n");
        _failures++;
        return hr;
    }

    if (FAILED(hr = _pCorProfilerInfo->SetEventMask(COR_PRF_MONITOR_REMOTING)))
    {
        _failures++;
        printf("FAIL: ICorProfilerInfo::SetEventMask() failed hr=0x%x\n", hr);
        return hr;
    }

    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::Shutdown()
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::AppDomainCreationStarted(AppDomainID appDomainId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::AppDomainCreationFinished(AppDomainID appDomainId, HRESULT hrStatus)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::AppDomainShutdownStarted(AppDomainID appDomainId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::AppDomainShutdownFinished(AppDomainID appDomainId, HRESULT hrStatus)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::AssemblyLoadStarted(AssemblyID assemblyId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::AssemblyLoadFinished(AssemblyID assemblyId, HRESULT hrStatus)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::AssemblyUnloadStarted(AssemblyID assemblyId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::AssemblyUnloadFinished(AssemblyID assemblyId, HRESULT hrStatus)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ModuleLoadStarted(ModuleID moduleId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ModuleLoadFinished(ModuleID moduleId, HRESULT hrStatus)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ModuleUnloadStarted(ModuleID moduleId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ModuleUnloadFinished(ModuleID moduleId, HRESULT hrStatus)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ModuleAttachedToAssembly(ModuleID moduleId, AssemblyID AssemblyId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ClassLoadStarted(ClassID classId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ClassLoadFinished(ClassID classId, HRESULT hrStatus)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ClassUnloadStarted(ClassID classId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ClassUnloadFinished(ClassID classId, HRESULT hrStatus)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::FunctionUnloadStarted(FunctionID functionId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::JITCompilationStarted(FunctionID functionId, BOOL fIsSafeToBlock)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::JITCompilationFinished(FunctionID functionId, HRESULT hrStatus, BOOL fIsSafeToBlock)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::JITCachedFunctionSearchStarted(FunctionID functionId, BOOL *pbUseCachedFunction)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::JITCachedFunctionSearchFinished(FunctionID functionId, COR_PRF_JIT_CACHE result)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::JITFunctionPitched(FunctionID functionId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::JITInlining(FunctionID callerId, FunctionID calleeId, BOOL *pfShouldInline)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ThreadCreated(ThreadID threadId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ThreadDestroyed(ThreadID threadId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ThreadAssignedToOSThread(ThreadID managedThreadId, DWORD osThreadId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::RemotingClientInvocationStarted()
{
#ifdef PRINT_REMOTING_CALLBACKS
	printf("RemotingClientInvocationStarted\n");
#endif
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::RemotingClientSendingMessage(GUID *pCookie, BOOL fIsAsync)
{
#ifdef PRINT_REMOTING_CALLBACKS
	printf("RemotingClientSendingMessage\n");
#endif
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::RemotingClientReceivingReply(GUID *pCookie, BOOL fIsAsync)
{
#ifdef PRINT_REMOTING_CALLBACKS
	printf("RemotingClientReceivingReply\n");
#endif
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::RemotingClientInvocationFinished()
{
#ifdef PRINT_REMOTING_CALLBACKS
	printf("RemotingClientInvocationFinished\n");
#endif
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::RemotingServerReceivingMessage(GUID *pCookie, BOOL fIsAsync)
{
#ifdef PRINT_REMOTING_CALLBACKS
	printf("RemotingServerReceivingMessage\n");
#endif
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::RemotingServerInvocationStarted()
{
#ifdef PRINT_REMOTING_CALLBACKS
	printf("RemotingServerInvocationStarted\n");
#endif
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::RemotingServerInvocationReturned()
{
#ifdef PRINT_REMOTING_CALLBACKS
	printf("RemotingServerInvocationReturned\n");
#endif
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::RemotingServerSendingReply(GUID *pCookie, BOOL fIsAsync)
{
#ifdef PRINT_REMOTING_CALLBACKS
	printf("RemotingServerSendingReply\n");
#endif
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::UnmanagedToManagedTransition(FunctionID functionId, COR_PRF_TRANSITION_REASON reason)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ManagedToUnmanagedTransition(FunctionID functionId, COR_PRF_TRANSITION_REASON reason)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::RuntimeSuspendStarted(COR_PRF_SUSPEND_REASON suspendReason)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::RuntimeSuspendFinished()
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::RuntimeSuspendAborted()
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::RuntimeResumeStarted()
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::RuntimeResumeFinished()
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::RuntimeThreadSuspended(ThreadID threadId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::RuntimeThreadResumed(ThreadID threadId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::MovedReferences(ULONG cMovedObjectIDRanges, ObjectID oldObjectIDRangeStart[], ObjectID newObjectIDRangeStart[], ULONG cObjectIDRangeLength[])
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ObjectAllocated(ObjectID objectId, ClassID classId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ObjectsAllocatedByClass(ULONG cClassCount, ClassID classIds[], ULONG cObjects[])
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ObjectReferences(ObjectID objectId, ClassID classId, ULONG cObjectRefs, ObjectID objectRefIds[])
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::RootReferences(ULONG cRootRefs, ObjectID rootRefIds[])
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ExceptionThrown(ObjectID thrownObjectId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ExceptionSearchFunctionEnter(FunctionID functionId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ExceptionSearchFunctionLeave()
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ExceptionSearchFilterEnter(FunctionID functionId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ExceptionSearchFilterLeave()
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ExceptionSearchCatcherFound(FunctionID functionId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ExceptionOSHandlerEnter(UINT_PTR __unused)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ExceptionOSHandlerLeave(UINT_PTR __unused)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ExceptionUnwindFunctionEnter(FunctionID functionId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ExceptionUnwindFunctionLeave()
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ExceptionUnwindFinallyEnter(FunctionID functionId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ExceptionUnwindFinallyLeave()
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ExceptionCatcherEnter(FunctionID functionId, ObjectID objectId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ExceptionCatcherLeave()
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::COMClassicVTableCreated(ClassID wrappedClassId, REFGUID implementedIID, void *pVTable, ULONG cSlots)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::COMClassicVTableDestroyed(ClassID wrappedClassId, REFGUID implementedIID, void *pVTable)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ExceptionCLRCatcherFound()
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ExceptionCLRCatcherExecute()
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ThreadNameChanged(ThreadID threadId, ULONG cchName, WCHAR name[])
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::GarbageCollectionStarted(int cGenerations, BOOL generationCollected[], COR_PRF_GC_REASON reason)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::SurvivingReferences(ULONG cSurvivingObjectIDRanges, ObjectID objectIDRangeStart[], ULONG cObjectIDRangeLength[])
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::GarbageCollectionFinished()
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::FinalizeableObjectQueued(DWORD finalizerFlags, ObjectID objectID)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::RootReferences2(ULONG cRootRefs, ObjectID rootRefIds[], COR_PRF_GC_ROOT_KIND rootKinds[], COR_PRF_GC_ROOT_FLAGS rootFlags[], UINT_PTR rootIds[])
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::HandleCreated(GCHandleID handleId, ObjectID initialObjectId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::HandleDestroyed(GCHandleID handleId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::InitializeForAttach(IUnknown *_pCorProfilerInfoUnk, void *pvClientData, UINT cbClientData)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ProfilerAttachComplete()
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ProfilerDetachSucceeded()
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ReJITCompilationStarted(FunctionID functionId, ReJITID rejitId, BOOL fIsSafeToBlock)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::GetReJITParameters(ModuleID moduleId, mdMethodDef methodId, ICorProfilerFunctionControl *pFunctionControl)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ReJITCompilationFinished(FunctionID functionId, ReJITID rejitId, HRESULT hrStatus, BOOL fIsSafeToBlock)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ReJITError(ModuleID moduleId, mdMethodDef methodId, FunctionID functionId, HRESULT hrStatus)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::MovedReferences2(ULONG cMovedObjectIDRanges, ObjectID oldObjectIDRangeStart[], ObjectID newObjectIDRangeStart[], SIZE_T cObjectIDRangeLength[])
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::SurvivingReferences2(ULONG cSurvivingObjectIDRanges, ObjectID objectIDRangeStart[], SIZE_T cObjectIDRangeLength[])
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ConditionalWeakTableElementReferences(ULONG cRootRefs, ObjectID keyRefIds[], ObjectID valueRefIds[], GCHandleID rootIds[])
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::GetAssemblyReferences(const WCHAR *wszAssemblyPath, ICorProfilerAssemblyReferenceProvider *pAsmRefProvider)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ModuleInMemorySymbolsUpdated(ModuleID moduleId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::DynamicMethodJITCompilationStarted(FunctionID functionId, BOOL fIsSafeToBlock, LPCBYTE ilHeader, ULONG cbILHeader)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::DynamicMethodJITCompilationFinished(FunctionID functionId, HRESULT hrStatus, BOOL fIsSafeToBlock)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::DynamicMethodUnloaded(FunctionID functionId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::EventPipeEventDelivered(
    EVENTPIPE_PROVIDER provider,
    DWORD eventId,
    DWORD eventVersion,
    ULONG cbMetadataBlob,
    LPCBYTE metadataBlob,
    ULONG cbEventData,
    LPCBYTE eventData,
    LPCGUID pActivityId,
    LPCGUID pRelatedActivityId,
    ThreadID eventThread,
    ULONG numStackFrames,
    UINT_PTR stackFrames[])
{
    return S_OK;
}

HRESULT CorProfiler::EventPipeProviderCreated(EVENTPIPE_PROVIDER provider)
{
    return S_OK;
}
