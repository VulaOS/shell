#ifndef VLALIB_H_INCLUDED
#define VLALIB_H_INCLUDED


#define _AMD64_
#include <minwindef.h>
#include <winternl.h>


typedef enum _EVENT_TYPE
{
    NotificationEvent,
    SynchronizationEvent
} EVENT_TYPE;


typedef struct _KEYBOARD_INPUT_DATA {
    USHORT UnitId;
    USHORT MakeCode;
    USHORT Flags;
    USHORT Reserved;
    ULONG  ExtraInformation;
} KEYBOARD_INPUT_DATA, *PKEYBOARD_INPUT_DATA;

typedef struct _SECTION_IMAGE_INFORMATION
{
    PVOID TransferAddress;
    ULONG ZeroBits;
    SIZE_T MaximumStackSize;
    SIZE_T CommittedStackSize;
    ULONG SubSystemType;
    union
    {
        struct
        {
            USHORT SubSystemMinorVersion;
            USHORT SubSystemMajorVersion;
        };
        ULONG SubSystemVersion;
    };
    union
    {
        struct
        {
            USHORT MajorOperatingSystemVersion;
            USHORT MinorOperatingSystemVersion;
        };
        ULONG OperatingSystemVersion;
    };
    USHORT ImageCharacteristics;
    USHORT DllCharacteristics;
    USHORT Machine;
    BOOLEAN ImageContainsCode;
    union
    {
        UCHAR ImageFlags;
        struct
        {
            UCHAR ComPlusNativeReady : 1;
            UCHAR ComPlusILOnly : 1;
            UCHAR ImageDynamicallyRelocated : 1;
            UCHAR ImageMappedFlat : 1;
            UCHAR BaseBelow4gb : 1;
            UCHAR ComPlusPrefer32bit : 1;
            UCHAR Reserved : 2;
        };
    };
    ULONG LoaderFlags;
    ULONG ImageFileSize;
    ULONG CheckSum;
} SECTION_IMAGE_INFORMATION, *PSECTION_IMAGE_INFORMATION;

typedef struct _RTL_USER_PROCESS_INFORMATION
{
    ULONG Length;
    HANDLE ProcessHandle;
    HANDLE ThreadHandle;
    CLIENT_ID ClientId;
    SECTION_IMAGE_INFORMATION ImageInformation;
} RTL_USER_PROCESS_INFORMATION, *PRTL_USER_PROCESS_INFORMATION;

typedef NTSTATUS (NTAPI *PUSER_THREAD_START_ROUTINE)(
    _In_ PVOID ThreadParameter
    );

typedef struct _RTLP_CURDIR_REF
{
    LONG ReferenceCount;
    HANDLE DirectoryHandle;
} RTLP_CURDIR_REF, *PRTLP_CURDIR_REF;

typedef struct _RTL_RELATIVE_NAME_U
{
    UNICODE_STRING RelativeName;
    HANDLE ContainingDirectory;
    PRTLP_CURDIR_REF CurDirRef;
} RTL_RELATIVE_NAME_U, *PRTL_RELATIVE_NAME_U;

typedef struct _KSYSTEM_TIME
{
    ULONG LowPart;
    LONG High1Time;
    LONG High2Time;
} KSYSTEM_TIME, *PKSYSTEM_TIME;

typedef enum _NT_PRODUCT_TYPE
{
    NtProductWinNt = 1,
    NtProductLanManNt,
    NtProductServer
} NT_PRODUCT_TYPE, *PNT_PRODUCT_TYPE;

#define PROCESSOR_FEATURE_MAX 64

typedef enum _ALTERNATIVE_ARCHITECTURE_TYPE
{
    StandardDesign,
    NEC98x86,
    EndAlternatives
} ALTERNATIVE_ARCHITECTURE_TYPE;

typedef struct _KUSER_SHARED_DATA
{
    //
    // Current low 32-bit of tick count and tick count multiplier.
    //
    // N.B. The tick count is updated each time the clock ticks.
    //

    ULONG TickCountLowDeprecated;
    ULONG TickCountMultiplier;

    //
    // Current 64-bit interrupt time in 100ns units.
    //

    volatile KSYSTEM_TIME InterruptTime;

    //
    // Current 64-bit system time in 100ns units.
    //

    volatile KSYSTEM_TIME SystemTime;

    //
    // Current 64-bit time zone bias.
    //

    volatile KSYSTEM_TIME TimeZoneBias;

    //
    // Support image magic number range for the host system.
    //
    // N.B. This is an inclusive range.
    //

    USHORT ImageNumberLow;
    USHORT ImageNumberHigh;

    //
    // Copy of system root in unicode.
    //
    // N.B. This field must be accessed via the RtlGetNtSystemRoot API for
    //      an accurate result.
    //

    WCHAR NtSystemRoot[260];

    //
    // Maximum stack trace depth if tracing enabled.
    //

    ULONG MaxStackTraceDepth;

    //
    // Crypto exponent value.
    //

    ULONG CryptoExponent;

    //
    // Time zone ID.
    //

    ULONG TimeZoneId;

    ULONG LargePageMinimum;

    //
    // This value controls the AIT Sampling rate.
    //

    ULONG AitSamplingValue;

    //
    // This value controls switchback processing.
    //

    ULONG AppCompatFlag;

    //
    // Current Kernel Root RNG state seed version
    //

    ULONGLONG RNGSeedVersion;

    //
    // This value controls assertion failure handling.
    //

    ULONG GlobalValidationRunlevel;

    volatile LONG TimeZoneBiasStamp;

    //
    // The shared collective build number undecorated with C or F.
    // GetVersionEx hides the real number
    //

    ULONG NtBuildNumber;

    //
    // Product type.
    //
    // N.B. This field must be accessed via the RtlGetNtProductType API for
    //      an accurate result.
    //

    NT_PRODUCT_TYPE NtProductType;
    BOOLEAN ProductTypeIsValid;
    BOOLEAN Reserved0[1];
    USHORT NativeProcessorArchitecture;

    //
    // The NT Version.
    //
    // N. B. Note that each process sees a version from its PEB, but if the
    //       process is running with an altered view of the system version,
    //       the following two fields are used to correctly identify the
    //       version
    //

    ULONG NtMajorVersion;
    ULONG NtMinorVersion;

    //
    // Processor features.
    //

    BOOLEAN ProcessorFeatures[PROCESSOR_FEATURE_MAX];

    //
    // Reserved fields - do not use.
    //

    ULONG Reserved1;
    ULONG Reserved3;

    //
    // Time slippage while in debugger.
    //

    volatile ULONG TimeSlip;

    //
    // Alternative system architecture, e.g., NEC PC98xx on x86.
    //

    ALTERNATIVE_ARCHITECTURE_TYPE AlternativeArchitecture;

    //
    // Boot sequence, incremented for each boot attempt by the OS loader.
    //

    ULONG BootId;

    //
    // If the system is an evaluation unit, the following field contains the
    // date and time that the evaluation unit expires. A value of 0 indicates
    // that there is no expiration. A non-zero value is the UTC absolute time
    // that the system expires.
    //

    LARGE_INTEGER SystemExpirationDate;

    //
    // Suite support.
    //
    // N.B. This field must be accessed via the RtlGetSuiteMask API for
    //      an accurate result.
    //

    ULONG SuiteMask;

    //
    // TRUE if a kernel debugger is connected/enabled.
    //

    BOOLEAN KdDebuggerEnabled;

    //
    // Mitigation policies.
    //

    union
    {
        UCHAR MitigationPolicies;
        struct
        {
            UCHAR NXSupportPolicy : 2;
            UCHAR SEHValidationPolicy : 2;
            UCHAR CurDirDevicesSkippedForDlls : 2;
            UCHAR Reserved : 2;
        };
    };

    //
    // Measured duration of a single processor yield, in cycles. This is used by
    // lock packages to determine how many times to spin waiting for a state
    // change before blocking.
    //

    USHORT CyclesPerYield;

    //
    // Current console session Id. Always zero on non-TS systems.
    //
    // N.B. This field must be accessed via the RtlGetActiveConsoleId API for an
    //      accurate result.
    //

    volatile ULONG ActiveConsoleId;

    //
    // Force-dismounts cause handles to become invalid. Rather than always
    // probe handles, a serial number of dismounts is maintained that clients
    // can use to see if they need to probe handles.
    //

    volatile ULONG DismountCount;

    //
    // This field indicates the status of the 64-bit COM+ package on the
    // system. It indicates whether the Itermediate Language (IL) COM+
    // images need to use the 64-bit COM+ runtime or the 32-bit COM+ runtime.
    //

    ULONG ComPlusPackage;

    //
    // Time in tick count for system-wide last user input across all terminal
    // sessions. For MP performance, it is not updated all the time (e.g. once
    // a minute per session). It is used for idle detection.
    //

    ULONG LastSystemRITEventTickCount;

    //
    // Number of physical pages in the system. This can dynamically change as
    // physical memory can be added or removed from a running system.  This
    // cell is too small to hold the non-truncated value on very large memory
    // machines so code that needs the full value should access
    // FullNumberOfPhysicalPages instead.
    //

    ULONG NumberOfPhysicalPages;

    //
    // True if the system was booted in safe boot mode.
    //

    BOOLEAN SafeBootMode;

    //
    // Virtualization flags.
    //

    union
    {
        UCHAR VirtualizationFlags;

#if defined(_ARM64_)

        //
        // N.B. Keep this bitfield in sync with the one in arc.w.
        //

        struct
        {
            UCHAR ArchStartedInEl2 : 1;
            UCHAR QcSlIsSupported : 1;
            UCHAR : 6;
        };

#endif

    };

    //
    // Reserved (available for reuse).
    //

    UCHAR Reserved12[2];

    //
    // This is a packed bitfield that contains various flags concerning
    // the system state. They must be manipulated using interlocked
    // operations.
    //
    // N.B. DbgMultiSessionSku must be accessed via the RtlIsMultiSessionSku
    //      API for an accurate result
    //

    union
    {
        ULONG SharedDataFlags;
        struct
        {
            //
            // The following bit fields are for the debugger only. Do not use.
            // Use the bit definitions instead.
            //

            ULONG DbgErrorPortPresent       : 1;
            ULONG DbgElevationEnabled       : 1;
            ULONG DbgVirtEnabled            : 1;
            ULONG DbgInstallerDetectEnabled : 1;
            ULONG DbgLkgEnabled             : 1;
            ULONG DbgDynProcessorEnabled    : 1;
            ULONG DbgConsoleBrokerEnabled   : 1;
            ULONG DbgSecureBootEnabled      : 1;
            ULONG DbgMultiSessionSku        : 1;
            ULONG DbgMultiUsersInSessionSku : 1;
            ULONG DbgStateSeparationEnabled : 1;
            ULONG DbgSplitTokenEnabled      : 1;
            ULONG DbgShadowAdminEnabled     : 1;
            ULONG SpareBits                 : 19;
        } DUMMYSTRUCTNAME2;
    } DUMMYUNIONNAME2;

    ULONG DataFlagsPad[1];

    //
    // Depending on the processor, the code for fast system call will differ,
    // Stub code is provided pointers below to access the appropriate code.
    //
    // N.B. The following field is only used on 32-bit systems.
    //

    ULONGLONG TestRetInstruction;

    LONGLONG QpcFrequency;

    //
    // On AMD64, this value is initialized to a nonzero value if the system
    // operates with an altered view of the system service call mechanism.
    //

    ULONG SystemCall;

    //
    // Reserved field - do not use. Used to be UserCetAvailableEnvironments.
    //

    ULONG Reserved2;

    //
    // Full 64 bit version of the number of physical pages in the system.
    // This can dynamically change as physical memory can be added or removed
    // from a running system.
    //

    ULONGLONG FullNumberOfPhysicalPages;

    //
    // Reserved, available for reuse.
    //

    ULONGLONG SystemCallPad[1];

    //
    // The 64-bit tick count.
    //

    union
    {
        volatile KSYSTEM_TIME TickCount;
        volatile ULONG64 TickCountQuad;
        struct
        {
            ULONG ReservedTickCountOverlay[3];
            ULONG TickCountPad[1];
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME3;

    //
    // Cookie for encoding pointers system wide.
    //

    ULONG Cookie;
    ULONG CookiePad[1];

    //
    // Client id of the process having the focus in the current
    // active console session id.
    //
    // N.B. This field must be accessed via the
    //      RtlGetConsoleSessionForegroundProcessId API for an accurate result.
    //

    LONGLONG ConsoleSessionForegroundProcessId;

    //
    // N.B. The following data is used to implement the precise time
    //      services. It is aligned on a 64-byte cache-line boundary and
    //      arranged in the order of typical accesses.
    //
    // Placeholder for the (internal) time update lock.
    //

    ULONGLONG TimeUpdateLock;

    //
    // The performance counter value used to establish the current system time.
    //

    ULONGLONG BaselineSystemTimeQpc;

    //
    // The performance counter value used to compute the last interrupt time.
    //

    ULONGLONG BaselineInterruptTimeQpc;

    //
    // The scaled number of system time seconds represented by a single
    // performance count (this value may vary to achieve time synchronization).
    //

    ULONGLONG QpcSystemTimeIncrement;

    //
    // The scaled number of interrupt time seconds represented by a single
    // performance count (this value is constant after the system is booted).
    //

    ULONGLONG QpcInterruptTimeIncrement;

    //
    // The scaling shift count applied to the performance counter system time
    // increment.
    //

    UCHAR QpcSystemTimeIncrementShift;

    //
    // The scaling shift count applied to the performance counter interrupt time
    // increment.
    //

    UCHAR QpcInterruptTimeIncrementShift;

    //
    // The count of unparked processors.
    //

    USHORT UnparkedProcessorCount;

    //
    // A bitmask of enclave features supported on this system.
    //
    // N.B. This field must be accessed via the RtlIsEnclaveFeaturePresent API for an
    //      accurate result.
    //

    ULONG EnclaveFeatureMask[4];

    //
    // Current coverage round for telemetry based coverage.
    //

    ULONG TelemetryCoverageRound;

    //
    // The following field is used for ETW user mode global logging
    // (UMGL).
    //

    USHORT UserModeGlobalLogger[16];

    //
    // Settings that can enable the use of Image File Execution Options
    // from HKCU in addition to the original HKLM.
    //

    ULONG ImageFileExecutionOptions;

    //
    // Generation of the kernel structure holding system language information
    //

    ULONG LangGenerationCount;

    //
    // Reserved (available for reuse).
    //

    ULONGLONG Reserved4;

    //
    // Current 64-bit interrupt time bias in 100ns units.
    //

    volatile ULONGLONG InterruptTimeBias;

    //
    // Current 64-bit performance counter bias, in performance counter units
    // before the shift is applied.
    //

    volatile ULONGLONG QpcBias;

    //
    // Number of active processors and groups.
    //

    ULONG ActiveProcessorCount;
    volatile UCHAR ActiveGroupCount;

    //
    // Reserved (available for re-use).
    //

    UCHAR Reserved9;

    union
    {
        USHORT QpcData;
        struct
        {
            //
            // A bitfield indicating whether performance counter queries can
            // read the counter directly (bypassing the system call) and flags.
            //

            volatile UCHAR QpcBypassEnabled;

            //
            // Reserved, leave as zero for backward compatibility. Was shift
            // applied to the raw counter value to derive QPC count.
            //

            UCHAR QpcReserved;
        };
    };

    LARGE_INTEGER TimeZoneBiasEffectiveStart;
    LARGE_INTEGER TimeZoneBiasEffectiveEnd;

    //
    // Extended processor state configuration (AMD64 and x86).
    //

    XSTATE_CONFIGURATION XState;

    KSYSTEM_TIME FeatureConfigurationChangeStamp;
    ULONG Spare;

    ULONG64 UserPointerAuthMask;

    //
    // Extended processor state configuration (ARM64). The reserved space for
    // other architectures is not available for reuse.
    //

#if defined(_ARM64_)
    XSTATE_CONFIGURATION XStateArm64;
#else
    ULONG Reserved10[210];
#endif
} KUSER_SHARED_DATA, *PKUSER_SHARED_DATA;

#define USER_SHARED_DATA ((KUSER_SHARED_DATA * const)0x7ffe0000)

extern NTSTATUS NTAPI NtDisplayString(PUNICODE_STRING String);
extern NTSTATUS NTAPI NtAllocateVirtualMemory(HANDLE, PVOID, ULONG_PTR, PSIZE_T, ULONG, ULONG);
extern NTSTATUS NTAPI NtFreeVirtualMemory(HANDLE, PVOID, PSIZE_T, ULONG);
extern NTSTATUS NTAPI NtDelayExecution(BOOL, PLARGE_INTEGER);
extern NTSTATUS NTAPI RtlAdjustPrivilege(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
extern NTSTATUS NTAPI NtCreateEvent(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, EVENT_TYPE, BOOL);
extern NTSTATUS NTAPI NtReadFile(HANDLE, HANDLE, PIO_APC_ROUTINE, PVOID, PIO_STATUS_BLOCK, PVOID, ULONG, PLARGE_INTEGER, PULONG);
extern NTSTATUS NTAPI NtCreateFile(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, PIO_STATUS_BLOCK, PLARGE_INTEGER, ULONG, ULONG, ULONG, ULONG, PVOID, ULONG);
extern NTSTATUS NTAPI NtClose(HANDLE);
extern NTSTATUS NTAPI NtWaitForSingleObject(HANDLE, BOOLEAN, PLARGE_INTEGER);
extern NTSTATUS NTAPI NtOpenFile(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, PIO_STATUS_BLOCK, ULONG, ULONG);
extern NTSTATUS NTAPI NtCreateSection(PHANDLE,ACCESS_MASK,POBJECT_ATTRIBUTES,PLARGE_INTEGER,ULONG,ULONG,HANDLE FileHandle);
extern NTSTATUS NTAPI RtlCreateUserThread(HANDLE, PSECURITY_DESCRIPTOR, BOOLEAN, ULONG, PVOID, PVOID, PUSER_THREAD_START_ROUTINE, PVOID, PHANDLE, CLIENT_ID*);
extern NTSTATUS NTAPI RtlCreateUserProcess(PUNICODE_STRING,ULONG ,PRTL_USER_PROCESS_PARAMETERS ,PSECURITY_DESCRIPTOR ,PSECURITY_DESCRIPTOR ,HANDLE ,BOOLEAN ,HANDLE ,HANDLE , PRTL_USER_PROCESS_INFORMATION );
extern BOOLEAN NTAPI RtlDosPathNameToNtPathName_U(PCWSTR ,PUNICODE_STRING ,PWSTR *,PRTL_RELATIVE_NAME_U);
extern NTSTATUS NTAPI RtlCreateProcessParameters(PRTL_USER_PROCESS_PARAMETERS,PUNICODE_STRING,PUNICODE_STRING ,PUNICODE_STRING ,PUNICODE_STRING ,PVOID ,PUNICODE_STRING ,PUNICODE_STRING ,PUNICODE_STRING ,PUNICODE_STRING );
extern NTSTATUS NTAPI NtResumeThread(HANDLE ,PULONG );
extern NTSTATUS NTAPI RtlDestroyProcessParameters(PRTL_USER_PROCESS_PARAMETERS);
#define STATUS_SUCCESS  ((NTSTATUS)0x00000000L)
#define NtCurrentProcess() ((HANDLE)(LONG_PTR)-1)
#define SE_CREATE_TOKEN_PRIVILEGE       (2L)
#define SE_ASSIGNPRIMARYTOKEN_PRIVILEGE (3L)
#define SE_LOCK_MEMORY_PRIVILEGE        (4L)
#define SE_INCREASE_QUOTA_PRIVILEGE     (5L)
#define SE_UNSOLICITED_INPUT_PRIVILEGE  (6L)
#define SE_MACHINE_ACCOUNT_PRIVILEGE    (7L)
#define SE_TCB_PRIVILEGE                (8L)
#define SE_SECURITY_PRIVILEGE           (9L)
#define SE_TAKE_OWNERSHIP_PRIVILEGE     (10L)
#define SE_LOAD_DRIVER_PRIVILEGE        (10L)
#define SE_SYSTEM_PROFILE_PRIVILEGE     (11L)
#define SE_SYSTEMTIME_PRIVILEGE         (12L)
#define SE_PROF_SINGLE_PROCESS_PRIVILEGE (13L)
#define SE_INC_BASE_PRIORITY_PRIVILEGE  (14L)
#define SE_CREATE_PAGEFILE_PRIVILEGE    (15L)
#define SE_CREATE_PERMANENT_PRIVILEGE   (16L)
#define SE_BACKUP_PRIVILEGE             (17L)
#define SE_RESTORE_PRIVILEGE            (18L)
#define SE_SHUTDOWN_PRIVILEGE           (19L)
#define SE_DEBUG_PRIVILEGE              (20L)
#define SE_AUDIT_PRIVILEGE              (21L)
#define SE_SYSTEM_ENVIRONMENT_PRIVILEGE (22L)
#define SE_CHANGE_NOTIFY_PRIVILEGE      (23L)
#define SE_REMOTE_SHUTDOWN_PRIVILEGE    (24L)
#define KEY_MAKE 0x00 
#define KEY_BREAK 0x01 
#define KEY_E0 0x02 
#define KEY_E1 0x04 
#define RTL_CONSTANT_STRING(s) { sizeof(s) - sizeof((s)[0]), sizeof(s), s }
#define NtCurrentProcess() ((HANDLE)(LONG_PTR)-1)
#define EVENT_QUERY_STATE 0x0001
#define RtlMoveMemory(Destination,Source,Length) memmove((Destination),(Source),(Length))
#define RtlFillMemory(Destination,Length,Fill) memset((Destination),(Fill),(Length))
#define RtlZeroMemory(Destination,Length) memset((Destination),0,(Length))


#define VLSTRINGSIZE 512 * sizeof(WCHAR)

void VlPuts(PCWSTR string);
void* VlAlloc(size_t size);
BOOL VlFree(void* address, size_t size);
NTSTATUS VlSleep(int milliseconds);
WCHAR* Vlitow(int num, WCHAR* str);
WCHAR* VlStatusToString(NTSTATUS status, WCHAR* str);
WCHAR* VlCharToString(WCHAR character);
WCHAR VlGetKey();
WCHAR* VlGets(WCHAR* prompt, size_t size);
BOOL VlFreeString(WCHAR* string, size_t size);
void VlStrTok(WCHAR** firststring, size_t firststringsize, WCHAR** secondstring, size_t secondstringsize, WCHAR delimiter, WCHAR* sourcestring);
NTSTATUS VlCreateProcess(PCWSTR file_name, PCWSTR cmd_line);

#endif