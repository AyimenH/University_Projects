// Author: Ayimen H.
// Date: Oct 27, 2024
// Revision: 0th Revision

// Class Invariant:
// baseMessageCount and messageCount must always be <= maxCapacity
// File I/O operations only occur in chunks (every 4th message) or upon reset=
// subclass of MsgStream

using System;
using System.IO;
using System.Runtime.CompilerServices;


namespace P3;

public class DurableStream: MsgStream
{
    private string[] baseMessages;
    private int baseMessageCount;
    
    private string[] baseFile;
    private int baseFileCount;
    
    private readonly string filePath;
    private bool fileClosed = false;

    // PostCondition: Contains messages from an existing file if available
    public DurableStream(int operationLimit, string filePath) : base(operationLimit)
    {
        if (filePath == null)
        {
            throw new ArgumentNullException(nameof(filePath));
        }
        
        this.filePath = filePath;
        baseMessages = new string[messageCount];
        
        for (int i = 0; i < messageCount; i++)
        {
            baseMessages[i] = messages[i];
        }
        
        baseMessageCount = messageCount;
        baseFile = new string[maxCapacity];

        if (File.Exists(filePath))
        {
            LoadMsgFromFile();
        }
    }

    public override void AppendMessage(string message)
    {
        base.AppendMessage(message);
        if (messageCount % 4 == 0 || messageCount == 0)
        {
            WriteMsgToFile();
        }
        
        Dispose();
    }

    // PreCondition: File at filePath exists and is accessible.
    private void LoadMsgFromFile()
    {
        try
        { 
            using (FileStream fileStream = new FileStream(filePath, FileMode.Open, FileAccess.Read))
            using (BufferedStream bufferedStream = new BufferedStream(fileStream))
            using (StreamReader reader = new StreamReader(bufferedStream))
            {
                string line;
                while ((line = reader.ReadLine()) != null && messageCount < maxCapacity)
                {
                    messages[messageCount] = line;
                    baseFile[messageCount] = line;
                    messageCount++;
                }
                baseFileCount = messageCount;
            }
        }
        catch (IOException e)
        {
            Console.WriteLine("Error in LoadMsgFromFile!: " + e.Message);
            throw;
        }
    }
    
    // PostCondition: Appends all messages in memory to the file at filePath.
    public void WriteMsgToFile()
    {
        try
        {
            using (FileStream fileStream = new FileStream(filePath, FileMode.Append, FileAccess.Write))
            using (BufferedStream bufferedStream = new BufferedStream(fileStream))
            using (StreamWriter writer = new StreamWriter(bufferedStream))
            {
                for (int i = 0; i < messageCount; i++)
                {
                    writer.WriteLine(messages[i]);
                }
                writer.Flush();
            }
        }
        catch (IOException e)
        {
            Console.WriteLine("Error in WriteMsgToFile!: " + e.Message);
        }
    }
    
    private void WriteMsgFromFile()
    {
        try
        {
            using (FileStream fileStream = new FileStream(filePath, FileMode.Append, FileAccess.Write))
            using (BufferedStream bufferedStream = new BufferedStream(fileStream))
            using (StreamWriter writer = new StreamWriter(bufferedStream))
            {
                for (int i = 0; i < baseFileCount; i++)
                {
                    writer.WriteLine(baseFile[i]);
                }
                writer.Flush();
            }
        }
        catch (IOException e)
        {
            Console.WriteLine("Error in WriteMsgFromFile!: " + e.Message);
        }
    }
    
    public void Dispose()
    {
        if (!fileClosed)
        {
            try
            {
                using (FileStream fileStream = new FileStream(filePath, FileMode.OpenOrCreate, FileAccess.Write))
                {
                    fileStream.Close();
                }

                fileClosed = true;
            }
            catch (IOException e)
            {
                Console.WriteLine("Error in Dispose!: " + e.Message);
            }
        }
    }
    
    // PostCondition: Resets memory to base state
    public new void Reset()
    {
        messages = new string[maxCapacity];
        for (int i = 0; i < baseMessageCount; i++)
        {
            messages[i] = baseMessages[i];
        }
        
        messageCount = baseMessageCount;
        
        try
        {
            using (FileStream fileStream = new FileStream(filePath, FileMode.Truncate, FileAccess.Write))
            {

            }
            WriteMsgFromFile();
        }
        
        catch (IOException e)
        {
            Console.WriteLine("Error in Reset!: " + e.Message);
        }
    }
    
    // PostCondition: Returns a deep copy of the DurableStream, including file state
    public override DurableStream DeepCopy()
    {
        DurableStream copy = new DurableStream(operationLimit, filePath);
        
        for (int i = 0; i < baseMessageCount; i++)
        {
            copy.baseMessages[i] = baseMessages[i];
        }
        
        for (int i = 0; i < baseFileCount; i++)
        {
            copy.baseFile[i] = baseFile[i];
        }
        
        for (int i = 0; i < messageCount; i++)
        {
            copy.messages[i] = messages[i];
        }
        
        copy.baseMessageCount = baseMessageCount;
        copy.baseFileCount =  baseFileCount;
        copy.fileClosed = fileClosed;
        
        return copy;
    }
}

// Implementation Invariant:
// - Append operations need not immediately trigger a write, except every 4th message).