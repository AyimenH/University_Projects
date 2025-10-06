// Author: Ayimen H.
// Date: Nov 25, 2024
// Revision: 0th Revision


// Class Invariant:
// basePartitionStream holds the initial copies of partitionStream for use in reset operations
// ^ for numPartitions
// Array is zero indexed and client should be aware of this when passing in partition key

using System;
using System.IO;
using System.Runtime.CompilerServices;

namespace P5;

public class PartitionStream: IDisposable
{ 
    private MsgStream[] partitionStream;
    private int numPartitions;
    
    private MsgStream[] basePartitionStream;
    private int baseNumPartitions;

    private bool isDisposed = false;
    
    // PostCondition: Initializes PartitionStream with deep copies of partition streams
    public PartitionStream(MsgStream[] driverPartitionStream, int driverNumPartitions)
    {
        if (driverPartitionStream == null || driverNumPartitions == 0)
        {
            throw new ArgumentException("Unacceptable partition stream provided!");
        }

        partitionStream = driverPartitionStream;
        driverPartitionStream = null;
        numPartitions = driverNumPartitions;
        
        basePartitionStream = new MsgStream[numPartitions];
        baseNumPartitions = numPartitions;

        for (int i = 0; i < numPartitions; i++)
        {
            basePartitionStream[i] = partitionStream[i].DeepCopy();
        }
    }
    
    public void WriteMessage(int partitionKey, string message)
    {
        try
        {
            if (partitionKey > numPartitions || partitionKey < 0)
            {
                throw new ArgumentOutOfRangeException("Invalid Partition Key!");
            }
            partitionStream[partitionKey].AppendMessage(message);
        }
        
        catch (Exception e)
        {
            Console.WriteLine($"Error in WriteMessage: {e.Message}");
            throw;
        }
    }
    
    public string[] ReadMessage(int partitionKey, int startingMessage, int endingMessage)
    {
        try
        {
            if (partitionKey > numPartitions || partitionKey < 0)
            {
                throw new ArgumentOutOfRangeException("Invalid Partition Key!");
            }
            return partitionStream[partitionKey].ReadMessages(startingMessage, endingMessage);
        }
        
        catch (Exception e)
        {
            Console.WriteLine($"Error in ReadMessage: {e.Message}");
            throw;
        }
    }
    
    public PartitionStream DeepCopy()
    {
        MsgStream[] copiedStreams = new MsgStream[numPartitions];
        for (int i = 0; i < numPartitions; i++)
        {
            copiedStreams[i] = partitionStream[i].DeepCopy();
        }
    
        PartitionStream copy = new PartitionStream(copiedStreams, numPartitions);
        return copy;
    }
    
    public int QueryPartitionKey()
    {
        int QueriedPartitionKey = numPartitions;
        return QueriedPartitionKey;
    }
    
    // PostCondition: Restores partitionStream to its initial base state
    public void Reset()
    {
        for (int i = 0; i < numPartitions; i++)
        {
            basePartitionStream[i].Reset();
            partitionStream[i] = basePartitionStream[i];
        }
        
        numPartitions = baseNumPartitions;
    }
    
    public void Dispose()
    {
        Dispose(true);
        GC.SuppressFinalize(this);
    }

    protected virtual void Dispose(bool isDisposing)
    {
        if (isDisposing)
        {
            if (isDisposing)
            {
                if (partitionStream != null)
                {
                    for (int i = 0; i < partitionStream.Length; i++)
                    {
                        MsgStream msgStream = partitionStream[i];
                        if (msgStream is IDisposable disposableStream)
                        {
                            disposableStream.Dispose();
                        }
                    }
                }

                if (basePartitionStream != null)
                {
                    for (int i = 0; i < basePartitionStream.Length; i++)
                    {
                        MsgStream msgStream = basePartitionStream[i];
                        if (msgStream is IDisposable disposableStream)
                        {
                            disposableStream.Dispose();
                        }
                    }
                }
            }
            
            isDisposed = true;
        }
    }
}

// Implementation Invariant:
// Append and Read operations are restricted to valid partition indices