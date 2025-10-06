// Author: Ayimen H.
// Date: Nov 25, 2024
// Revision: 0th Revision


// Class Invariant:
// operationCount must always be <= operationLimit
// maxCapacity > 0 and operationLimit > 0
// subclasses of MsgStream may have differing Behaviour!

using System;
using System.Runtime.CompilerServices;

namespace P5;

public class MsgStream
{
    protected static readonly int OperationLimit = 16;
    protected static readonly int MaxCapacity = 64;
    protected static int instanceCounter; 

    protected string[] messages;
    protected int messageCount;
    
    protected int maxCapacity;
    
    protected int operationLimit;
    protected int operationCount;
    
    public MsgStream(int operationLimit)
    {
        instanceCounter++;
        maxCapacity = (operationLimit + instanceCounter) % (MaxCapacity - 8 + 1);
        
        this.operationLimit = operationLimit;
        messages = new string[maxCapacity];
    }
    
    protected void IsOperationAllowed()
    {
        try
        {
            if (operationCount >= operationLimit)
            {
                throw new InvalidOperationException("Maximum Operation Limit reached!");
            }
        }
        
        catch (Exception e)
        {
            Console.WriteLine($"Operation not allowed: {e.Message}");
            throw;
        }
    }

    public virtual void AppendMessage(string message)
    {
        try
        {
            if (messageCount >= maxCapacity)
            {
                throw new InvalidOperationException("Maximum Message Limit reached!");
            }

            messages[messageCount] = message;
            messageCount++;
        }
        
        catch (Exception e)
        {
            Console.WriteLine($"Error in AppendMessage: {e.Message}");
            throw;
        }
    }
    
    public string[] ReadMessages(int startingMessage, int endingMessage)
    {
        try
        {
            IsOperationAllowed();

            if (startingMessage < 0 || endingMessage >= messageCount || startingMessage > endingMessage)
            {
                throw new ArgumentOutOfRangeException("Message range is invalid!");
            }

            string[] clientSideArray = new string[endingMessage - startingMessage + 1];
            for (int i = 0; i <= (endingMessage - startingMessage); i++)
            {
                clientSideArray[i] = messages[startingMessage + i];
            }

            operationCount++;
            return clientSideArray;
        }
        
        catch (Exception e)
        {
            Console.WriteLine($"Error in ReadMessages: {e.Message}");
            throw;
        }
    }
    
    public void Reset()
    {
        operationCount = 0;
        messageCount = 0;
        
        messages = new string[maxCapacity];
    }
    
    public int QueryMaxCapacity()
    {
        int QueriedMaxCapacity = maxCapacity;
        return QueriedMaxCapacity;
    }
    
    public int QueryCurrentMessageCount()
    {
        int QueriedMessageCount = messageCount;
        return QueriedMessageCount;
    }
    
    // PostCondition: Returns a new MsgStream instance with the same data and state
    public virtual MsgStream DeepCopy()
    {
        MsgStream copy = new MsgStream(operationLimit);
        copy.messageCount = messageCount;
        
        copy.operationLimit = operationLimit;
        copy.operationCount = operationCount;
        copy.maxCapacity = maxCapacity;
        
        copy.messages = new string[maxCapacity];

        for (int i = 0; i < messageCount; i++)
        {
            copy.messages[i] = messages[i];
        }

        return copy;
    }
}

// Implementation Invariant:
// Only `ReadMessages` increments operationCount, while `AppendMessage` does not
// The maxCapacity remains constant after initialization