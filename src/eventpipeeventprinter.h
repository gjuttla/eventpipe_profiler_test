
#pragma once

#include "eventpipemetadatareader.h"
#include <vector>
#include <assert.h>

class EventPipeEventPrinter
{
    LPWSTR TypeCodeToString(EventPipeTypeCode typeCode);

    void PrintIndentLevel(ULONG level);

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

    void PrintEvent(LPWSTR providerName,
                    EventPipeMetadataInstance metadata,
                    DWORD eventThreadId,
                    LPCBYTE eventData,
                    ULONG cbEventData,
                    UINT_PTR stackFrames[],
                    ULONG numStackFrames);
};
