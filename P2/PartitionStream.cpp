// Author: Ayimen H.
// Date: Oct 12, 2024
// Revision: 0

// Class Invariant:
// Array is zero indexed and client should be aware of this when passing in partition key

#include "PartitionStream.h"

using namespace std;

PartitionStream::PartitionStream(MsgStream*& driverPartitionStream, unsigned driverNumPartitions)
{
    if (driverPartitionStream == nullptr || driverNumPartitions == 0)
    {
        throw invalid_argument("Unacceptable partition stream provided!");
    }

    partitionStream = driverPartitionStream;
    driverPartitionStream = nullptr;

    this -> numPartitions = driverNumPartitions;
}

void PartitionStream::writeMessage(int partitionKey, const string& message)
{
    if (partitionKey > numPartitions)
    {
        throw out_of_range("Invalid Partition Key!");
    }
    partitionStream[partitionKey].AppendMessage(message);
}

string* PartitionStream::readMessage(int partitionKey, int startingMessage, int endingMessage)
{
    if (partitionKey > numPartitions)
    {
        throw out_of_range("Invalid Partition Key!");
    }
    return partitionStream[partitionKey].ReadMessages(startingMessage, endingMessage);
}

int PartitionStream::QueryPartitionKey()
{
    int QueriedPartitionKey = numPartitions;
    return QueriedPartitionKey;
}

PartitionStream::PartitionStream(const PartitionStream& src)
{
    numPartitions = src.numPartitions;
    partitionStream = new MsgStream[numPartitions];

    for (unsigned i = 0; i < numPartitions; i++)
    {
        partitionStream[i] = src.partitionStream[i];
    }
}

PartitionStream& PartitionStream::operator= (const PartitionStream& src)
{
    if (this == &src)
    {
        return *this;
    }

    delete[] partitionStream;
    numPartitions = src.numPartitions;

    partitionStream = new MsgStream[numPartitions];
    for (unsigned i = 0; i < numPartitions; i++)
    {
        partitionStream[i] = src.partitionStream[i];
    }

    return *this;
}

PartitionStream::PartitionStream(PartitionStream&& src) noexcept
{
    numPartitions = src.numPartitions;
    partitionStream = src.partitionStream;

    src.numPartitions = 0;
    src.partitionStream = nullptr;
}

PartitionStream& PartitionStream::operator= (PartitionStream&& src) noexcept
{
    if (this == &src)
    {
        return *this;
    }

    swap(numPartitions, src.numPartitions);
    swap(partitionStream, src.partitionStream);

    return *this;
}

void PartitionStream::reset()
{
    for (unsigned i = 0; i < numPartitions; i++)
    {
        partitionStream[i].Reset();
        delete &partitionStream[i];
    }
    numPartitions = 0;
}

PartitionStream::~PartitionStream()
{
    delete[] partitionStream;
}

// Implementation Invariant:
// partitionStream must be valid after initialization
// numPartitions must reflect the actual number of MsgStream objects