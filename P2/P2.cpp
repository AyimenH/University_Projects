// Author: Ayimen H.
// Date: Oct 14, 2024
// Revision: First

#include "MsgStream.h"
#include "PartitionStream.h"
#include <iostream>

MsgStream* driverMsgStream = new MsgStream[4];

int main() {
    driverMsgStream[0] = MsgStream(10);
    driverMsgStream[1] = MsgStream(10);
    driverMsgStream[2] = MsgStream(10);
    driverMsgStream[3] = MsgStream(10);

    driverMsgStream[0].AppendMessage("Hello World!");
    driverMsgStream[1].AppendMessage("Hola Mundo!");
    driverMsgStream[2].AppendMessage("Konnichiwa Sekai!");
    driverMsgStream[3].AppendMessage("Sat Sri Akal, Duniya!");

    PartitionStream driverPartitionStream(driverMsgStream, 4);

    PartitionStream copyPartitionStream = driverPartitionStream;
    PartitionStream movedPartitionStream = move(driverPartitionStream);

    return 0;
}

// Implementation Invariant (kinda; didn't know where to put this info)
// Read and Write Messages simply utilize the MsgStream version and have a conditional before it
// WriteMessage does not add