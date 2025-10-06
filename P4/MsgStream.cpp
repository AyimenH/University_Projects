// Author: Ayimen H.
// Date: Nov 11, 2024
// Revision: 0th Revision

// Class Invariant:
// operationCount must always be <= operationLimit
// maxCapacity > 0 and operationLimit > 0
// subclasses of MsgStream may have differing Behaviour!
// +, =+, -, -=, ==, != are all supported
// Overloaded operators are different so look at Conditions
// -/-= operator removes values all the values in the second stream from the first stream

#include "MsgStream.h"

using namespace std;

int MsgStream::instanceCounter = 0;

MsgStream::MsgStream(int operationLimit): messageCount(0), operationLimit(operationLimit), operationCount(0)
{
    instanceCounter++;
    maxCapacity = (operationLimit + instanceCounter) % (MaxCapacity) + 8;

    this->operationLimit = operationLimit;
    messages = new string[maxCapacity];
}

MsgStream::MsgStream()
{
    operationLimit = 16;
    instanceCounter++;
    maxCapacity = (operationLimit + instanceCounter) % (MaxCapacity) + 8;

    this->operationLimit = operationLimit;
    messages = new string[maxCapacity];
}

void MsgStream::IsOperationAllowed()
{
    if (operationCount >= operationLimit)
    {
        throw runtime_error("Maximum Operation Limit reached!");
    }
}

// Appending does not increment Operation Count

void MsgStream::AppendMessage(const string& message)
{
    if (messageCount >= maxCapacity)
    {
        throw invalid_argument("Maximum Message Limit reached!");
    }

    messages[messageCount] = message;
    messageCount++;
}

string* MsgStream::ReadMessages(int startingMessage, int endingMessage)
{
    IsOperationAllowed();

    if (startingMessage < 0 || endingMessage >= messageCount || startingMessage > endingMessage)
    {
        throw out_of_range("Message range is invalid!");
    }

    int rangeSize = endingMessage - startingMessage + 1;
    string* clientSideArray = new string[rangeSize];

    for (int i = 0; i < rangeSize; ++i)
    {
        clientSideArray[i] = messages[startingMessage + i];
    }

    operationCount++;
    return clientSideArray;
}

MsgStream::MsgStream(const MsgStream& src)
{
    messageCount = src.messageCount;
    maxCapacity = src.maxCapacity;

    operationLimit = src.operationLimit;
    operationCount = src.operationCount;

    messages = new string[maxCapacity];

    for (int i = 0; i < messageCount; ++i)
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

    operationLimit = src.operationLimit;
    operationCount = src.operationCount;

    messages = new string[maxCapacity];
    for (int i = 0; i < messageCount; ++i)
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

void MsgStream::Reset()
{
    operationCount = 0;
    messageCount = 0;

    messages = new string[maxCapacity];
}

int MsgStream::QueryMaxCapacity() const
{
    int QueryMaxCapacity = maxCapacity;
    return QueryMaxCapacity;
}

int MsgStream::QueryCurrentMessageCount() const
{
    int QueriedMessageCount = messageCount;
    return QueriedMessageCount;
}

// PostCondition: Separate Result object is returned containing added objects messages

MsgStream MsgStream::operator+(const MsgStream& other) const
{
    MsgStream result;
    result.operationLimit = this->operationLimit;
    result.maxCapacity = min(MaxCapacity, this->messageCount + other.messageCount);

    for (int i = 0; i < this->messageCount && i < result.maxCapacity; ++i)
    {
        result.messages[i] = this->messages[i];
    }

    for (int i = 0; i < other.messageCount && (i + this->messageCount) < result.maxCapacity; ++i)
    {
        result.messages[i + this->messageCount] = other.messages[i];
    }

    result.messageCount = min(result.maxCapacity, this->messageCount + other.messageCount);
    result.operationCount = this->operationCount + other.operationCount;
    return result;
}

// PostCondition: Destructive initial object is returned containing added object's messages

MsgStream& MsgStream::operator+=(const MsgStream& other)
{
    IsOperationAllowed();
    int newMessageCount = this->messageCount + other.messageCount;

    for (int i = 0; i < other.messageCount && this->messageCount < newMessageCount; ++i)
    {
        this->messages[this->messageCount++] = other.messages[i];
    }

    ++operationCount;
    return *this;
}

// PostCondition: Separate Result object is returned containing only messages that do NOT match

MsgStream MsgStream::operator-(const MsgStream& other) const
{
    MsgStream result;
    result.operationLimit = this->operationLimit;
    result.maxCapacity = this->maxCapacity;

    for (int i = 0; i < this->messageCount; ++i)
    {
        bool match = false;
        for (int j = 0; j < other.messageCount; ++j)
        {
            if (this->messages[i] == other.messages[j])
            {
                match = true;
                break;
            }
        }

        if (!match && result.messageCount < result.maxCapacity)
        {
            result.messages[result.messageCount++] = this->messages[i];
        }
    }

    result.operationCount = this->operationCount;
    return result;
}

// PostCondition: Destructive initial object is returned containing only messages that do NOT match

MsgStream& MsgStream::operator-=(const MsgStream& other) {
    IsOperationAllowed();

    for (int i = 0; i < this->messageCount; ++i)
    {
        bool match = false;
        for (int j = 0; j < other.messageCount; ++j)
        {
            if (this->messages[i] == other.messages[j])
            {
                match = true;
                break;
            }
        }

        if (match)
        {
            for (int k = i; k < messageCount - 1; ++k)
            {
                messages[k] = messages[k + 1];
            }

            --messageCount;
            --i;
        }
    }

    ++operationCount;
    return *this;
}

// PostCondition: Returns Bool value of equality

bool MsgStream::operator==(const MsgStream& other) const
{
    if (this->messageCount != other.messageCount || this->operationCount != other.operationCount)
    {
        return false;
    }

    for (int i = 0; i < messageCount; ++i)
    {
        if (this->messages[i] != other.messages[i])
        {
            return false;
        }
    }
    return true;
}

bool MsgStream::operator!=(const MsgStream& other) const
{
    return !(*this == other);
}

// Implementation Invariant:
// Only `ReadMessages` increments operationCount, while `AppendMessage` does not
// Move anc Copy Semantics are supported for MsgStream