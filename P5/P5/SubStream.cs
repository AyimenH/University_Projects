// Author: Ayimen H.
// Date: Nov 25, 2024
// Revision: 0th Revision

// Class Invariant:
// subPartitionStream must be a valid PartitionStream
// Subscribers are tracking every time a message is written to any partition

using System;

namespace P5;

public interface ISubscriber
{
    void NewMessage();
}

public class Subscribers : ISubscriber
{
    private int messagesAppended;
    
    public void NewMessage()
    {
        messagesAppended++;
    }

    public int queryMessageAppended()
    {
        int QueryMessageAppended = messagesAppended;
        return QueryMessageAppended;
    }
}

public class SubStream : Subscribers
{
    private PartitionStream subPartitionStream;
    private Subscribers[] subscribers;
    private int subscriberCount;

    // PreCondition: 
    // driverPartitionStream must be a non-null array of MsgStream
    // driverNumPartitions must be > 0
    
    // PostCondition:
    // subPartitionStream is initialized with given streams and partitions
    // Each subscriber is initialized to a new Subscribers object
    
    public SubStream(MsgStream[] driverPartitionStream, int driverNumPartitions)
    {
        if (driverPartitionStream == null || driverNumPartitions == 0)
        {
            throw new ArgumentException("Unacceptable partition stream provided!");
        }
        
        subPartitionStream = new PartitionStream(driverPartitionStream, driverNumPartitions);
        subscribers = new Subscribers[driverNumPartitions];
        
        for (int i = 0; i < driverNumPartitions; i++)
        {
            subscribers[i] = new Subscribers();
        }
        
        subscriberCount = driverNumPartitions;
    }

    public void WriteMessage(int partitionKey, string message)
    {
        subPartitionStream.WriteMessage(partitionKey, message);
        
        for (int i = 0; i < subscriberCount; i++)
        {
            subscribers[i].NewMessage();
        }
    }

    public int[] QuerySubscribers()
    { 
        int[] queriedSubscribers = new int[subscriberCount];

        for (int i = 0; i < subscriberCount; i++)
        {
            queriedSubscribers[i] = subscribers[i].queryMessageAppended();
        }
        
        return queriedSubscribers;
    }
}

// Implementation Invariant:
// Subscriber message counts are for each object
// subscriberCount is equal to driverNumPartitions
// Subscribers only track the number of messages