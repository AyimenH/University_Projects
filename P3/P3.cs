// Author: Ayimen H.
// Date: Oct 27, 2024
// Revision: 0th Revision

namespace P3;

public class P3
{
    static void Main()
    {
        string file = "messages.txt";
        string testFile = "test.txt";
        
        string string1 = "Hello World!";
        string string2 = "Hola Mundo!";
        string string3 = "Sekai Konnichiwa!";
        string string4 = "Sat Sri Akal, Duniya!";

        MsgStream[] heterogeneousArray = new MsgStream[4];
        
        for (int i = 0; i < heterogeneousArray.Length; i++)
        {
            heterogeneousArray[i] = getObj(i, file);
        }

        heterogeneousArray[0].AppendMessage(string1);
        heterogeneousArray[1].AppendMessage(string2);
        heterogeneousArray[2].AppendMessage(string3);
        heterogeneousArray[3].AppendMessage(string4);
        
        MsgStream[] homogeneousArray = new MsgStream[4];
        
        for (int i = 0; i < homogeneousArray.Length; i++)
        {
            homogeneousArray[i] = new MsgStream(10);
        }
        
        homogeneousArray[0].AppendMessage(string1);
        homogeneousArray[1].AppendMessage(string2);
        homogeneousArray[2].AppendMessage(string3);
        homogeneousArray[3].AppendMessage(string4);
        
        PartitionStream heterogeneousPartition = new PartitionStream(heterogeneousArray, 4);
        PartitionStream homogeneousPartition = new PartitionStream(homogeneousArray, 4);
        
        homogeneousPartition.WriteMessage( 0, string2);
        homogeneousPartition.WriteMessage(1, string2);
        
        Console.WriteLine(string.Join(", ", homogeneousPartition.ReadMessage(0, 0, 1)));
        
        homogeneousPartition.Reset();
        
        heterogeneousPartition.WriteMessage(1, string2);
        heterogeneousPartition.WriteMessage(1, string2);
        heterogeneousPartition.WriteMessage(1, string2);
        
        Console.WriteLine(string.Join(", ", heterogeneousPartition.ReadMessage(1, 0, 1)));
        
        heterogeneousPartition.Reset();
        
        MsgStream originalMsgStream = new MsgStream(10);
        originalMsgStream.AppendMessage("Original");
        
        MsgStream copyMsgStream = originalMsgStream.DeepCopy();
        copyMsgStream.AppendMessage("Copy");
        
        Console.WriteLine("Original count: " + originalMsgStream.QueryCurrentMessageCount());
        Console.WriteLine("Copied count: " + copyMsgStream.QueryCurrentMessageCount());
        
        DurableStream originalDurableStream = new DurableStream(10, testFile);
        originalDurableStream.AppendMessage("Original Durable");
        
        DurableStream copyDurableStream = originalDurableStream.DeepCopy();
        copyDurableStream.AppendMessage("Copied Durable");
        
        Console.WriteLine("Original count: " + originalDurableStream.QueryCurrentMessageCount());
        Console.WriteLine("Copied count: " + copyDurableStream.QueryCurrentMessageCount());
        
        PartitionStream originalPartition = new PartitionStream(homogeneousArray, 4);
        
        originalPartition.WriteMessage(0, string1);
        originalPartition.WriteMessage(0, string2);
        
        PartitionStream copyPartition = originalPartition.DeepCopy();
        
        copyPartition.WriteMessage(0,"New message");
        
        Console.WriteLine("Partition 0 Original PartitionStream message count: " +
                          originalPartition.ReadMessage(0, 0, 0).Length);
        Console.WriteLine("Partition 0 Copy PartitionStream message count: " +
                          copyPartition.ReadMessage(0, 0, 1).Length);
        
        originalDurableStream.Dispose();
        copyDurableStream.Dispose();
        
        for (int i = 0; i < heterogeneousArray.Length; i++)
        {
            MsgStream obj = heterogeneousArray[i];
            if (obj is DurableStream durableObj)
            {
                durableObj.Dispose();
            }
        }
    }

    static MsgStream getObj(int i, string file)
    {
        if (i % 2 == 0)
        {
            return new MsgStream(10);
        }
        return new DurableStream(10, file);
    }
}
