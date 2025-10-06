// Author: Ayimen H.
// Date: Nov 11, 2024
// Revision: 0th Revision

// Class Invariant:
// basePartitionStream holds the initial copies of partitionStream for use in reset operations
// ^ for numPartitions
// Array is zero indexed and client should be aware of this when passing in partition key
// +, =+, -, -=, ==, != are all supported
// Overloaded operators are different so look at Conditions
// -/-= operator removes values all the values in the second stream from the first stream

#include "PartitionStream.h"

using namespace std;

PartitionStream::PartitionStream(unique_ptr<MsgStream[]>& driverPartitionStream, int driverNumPartitions)
{
    if (driverPartitionStream == nullptr || driverNumPartitions == 0)
    {
        throw invalid_argument("Unacceptable partition stream provided!");
    }

    numPartitions = driverNumPartitions;
    baseNumPartitions = driverNumPartitions;

    partitionStream = make_unique<MsgStream[]>(numPartitions);
    basePartitionStream = make_unique<MsgStream[]>(numPartitions);

    for (int i = 0; i < numPartitions; i++)
    {
        partitionStream[i] = driverPartitionStream[i];
        basePartitionStream[i] = driverPartitionStream[i];
    }
}

PartitionStream::PartitionStream()
{
    numPartitions = 0;
    baseNumPartitions = 0;

    partitionStream = nullptr;
    basePartitionStream = nullptr;
}

void PartitionStream::writeMessage(int partitionKey, const string& message)
{
    if (partitionKey >= numPartitions || partitionKey < 0)
    {
        throw out_of_range("Invalid Partition Key!");
    }

    partitionStream[partitionKey].AppendMessage(message);
}

string* PartitionStream::readMessage(int partitionKey, int startingMessage, int endingMessage) {
    if (partitionKey >= numPartitions || partitionKey < 0) {
        throw out_of_range("Invalid Partition Key!");
    }
    return partitionStream[partitionKey].ReadMessages(startingMessage, endingMessage);
}

int PartitionStream::QueryPartitionKey() const {
    int QueriedPartitionKey = numPartitions;
    return QueriedPartitionKey;
}

void PartitionStream::reset() {
    for (int i = 0; i < numPartitions; i++)
    {
        basePartitionStream[i].Reset();
        partitionStream[i] = basePartitionStream[i];
    }

    numPartitions = baseNumPartitions;
}

// PostCondition: New PartitionStream returned with numPartitions of both streams and their values

PartitionStream PartitionStream::operator+(const PartitionStream& other) const
{
    int combinedNumPartitions = numPartitions + other.numPartitions;
    unique_ptr<MsgStream[]> combinedStream = make_unique<MsgStream[]>(combinedNumPartitions);

    for (int i = 0; i < numPartitions; ++i)
    {
        combinedStream[i] = partitionStream[i];
    }

    for (int i = 0; i < other.numPartitions && (i + numPartitions) < combinedNumPartitions; ++i)
    {
        combinedStream[i + numPartitions] = other.partitionStream[i];
    }

    return PartitionStream(combinedStream, combinedNumPartitions);
}

// PostCondition: current PartitionStream returned with numPartitions of both streams and their values

PartitionStream& PartitionStream::operator+=(const PartitionStream& other)
{
    int newPartitionCount = numPartitions + other.numPartitions;

    for (int i = 0; i < other.numPartitions && numPartitions < newPartitionCount; ++i)
    {
        partitionStream[numPartitions++] = other.partitionStream[i];
    }

    return *this;
}

// PostCondition: New PartitionStream returned with only values that are not in both streams

PartitionStream PartitionStream::operator-(const PartitionStream& other) const
{
    unique_ptr<MsgStream[]> resultStream = make_unique<MsgStream[]>(numPartitions);
    int resultCount = 0;

    for (int i = 0; i < numPartitions; ++i)
    {
        bool match = false;
        for (int j = 0; j < other.numPartitions; ++j)
        {
            if (partitionStream[i] == other.partitionStream[j])
            {
                match = true;
                break;
            }
        }

        if (!match)
        {
            resultStream[resultCount++] = partitionStream[i];
        }
    }

    return PartitionStream(resultStream, resultCount);
}

// PostCondition: Current PartitionStream returned with only values that are not in both streams

PartitionStream& PartitionStream::operator-=(const PartitionStream& other)
{
    for (int i = 0; i < numPartitions; ++i)
    {
        bool match = false;
        for (int j = 0; j < other.numPartitions; ++j)
        {
            if (partitionStream[i] == other.partitionStream[j])
            {
                match = true;
                break;
            }
        }

        if (match)
        {
            for (int k = i; k < numPartitions - 1; ++k)
            {
                partitionStream[k] = partitionStream[k + 1];
            }

            --numPartitions;
            --i;
        }
    }

    return *this;
}

// PostCondition: Equality checked returns bool

bool PartitionStream::operator==(const PartitionStream& other) const
{
    if (numPartitions != other.numPartitions)
    {
        return false;
    }

    for (int i = 0; i < numPartitions; ++i)
    {
        if (partitionStream[i].QueryCurrentMessageCount() != other.partitionStream[i].QueryCurrentMessageCount())
        {
            return false;
        }

        int msgCount = partitionStream[i].QueryCurrentMessageCount();
        if (msgCount > 0)
        {
            try
            {
                string* messages1 = partitionStream[i].ReadMessages(0, msgCount - 1);
                string* messages2 = other.partitionStream[i].ReadMessages(0, msgCount - 1);

                for (int j = 0; j < msgCount; ++j)
                {
                    if (messages1[j] != messages2[j])
                    {
                        delete[] messages1;
                        delete[] messages2;

                        return false;
                    }
                }

                delete[] messages1;
                delete[] messages2;
            }

            catch (const exception& e)
            {
                return false;
            }
        }
    }
    return true;
}

bool PartitionStream::operator!=(const PartitionStream& other) const
{
    return !(*this == other);
}

// Implementation Invariant:
// Append and Read operations are restricted to valid partition indices
// PartitionStreams are now utilizing unique ptrs
// ^ Move and Copy not supported and no destructor due to this