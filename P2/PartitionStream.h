// Author: Ayimen H.
// Date: Oct 12, 2024
// Revision: 0

#ifndef PARTITIONSTREAM_H
#define PARTITIONSTREAM_H
#include "MsgStream.h"

using namespace std;

class PartitionStream {
    private:
        MsgStream* partitionStream;
        int numPartitions = 0;

    public:
        PartitionStream(MsgStream* &partitionStream, unsigned numPartitions);

        // PreCondition: The partition stream is valid
        // PostCondition: A message is appended to the MsgStream based on the partition key
        void writeMessage(int partitionKey, const string& message);

        // PreCondition: The partition stream is valid
        // PostCondition: Returns the next message from the MsgStream based on the partition key
        string* readMessage(int partitionKey, int startingMessage, int endingMessage);

        PartitionStream(const PartitionStream& src);
        PartitionStream& operator=(const PartitionStream& src);

        PartitionStream(PartitionStream&& src) noexcept;
        PartitionStream& operator=(PartitionStream&& src) noexcept;

        int QueryPartitionKey();

        void reset();

        ~PartitionStream();
};

#endif //PARTITIONSTREAM_H
