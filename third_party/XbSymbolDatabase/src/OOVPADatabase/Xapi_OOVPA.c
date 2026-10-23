// SPDX-License-Identifier: ODbL-1.0

// Titles which did compiled with full library
//   [LibV] Title Name                       |  Verify   |  Comments
//-------------------------------------------------------------------
// * [3911] Cel Damage                       |   100%    | have 38/45 library.
// * [3950] Shikigami no Shiro               |   100%    | have 35/45 library.
// * [4034] Dark Summit                      |   100%    | have 21/45 library.
// * [4039] New Legends                      |   100%    | have 30/45 library.
// * [4134] Double-S.T.E.A.L                 |   100%    | have 39/47 library.
// * [4242] NFL Blitz 2002                   |   100%    | have 46/48 library.
// * [4361] ESPN NBA 2Night 2002             |   100%    | have 33/48 library.
// * [4432] RedCard 2003                     |   100%    | have 46/48 library.
// * [4531] NHL HITZ 2003                    |   100%    | have 41/48 library.
// * [4627] MLB SlugFest 2003                |   100%    | have 46/48 library.
// * [4721] Terminator - Dawn of Fate        |   100%    | have 41/48 library.
// * [4831] Whacked                          |   100%    | have 42/50 library.
// * [4928] Drihoo                           |   100%    | have 42/50 library.
// * [5028] Shikigami no Shiro Evolution     |   100%    | have 39/50 library.
// * [5120] N.U.D.E.@                        |   100%    | have 40/50 library.
// * [5233] Evil Dead                        |   100%    | have 39/50 library.
// * [5344] Starsky & Hutch                  |   100%    | have 43/50 library.
// * [5455] NCAA Football 2004               |   100%    | have 44/50 library.
// * [5558] XIII                             |   100%    | have 42/50 library.
// * [5659] LMA Manager 2004                 |   100%    | have 42/50 library.
// * [5788] All-Star Baseball 2005           |   100%    | have 42/50 library.
// * [5849] Nickelodeon Tak 2                |   100%    | have 40/50 library.

// TODO: Known Xapi OOVPA issue list
// * Verification needed: Function Name ( Revision )
//   * ConvertThreadToFiber (3950, 4034, 4039, 4134, 4531, 4721, 5028, 5455)
//   * CreateFiber (3950, 4034, 4039, 4134, 4531, 4721, 5028, 5455)
//   * DeleteFiber (3950, 4034, 4039, 4134, 4531, 4721, 5028, 5455)
//   * ExitThread (4034)
//   * GetExitCodeThread (4034)
//   * GetOverlappedResult (4034)
//   * GetThreadPriority (4034)
//   * GetTimeZoneInformation (4034)
//   * MoveFileA (4034)
//   * QueueUserAPC (4034)
//   * SetThreadPriority (4034)
//   * SetThreadPriorityBoost (4034)
//   * SignalObjectAndWait (4034)
//   * SwitchToFiber (3950, 4034, 4039, 4134, 4531, 4721, 5028, 5455)
//   * SwitchToThread (4034)
//   * XCalculateSignatureBegin (4034)
//   * XGetDeviceChanges (4034)
//   * XInputGetCapabilities (4034)
//   * XInputGetDeviceDescription (4928, 5028, 5120, 5233, 5455)
//   * XInputPoll (4034)
//   * XMountAlternateTitleA (4034)
//   * XMountMURootA (3950, 4034, 4039, 4134, 5028, 5120, 5233)
//   * XapiFiberStartup (3950, 4034, 4039, 4134, 4531, 4721, 5028, 5455)
//   * timeKillEvent (3950, 4034, 5028, 5233)
//   * timeSetEvent (4034, 5233)
//   * XReadMUMetaData (3911, 3950, 4034, 4039, 4134)
// * Following OOVPA are invalid
//   * CloseHandle (3911) // Has exact asm codes _ResetEvent@4
//   * ReadFileEx (3911) // Has exact asm codes _WriteFileEx@20
//   * WriteFileEx (3911) // Has exact asm codes _ReadFileEx@20
//   * lstrcmpiW (3911) // Necessary XREF _xCompareStringW@20
// * Following OOVPA are missing (Obsolete?)
//   * GetThreadPriorityBoost
//   * RtlAllocateHeap
//   * RtlCreateHeap
//   * RtlDestroyHeap
//   * RtlFreeHeap
//   * RtlReAllocateHeap
//   * RtlSizeHeap
//   * XCalculateSignatureBeginEx
//   * XCalculateSignatureEnd
//   * XCalculateSignatureUpdate
// NOTE: Known Xapi OOVPA not included in initial revision.
//   * XFormatUtilityDrive (4242)
//   * XSetProcessQuantumLength (4134)
//   * XInputGetDeviceDescription (4831)
//   * XGetDeviceEnumerationStatus (4831)
// List of known Symbols may can be add to database (3911)
//   * CancelWaitableTimer
//   * CharLowerA
//   * CharLowerW
//   * CharUpperA
//   * CharUpperW
//   * CloseHandle
//   * CompareFileTime
//   * CopyFileA
//   * CopyFileExA
//   * CopyRect
//   * CreateDirectoryA
//   * CreateFileA
//   * CreateIoCompletionPort
//   * CreateSemaphoreA
//   * CreateWaitableTimerA
//   * DebugBreak
//   * DebugPrint
//   * DeleteFileA
//   * DeviceIoControl
//   * DmGetCurrentValue
//   * DmTell
//   * DuplicateHandle
//   * EqualRect
//   * FileTimeToLocalFileTime
//   * FileTimeToSystemTime
//   * FindFirstFileA
//   * FindNextFileA
//   * FlushFileBuffers
//   * GetCurrentThreadId
//   * GetDiskFreeSpaceExA
//   * GetFileAttributesA
//   * GetFileAttributesExA
//   * GetFileInformationByHandle
//   * GetFileSize
//   * GetFileSizeEx
//   * GetFileTime
//   * GetLocalTime
//   * GetNextNickname
//   * GetProcessHeap
//   * GetQueuedCompletionStatus
//   * GetSystemTime
//   * GetSystemTimeAsFileTime
//   * GetThreadPriorityBoost
//   * GetThreadTimes
//   * GetTickCount
//   * GetVolumeInformationA
//   * GlobalAlloc
//   * GlobalMemoryStatus
//   * GlobalReAlloc
//   * HCD_CancelRequest
//   * HCD_DisableRootHubPort
//   * HCD_DriverEntry
//   * HCD_EnumHardware
//   * HCD_NewHostController
//   * HCD_ResetRootHubPort
//   * HCD_SubmitRequest
//   * HeapCreate
//   * HeapDestroy
//   * HeapFree
//   * HexDigitToChar
//   * InflateRect
//   * IntersectRect
//   * IsBadCodePtr
//   * IsBadReadPtr
//   * IsBadStringPtrA
//   * IsBadStringPtrW
//   * IsBadWritePtr
//   * IsRectEmpty
//   * KeGetCurrentIrql
//   * KeGetCurrentIrql
//   * KeGetCurrentPrcb
//   * KeGetCurrentPrcb
//   * KeGetCurrentThread
//   * KeGetCurrentThread
//   * KeGetCurrentThread
//   * KeGetCurrentThread
//   * KeGetCurrentThread
//   * LocalAlloc
//   * LocalFileTimeToFileTime
//   * LocalFree
//   * LocalHandle
//   * LocalLock
//   * LocalReAlloc
//   * LocalSize
//   * LocalUnlock
//   * lstrcatA
//   * lstrcatW
//   * lstrcmpA
//   * lstrcmpiA
//   * lstrcmpiW
//   * lstrcmpW
//   * lstrcpyA
//   * lstrcpynA
//   * lstrcpynW
//   * lstrcpyW
//   * lstrlenA
//   * lstrlenW
//   * MoveFileExA
//   * MoveFileWithProgressA
//   * MulDiv
//   * MultiByteToWideChar
//   * MU_AddDevice
//   * MU_CloseDeviceObject
//   * MU_CreateDeviceObject
//   * MU_RemoveDevice
//   * OffsetRect
//   * OpenMutexA
//   * OpenSemaphoreA
//   * OpenWaitableTimerA
//   * PortNumberToRootHubPort
//   * PostQueuedCompletionStatus
//   * PtInRect
//   * QueryPerformanceFrequency
//   * ReadFile
//   * ReadFileEx
//   * ReadFileScatter
//   * ReleaseMutex
//   * ReleaseSemaphore
//   * RemoveDirectoryA
//   * ResumeThread
//   * RootHubPortToPortNumber
//   * RtlAllocateHeap
//   * RtlAllocateHeapSlowly
//   * RtlCreateHeap
//   * RtlDestroyHeap
//   * RtlFreeHeap
//   * RtlFreeHeapSlowly
//   * RtlpCheckBusyBlockTail
//   * RtlpCoalesceFreeBlocks
//   * RtlpCreateUnCommittedRange
//   * RtlpCutoverTimeToSystemTime
//   * RtlpDeCommitFreeBlock
//   * RtlpDestroyHeapSegment
//   * RtlpDestroyUnCommittedRange
//   * RtlpExtendHeap
//   * RtlpFindAndCommitPages
//   * RtlpGetExtraStuffPointer
//   * RtlpGetSizeOfBigBlock
//   * RtlpGrowBlockInPlace
//   * RtlpInitializeHeapSegment
//   * RtlpInsertFreeBlock
//   * RtlpInsertUnCommittedPages
//   * RtlRandom
//   * RtlReAllocateHeap
//   * RtlSizeHeap
//   * RtlZeroHeap
//   * SetEndOfFile
//   * SetFileAttributesA
//   * SetFilePointer
//   * SetFilePointerEx
//   * SetFileTime
//   * SetRect
//   * SetRectEmpty
//   * SetUnhandledExceptionFilter
//   * SetWaitableTimer
//   * Sleep
//   * SleepEx
//   * SubtractRect
//   * SuspendThread
//   * SystemTimeToFileTime
//   * timeGetSystemTime
//   * TlsAlloc
//   * TlsFree
//   * TlsGetValue
//   * TlsSetValue
//   * UnionRect
//   * USBD_CalculateUsbBandwidth
//   * USBD_CompleteRequest
//   * USBD_DeviceConnected
//   * USBD_DeviceDisconnected
//   * USBD_Init
//   * USBD_NewHostController
//   * USBHUB_AddDevice
//   * USBHUB_Init
//   * USBHUB_RemoveDevice
//   * VirtualAlloc
//   * VirtualAllocEx
//   * VirtualFree
//   * VirtualFreeEx
//   * VirtualProtect
//   * VirtualProtectEx
//   * VirtualQuery
//   * VirtualQueryEx
//   * WaitForMultipleObjects
//   * WaitForMultipleObjectsEx
//   * WaitForSingleObject
//   * WaitForSingleObjectEx
//   * WideCharToMultiByte
//   * WriteFile
//   * WriteFileEx
//   * WriteFileGather
//   * wsprintfA
//   * wsprintfW
//   * wvsprintfA
//   * wvsprintfW
//   * XapiAutoPowerDownTimeout
//   * XapiConvertSignatureToNonRoamable
//   * XapiCopySectionToFile
//   * XapiDirectoryInformationToFindData
//   * XapiDispatchAPC
//   * XapiFillInSaveGameData
//   * XapiFindValueInMetaFile
//   * XapiFormatFATVolume
//   * XapiFormatTimeOut
//   * XapiGetDirectoryDisplayBlocks
//   * XapiGetNextSoundtrack
//   * XapiInitAutoPowerDown
//   * XapiIsXapiThread
//   * XapiMmTimerThread
//   * XapiNukeDirectory
//   * XapiNukeDirectoryFromHandle
//   * XapiOpenStDbAndReadHeader
//   * XapipGetTimeZoneBias
//   * XapipQueryTimeZoneInformation
//   * XapipUseDaylightSavingTime
//   * XapiReadFromStDb
//   * XapiSaveGameHashEncode
//   * XapiSetupPerTitleDriveLetters
//   * XapiTouchDirectoryTimestamp
//   * XapiValidateAndSkipUnicodeSignature
//   * XapiValidateDiskPartition
//   * XapiVerifyGameName
//   * XboxTimeZoneDateToSystemTime
//   * XboxTimeZoneNameToWstr
//   * XCalculateSignatureBeginEx
//     * XapipCalculateContentSignatureBegin,
//     * XapipCalculateSaveGameSignatureBegin,
//   * XCalculateSignatureEnd
//   * XCalculateSignatureUpdate
//   * xCompareStringA
//   * xCompareStringW
//   * XCreateSaveGame
//   * XDeleteSaveGame
//   * XdReportDeviceInsertionRemoval
//   * XFindClose
//   * XFindFirstNicknameW
//   * XFindFirstSaveGame
//   * XFindFirstSoundtrack
//   * XFindNextNicknameW
//   * XFindNextSaveGame
//   * XFindNextSoundtrack
//   * XFreeSectionA
//   * XFreeSectionByHandle
//   * XGetAudioFlags
//   * XGetAVPack
//   * XGetDiskClusterSizeA
//   * XGetDiskSectorSizeA
//   * XGetDisplayBlocks
//   * XGetFileCacheSize
//   * XGetGameRegion
//   * XGetLanguage
//   * XGetParentalControlSetting
//   * XGetSectionHandleA
//   * XGetSoundtrackSongInfo
//   * XGetVideoFlags
//   * XGetVideoStandard
//   * XID_AddDevice
//   * XID_Init
//   * XID_RemoveDevice
//   * XLoadSectionA
//   * XLoadSectionByHandle
//   * XOpenSoundtrackSong
//   * XPhysicalAlloc
//   * XPhysicalFree
//   * XPhysicalProtect
//   * XPhysicalSize
//   * XQueryMemoryProtect
//   * XQueryValue
//   * XSetFileCacheSize
//   * XSetNicknameW
//   * XShaHmacComputeFinal
//   * XShaHmacInitialize
//   * XShaHmacUpdate
//   * XWriteTitleInfoAndRebootA
//   * XWriteTitleInfoNoReboot
//   * initterm
//   * initterm_e
//   * InterlockedCompareExchange
//   * InterlockedDecrement
//   * InterlockedExchange
//   * InterlockedExchangeAdd
//   * InterlockedIncrement

#include "OOVPA_databases.h"

#include "Xapi/3911.inl"
#include "Xapi/3950.inl"
#include "Xapi/4039.inl"
#include "Xapi/4134.inl"
#include "Xapi/4242.inl"
#include "Xapi/4361.inl"
#include "Xapi/4721.inl"
#include "Xapi/4831.inl"
#include "Xapi/5028.inl"
#include "Xapi/5120.inl"
#include "Xapi/5344.inl"
#include "Xapi/5455.inl"

// ******************************************************************
// * XAPILIB_OOVPA_Table
// ******************************************************************
static OOVPATable XAPILIB_OOVPA_Table[] = {

    // Variables
    REGISTER_OOVPAS_M(SYM_VAR(_tls_array),
                      SYM_SIG(0)),
    REGISTER_OOVPAS_M(SYM_VAR(_tls_index),
                      SYM_SIG(0)),
    REGISTER_OOVPAS_M(SYM_VAR(g_DeviceType_Gamepad),
                      SYM_SIG(0)),
    REGISTER_OOVPAS_M(SYM_VAR(g_DeviceType_IRDongle),
                      SYM_SIG(0)),
    REGISTER_OOVPAS_M(SYM_VAR(g_DeviceType_Keyboard),
                      SYM_SIG(0)),
    REGISTER_OOVPAS_M(SYM_VAR(g_DeviceType_Mouse),
                      SYM_SIG(0)),
    REGISTER_OOVPAS_M(SYM_VAR(g_DeviceType_MU),
                      SYM_SIG(3911)),
    REGISTER_OOVPAS_M(SYM_VAR(g_DeviceType_SBC),
                      SYM_SIG(4242)),
    REGISTER_OOVPAS_M(SYM_VAR(g_DeviceTypeInfoTableBegin),
                      SYM_SIG(4242)),
    REGISTER_OOVPAS_M(SYM_VAR(g_DeviceTypeInfoTableEnd),
                      SYM_SIG(4242)),
    REGISTER_OOVPAS_M(SYM_VAR(g_XapiAltLett_MU),
                      SYM_SIG(0)),
    REGISTER_OOVPAS_M(SYM_VAR(g_XapiCurrentTopLevelFilter),
                      SYM_SIG(0)),
    REGISTER_OOVPAS_M(SYM_VAR(g_XapiMountedMUs),
                      SYM_SIG(0)),
    REGISTER_OOVPAS_M(SYM_VAR(XapiCurrentFiber_OFFSET),
                      SYM_SIG(0)),
    REGISTER_OOVPAS_M(SYM_VAR(XapiLastErrorCode_OFFSET),
                      SYM_SIG(0)),
    REGISTER_OOVPAS_M(SYM_VAR(XapiThreadFiberData_OFFSET),
                      SYM_SIG(0)),
    REGISTER_OOVPAS_M(SYM_VAR(XapiThreadNotifyRoutineList),
                      SYM_SIG(0)),

    // Without xrefs dependency
    REGISTER_OOVPAS(SYM_FUN(_cinit, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(_rtinit, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS_C(SYM_FUN(IUsbInit_GetMaxDeviceTypeCount, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(psh, DeviceType))),
                      SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(XapiFormatObjectAttributes, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pObjectAttributes), PARAM(psh, pObjectName), PARAM(psh, pName))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(XapiCallThreadNotifyRoutines, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Create))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS_M(SYM_FUN(XapiMapLetterToDirectory, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pDriveString), PARAM(psh, pDeviceString), PARAM(psh, pszTitleId), PARAM(psh, bCreateDirectory), PARAM(psh, pwszTitleName), PARAM(psh, bUpdateTimestamp))),
                      SYM_SIG(3911)),
    REGISTER_OOVPAS_M(SYM_FUN(XGetSectionSize, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, hSection))),
                      SYM_SIG(0)),
    REGISTER_OOVPAS(SYM_FUN(XLaunchNewImageA, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, lpTitlePath), PARAM(psh, pLaunchData))),
                    SYM_SIG(3911, 4721, 5344)),
    REGISTER_OOVPAS(SYM_FUN(XUnmountAlternateTitleA, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, chDrive))),
                    SYM_SIG(3911)),

    // With xrefs dependency (unorder, need to scan next before order list)
    REGISTER_OOVPAS(SYM_FUN(mainXapiStartup, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, lpParameter))),
                    SYM_SIG(3911, 4831)), // Final generic OOVPA: 4831; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(GetLastError, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(SetLastError, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, ErrorCode))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(UnhandledExceptionFilter, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, ExceptionPointers))),
                    SYM_SIG(3911, 4831)), // Final generic OOVPA: 4831 Removed: 0
    REGISTER_OOVPAS(SYM_FUN(XapiBootToDash, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, dwReason), PARAM(psh, dwParameter1), PARAM(psh, dwParameter2))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(XapiSelectCachePartition, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, bAlwaysFormat), PARAM(psh, pnCachePartition), PARAM(psh, pbForceFormat))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(XapiSetLastNTError, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, Status))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(XapiThreadStartup, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, StartRoutine), PARAM(psh, StartContext))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0

    // With xrefs dependency (order)
    REGISTER_OOVPAS(SYM_FUN(CreateEventA, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, lpEventAttributes), PARAM(psh, bManualReset), PARAM(psh, bInitialState), PARAM(psh, lpName))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CreateMutexA, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, lpMutexAttributes), PARAM(psh, bInitialOwner), PARAM(psh, lpName))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CreateThread, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, lpThreadAttributes), PARAM(psh, dwStackSize), PARAM(psh, lpStartAddress), PARAM(psh, lpParameter), PARAM(psh, dwCreationFlags), PARAM(psh, lpThreadId))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(ExitThread, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, dwExitCode))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(MoveFileA, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, lpExistingFileName), PARAM(psh, lpNewFileName))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(SwitchToThread, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(XapiInitProcess, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 3950, 4242, 4831, 5028)), // obsolete, Too High Level (from 4721's comment)
    REGISTER_OOVPAS(SYM_FUN(ConvertThreadToFiber, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, lpParameter))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(XCalculateSignatureBegin, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, dwFlags), PARAM(psh, dwAltTitleId))),
                    SYM_SIG(3911, 4034)), // Final generic OOVPA: ????; Removed: 0 // TODO: need verification for 4034 against 3950 and lower.
    REGISTER_OOVPAS(SYM_FUN(CreateFiber, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, dwStackSize), PARAM(psh, lpStartAddress), PARAM(psh, lpParameter))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(DeleteFiber, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, lpFiber))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(GetExitCodeThread, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, hThread), PARAM(psh, lpExitCode))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(GetOverlappedResult, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, hFile), PARAM(psh, lpOverlapped), PARAM(psh, lpNumberOfBytesTransferred), PARAM(psh, bWait))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(GetThreadPriority, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, hThread))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(GetTimeZoneInformation, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, lpTimeZoneInformation))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS_M(SYM_FUN(GetTypeInformation, CALL(fas), STACK(/*default*/), PARAMS(PARAM(ecx, XppType))),
                      SYM_SIG(4242)), // Final generic OOVPA: 4242; Removed: 0
    REGISTER_OOVPAS_C(SYM_FUN(GetTypeInformation2, CALL(fas), STACK(/*default*/), PARAMS(PARAM(_cl, XidType), PARAM(edx, pTypeIndex))),
                      SYM_SIG(4242, 5455)), // Final generic OOVPA: 5455; Removed: 0
    REGISTER_OOVPAS_M(SYM_FUN(MU_Init, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThis))),
                      SYM_SIG(3911, 4242, 5120)),
    REGISTER_OOVPAS(SYM_FUN(OpenEventA, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, dwDesiredAccess), PARAM(psh, bInheritHandle), PARAM(psh, lpName))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(OutputDebugStringA, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, lpOutputString))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(OutputDebugStringW, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, lpOutputString))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(mainCRTStartup, CALL(cde), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 4361)), // Final generic OOVPA: 4361; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(PulseEvent, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, hEvent))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(QueueUserAPC, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pfnAPC), PARAM(psh, hThread), PARAM(psh, dwData))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(QueryPerformanceCounter, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, lpPerformanceCount))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(RaiseException, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, dwExceptionCode), PARAM(psh, dwExceptionFlags), PARAM(psh, nNumberOfArguments), PARAM(psh, lpArguments))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(ResetEvent, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, hEvent))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(SetEvent, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, hEvent))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(SetThreadPriority, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, hThread), PARAM(psh, nPriority))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(SetThreadPriorityBoost, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, hThread), PARAM(psh, DisablePriorityBoost))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(SignalObjectAndWait, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, hObjectToSignal), PARAM(psh, hObjectToWaitOn), PARAM(psh, dwMilliseconds), PARAM(psh, bAlertable))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(SwitchToFiber, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, lpFiber))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(XAutoPowerDownResetTimer, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911)), // Just calls KeSetTimer (from 3911's comment)
    REGISTER_OOVPAS(SYM_FUN(XFormatUtilityDrive, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(4242)),
    REGISTER_OOVPAS(SYM_FUN(XGetDeviceChanges, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, DeviceType), PARAM(psh, pdwInsertions), PARAM(psh, pdwRemovals))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(XGetDeviceEnumerationStatus, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(XGetDevices, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, DeviceType))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(XGetLaunchInfo, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pdwLaunchDataType), PARAM(psh, pLaunchData))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(XID_fCloseDevice, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(3911, 4831)),
    REGISTER_OOVPAS(SYM_FUN(XInitDevices, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, dwPreallocTypeCount), PARAM(psh, PreallocTypes))),
                    SYM_SIG(3911, 5120)),
    REGISTER_OOVPAS(SYM_FUN(XInputClose, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, hDevice))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(XInputGetCapabilities, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, hDevice), PARAM(psh, pCapabilities))),
                    SYM_SIG(3911, 4831)), // Final generic OOVPA: 4831; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(XInputGetDeviceDescription, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, hDevice), PARAM(psh, pDescription))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(XInputGetState, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, hDevice), PARAM(psh, pState))),
                    SYM_SIG(3911, 4242, 5455)),
    REGISTER_OOVPAS_C(SYM_FUN(XInputOpen, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, DeviceType), PARAM(psh, dwPort), PARAM(psh, dwSlot), PARAM(psh, pPollingParameters))),
                      SYM_SIG(3911, 4242)), // Final generic OOVPA: 4242; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(XInputPoll, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, hDevice))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(XInputSetLightgunCalibration, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, hDevice), PARAM(psh, pCalibrationOffsets))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(XInputSetState, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, hDevice), PARAM(psh, pFeedback))),
                    SYM_SIG(3911, 4242, 4831)),
    REGISTER_OOVPAS(SYM_FUN(XMountAlternateTitleA, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, lpRootPath), PARAM(psh, dwAltTitleId), PARAM(psh, pchDrive))),
                    SYM_SIG(3911, 5028, 5455)),
    REGISTER_OOVPAS(SYM_FUN(XMountMUA, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, dwPort), PARAM(psh, dwSlot), PARAM(psh, pchDrive))),
                    SYM_SIG(3911, 4242)),
    REGISTER_OOVPAS(SYM_FUN(XMountMURootA, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, dwPort), PARAM(psh, dwSlot), PARAM(psh, pchDrive))),
                    SYM_SIG(3911, 4242)),
    REGISTER_OOVPAS(SYM_FUN(XMountUtilityDrive, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, bFormatClean))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(XMUNameFromDriveLetter, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, chDrive), PARAM(psh, pwszName), PARAM(psh, chName))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(XMUPortFromDriveLetterA, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, chDrive))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(XMUSlotFromDriveLetterA, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, chDrive))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(XMUWriteNameToDriveLetter, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, chDrive), PARAM(psh, pwszName))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(XReadMUMetaData, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, dwPort), PARAM(psh, dwSlot), PARAM(psh, lpBuffer), PARAM(psh, dwByteOffset), PARAM(psh, dwNumberOfBytesToRead))),
                    SYM_SIG(4242)),
    REGISTER_OOVPAS(SYM_FUN(XRegisterThreadNotifyRoutine, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, pThreadNotification), PARAM(psh, bRegister))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(XSetProcessQuantumLength, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, dwMilliseconds))),
                    SYM_SIG(4134)),
    REGISTER_OOVPAS(SYM_FUN(XUnmountMU, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, dwPort), PARAM(psh, dwSlot))),
                    SYM_SIG(3911, 4242)),
    REGISTER_OOVPAS(SYM_FUN(XapiFiberStartup, CALL(cde), STACK(/*default*/), PARAMS(PARAM(psh, lpStartAddress))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(timeKillEvent, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, uTimerID))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(timeSetEvent, CALL(std), STACK(/*default*/), PARAMS(PARAM(psh, uDelay), PARAM(psh, uResolution), PARAM(psh, lpTimeProc), PARAM(psh, dwUser), PARAM(psh, uEvent))),
                    SYM_SIG(3911)),
};

// ******************************************************************
// * XAPILIB_OOVPA
// ******************************************************************
OOVPATableList XAPILIB_OOVPA = { XBSDB_ARRAY_SIZE(XAPILIB_OOVPA_Table), XAPILIB_OOVPA_Table };
