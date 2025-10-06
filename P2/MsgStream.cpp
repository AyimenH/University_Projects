// Author: Ayimen H.
// Date: Oct 12, 2024
// Revision: 0

// Class Invariant:
// messageCount must be <= operationLimit
// messages must not be null after initialization

#include "MsgStream.h"

    MsgStream::MsgStream(int operationLimit)
     {
        srand(time(nullptr));
        maxCapacity = rand() % (MaxCapacity - 8 + 1) + 8;

        this->operationLimit = operationLimit;
        messages = new string[maxCapacity];
    }

    void MsgStream::IsOperationAllowed() {
        if (operationCount >= operationLimit) {
            throw runtime_error("Maximum Operation Limit reached!");
        }
    }

    void MsgStream::AppendMessage(const string& message) {
        if (messageCount >= maxCapacity) {
            throw runtime_error("Maximum Message capacity reached!");
        }
        messages[messageCount] = message;
        messageCount++;
    }

    string* MsgStream::ReadMessages(int startingMessage, int endingMessage) {
        IsOperationAllowed();

        if (startingMessage < 0 || endingMessage >= messageCount || startingMessage > endingMessage) {
            throw out_of_range("Message Range invalid!");
        }

        string* clientSideArray = new string[endingMessage - startingMessage + 1];
        for (int i = 0; i <= (endingMessage - startingMessage); i++) {
            clientSideArray[i] = messages[startingMessage + i];
        }

        operationCount++;
        return clientSideArray;
    }

    void MsgStream::Reset() {
        operationCount = 0;
        messageCount = 0;

        delete[] messages;
        messages = new string[maxCapacity];
    }

    int MsgStream::QueryMaxCapacity()
    {
        int QueriedMaxCapacity = maxCapacity;
        return QueriedMaxCapacity;
    }

    MsgStream::MsgStream(const MsgStream& src)
    {
        messageCount = src.messageCount;
        maxCapacity = src.maxCapacity;
        messages = new string[maxCapacity];

        for (unsigned i = 0; i < maxCapacity; ++i)
        {
            messages[i] = src.messages[i];
        }
    }

    MsgStream& MsgStream::operator=(const MsgStream& src)
    {
        if (this == &src)
        {
            return *this;
        }

        delete[] messages;
        messageCount = src.messageCount;
        maxCapacity = src.maxCapacity;

        messages = new string[maxCapacity];
        for (unsigned i = 0; i < maxCapacity; ++i)
        {
            messages[i] = src.messages[i];
        }

        return *this;
    }

    MsgStream::MsgStream(MsgStream&& src) noexcept
    {
        messageCount = src.messageCount;
        maxCapacity = src.maxCapacity;
        messages = src.messages;

        src.messageCount = 0;
        src.maxCapacity = 0;
        src.messages = nullptr;
    }

    MsgStream& MsgStream::operator=(MsgStream&& src) noexcept
    {
        if (this == &src)
        {
            return *this;
        }

        swap(messageCount, src.messageCount);
        swap(messages, src.messages);
        swap(maxCapacity, src.maxCapacity);

        return *this;
    }

    int MsgStream::QueryCurrentMessageCount()
        {
            int QueriedMessageCount = messageCount;
            return QueriedMessageCount;
        }

// Implementation Invariant:
// Appending does not increment the operationCount but reading messages does
// Array size should not be modified so maxCapacity can be used in error handling
// MaxCapacity should have a minimum value > 0 so error checking works properly
