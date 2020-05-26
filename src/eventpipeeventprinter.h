
#pragma once

#include "eventpipemetadatareader.h"
#include <vector>
#include <assert.h>

class EventPipeEventPrinter
{
    LPWSTR TypeCodeToString(EventPipeTypeCode typeCode);

    void PrintIndentLevel(ULONG level);
    void PrintGuid(LPCGUID guid);

    bool PrintType(EventPipeDataDescriptor type,
                   ULONG indentLevel, // number of tabs to put in
                   LPCBYTE eventData,
                   ULONG cbEventData,
                   ULONG *offset);

    bool PrintParam(EventPipeDataDescriptor descriptor,
                    ULONG indentLevel, // number of tabs to put in
                    LPCBYTE eventData,
                    ULONG cbEventData,
                    ULONG *offset);

public:
    EventPipeEventPrinter();
    ~EventPipeEventPrinter() = default;

    void PrintEvent(LPCWSTR providerName,
                    EventPipeMetadataInstance metadata,
                    LPCBYTE eventData,
                    ULONG cbEventData,
                    LPCGUID pActivityId,
                    LPCGUID pRelatedActivityId,
                    ThreadID eventThread,
                    UINT_PTR stackFrames[],
                    ULONG numStackFrames);
};
