// Author: Ayimen H.
// Date: Oct 3, 2024
// Revision: First one?
// Class Invariant:
// messageCount must be >= to maxCapacity.
// operationCount must be >= to operationLimit.

using System;

namespace P1
{
    public class MsgStream
    {
        private const int OperationLimit = 16;
        private const int MaxCapacity = 64;
        private string[] messages;
        private int maxCapacity;
        private int operationLimit;
        private int operationCount;
        private int messageCount;

        // PreCondition: OperationLimit > 0
        public MsgStream(int operationLimit = OperationLimit)
        {
            Random random = new Random();
            maxCapacity = random.Next(8, MaxCapacity + 1);
            this.operationLimit = operationLimit;
            operationCount = 0;
            messageCount = 0;
            messages = new string[maxCapacity];
        }

        private void IsOperationAllowed()
        {
            if (operationCount >= operationLimit)
            {
                throw new InvalidOperationException("Maximum Operation Limit reached!");
            }
        }

        // PreCondition: MsgStream must not be full
        public void AppendMessage(string message)
        {
            if (messageCount >= maxCapacity)
            {
                throw new InvalidOperationException("Maximum Message capacity reached!");
            }
            messages[messageCount] = message;
            messageCount++;
        }

        // PreCondition: startingMessage and endingMessages must be valid indexes within the array
        // PostCondition: Returns array of messages within designated range
        public string[] ReadMessages(int startingMessage, int endingMessage)
        {
            IsOperationAllowed();

            if (startingMessage < 0 || endingMessage >= messageCount || startingMessage > endingMessage)
            {
                throw new ArgumentOutOfRangeException("Message Range invalid!");
            }

            int messageRangeLength = endingMessage - startingMessage + 1;
            string[] clientSideArray = new string[messageRangeLength];
            Array.Copy(messages, startingMessage, clientSideArray, 0, messageRangeLength);

            // Increment operation count after successful read operation
            operationCount++;
            return clientSideArray;
        }

        // PostCondition: All counters are set to zero and messages is emptied.
        public void Reset()
        {
            operationCount = 0;
            messageCount = 0;
            messages = new string[maxCapacity];
        }

        // Postcondition: returns copy of maxCapacity for use in testing
        public int QueryMaxCapacity()
        {
            int QueriedMaxCapacity = maxCapacity;
            return QueriedMaxCapacity;
        }
    }
}

// Implementation Invariant:
// Appending does not increment the operationCount but reading messages does.
// Array size should not be modified so maxCapacity can be used in error handling.
// MaxCapacity should have a minimum value > 0 so error checking works properly.
