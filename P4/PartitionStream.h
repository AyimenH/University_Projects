// Author: Ayimen H.
// Date: Nov 11, 2024
// Revision: 0th Revision

#ifndef PARTITIONSTREAM_H
#define PARTITIONSTREAM_H

using namespace std;

#include <iostream>
#include <string>
#include "MsgStream.h"

class PartitionStream {
private:
    int numPartitions;
    int baseNumPartitions;

    unique_ptr<MsgStream[]> partitionStream;
    unique_ptr<MsgStream[]> basePartitionStream;

public:
    PartitionStream(unique_ptr<MsgStream[]>& driverPartitionStream, int driverNumPartitions);
    PartitionStream();

    void writeMessage(int partitionKey, const string& message);
    string* readMessage(int partitionKey, int startingMessage, int endingMessage);

    int QueryPartitionKey() const;
    void reset();

    PartitionStream operator+(const PartitionStream& other) const;
    PartitionStream& operator+=(const PartitionStream& other);

    PartitionStream operator-(const PartitionStream& other) const;
    PartitionStream& operator-=(const PartitionStream& other);

    bool operator==(const PartitionStream& other) const;
    bool operator!=(const PartitionStream& other) const;
};

#endif //PARTITIONSTREAM_H
