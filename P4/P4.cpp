// Author: Ayimen H.
// Date: Nov 11, 2024
// Revision: 0th Revision

#include <iostream>
#include <memory>
#include <string>
#include "MsgStream.h"
#include "PartitionStream.h"
#include "DurableStream.h"


using namespace std;

unique_ptr<MsgStream> getObj(int i, const string& file)
{
    if (i % 2 == 0)
    {
        return make_unique<MsgStream>(16);
    }

        return make_unique<DurableStream>(16, file);
}

int main() {
    string file = "messages.txt";

    string string1 = "Hello World!";
    string string2 = "Hola Mundo!";
    string string3 = "Sekai Konnichiwa!";
    string string4 = "Sat Sri Akal, Duniya!";

    unique_ptr<MsgStream[]> heterogeneousArray = make_unique<MsgStream[]>(4);
    for (int i = 0; i < 4; i++)
    {
        unique_ptr<MsgStream> temp = getObj(i, file);
        heterogeneousArray[i] = *temp;
    }

    heterogeneousArray[0].AppendMessage(string1);
    heterogeneousArray[1].AppendMessage(string2);
    heterogeneousArray[2].AppendMessage(string3);
    heterogeneousArray[3].AppendMessage(string4);

    unique_ptr<MsgStream[]> homogeneousArray = make_unique<MsgStream[]>(4);
    for (int i = 0; i < 4; i++)
    {
        MsgStream temp(16);
        homogeneousArray[i] = temp;
    }

    homogeneousArray[0].AppendMessage(string1);
    homogeneousArray[1].AppendMessage(string2);
    homogeneousArray[2].AppendMessage(string3);
    homogeneousArray[3].AppendMessage(string4);

    PartitionStream heterogeneousPartition(heterogeneousArray, 4);
    PartitionStream homogeneousPartition(homogeneousArray, 4);

    homogeneousPartition.writeMessage(0, string2);
    homogeneousPartition.writeMessage(1, string2);

    string* homogeneousMessages = homogeneousPartition.readMessage(1, 0, 0);

    cout << "homogeneousMessages: ";
    for (int i = 0; i < 1; i++)
    {
        cout << homogeneousMessages[i] << " ";
    }

    cout << endl;
    homogeneousPartition.reset();

    heterogeneousPartition.writeMessage(1, string2);
    heterogeneousPartition.writeMessage(1, string2);
    heterogeneousPartition.writeMessage(1, string2);

    string* heterogeneousMessages = heterogeneousPartition.readMessage(1, 0, 1);

    cout << "heterogeneousMessages: ";
    for (int i = 0; i < 2; i++)
    {
        cout << heterogeneousMessages[i] << " ";
    }

    cout << endl;
    heterogeneousPartition.reset();

    // Copy & Move Semantics Test

    MsgStream originalMsgStream(16);
    originalMsgStream.AppendMessage("Original message");

    MsgStream copyMsgStream = originalMsgStream;
    copyMsgStream.AppendMessage("Another Message");

    string* oPtr = originalMsgStream.ReadMessages(0,0);
    string* cPtr = copyMsgStream.ReadMessages(0,1);

    cout << "Original messages: ";
    for (int i = 0; i < 1; i++)
    {
        cout << oPtr[i] << " ";
    }

    cout << endl;

    cout << "Copied messages: ";
    for (int i = 0; i < 2; i++)
    {
        cout << cPtr[i] << " ";
    }

    cout << endl;

    originalMsgStream.Reset();
    copyMsgStream.Reset();

    // == Overloaded Operator

    MsgStream equalMsg1(16);
    MsgStream equalMsg2(16);

    equalMsg1.AppendMessage("Message 1");
    equalMsg1.AppendMessage("Message 2");

    equalMsg2.AppendMessage("Message 1");
    equalMsg2.AppendMessage("Message 2");

    cout << "Equality operator test (equal streams): " << (equalMsg1 == equalMsg2 ? "Pass" : "Fail") << endl;

    // Test inequality operator (!=)
    MsgStream inequalMsg1(16);
    MsgStream inequalMsg2(16);

    inequalMsg1.AppendMessage("Message 1");
    inequalMsg1.AppendMessage("Message 2");

    inequalMsg2.AppendMessage("Message 1");
    inequalMsg2.AppendMessage("Different Message");

    cout << "Inequality operator test (different streams): " << (inequalMsg1 != inequalMsg2 ? "Pass" : "Fail") << endl;

    equalMsg1.Reset();
    equalMsg2.Reset();
    inequalMsg1.Reset();
    inequalMsg2.Reset();

    // + Overloaded Operator

    MsgStream addMsg1(16);
    MsgStream addMsg2(16);

    addMsg1.AppendMessage("Message 1");
    addMsg2.AppendMessage("Message 2");

    MsgStream addMsgStream = addMsg1 + addMsg2;

    string* addPtr = addMsgStream.ReadMessages(0,1);

    cout << "+ Operator: ";
    for (int i = 0; i < 2; i++)
    {
        cout << addPtr[i] << " ";
    }

    cout << endl;

    // += Overloaded Operator

    MsgStream addMsg3(16);
    addMsg3.AppendMessage("Message 3");

    MsgStream addAssignMsgStream = addMsg1 += addMsg3;

    string* addAssignPtr = addAssignMsgStream.ReadMessages(0,1);

    cout << "+= Operator: ";
    for (int i = 0; i < 2; i++)
    {
        cout << addAssignPtr[i] << " ";
    }

    cout << endl;

    addMsg1.Reset();
    addMsg2.Reset();
    addMsg3.Reset();

    // - Overloaded Operator Test
    MsgStream minusMsg1(16);
    MsgStream minusMsg2(16);

    minusMsg1.AppendMessage("Message 1");
    minusMsg1.AppendMessage("Message 2");
    minusMsg2.AppendMessage("Message 1");
    minusMsg2.AppendMessage("Message 2");

    MsgStream minusMsgStream = minusMsg1 - minusMsg2;

    string* minusPtr = minusMsgStream.ReadMessages(0, 0);

    cout << "- Operator: ";
    for (int i = 0; i < 1; i++) {
        cout << minusPtr[i] << " "; // should be empty
    }
    cout << endl;

    minusMsg1.Reset();
    minusMsg2.Reset();

    // -= Overloaded Operator Test
    MsgStream minusMsg3(16);
    minusMsg3.AppendMessage("Message 1");
    minusMsg3.AppendMessage("Message 2");
    minusMsg3.AppendMessage("Message 3");

    MsgStream minusMsg4(16);
    minusMsg4.AppendMessage("Message 2");

    MsgStream minusAssignMsgStream = minusMsg3 -= minusMsg4;

    string* minusAssignPtr = minusAssignMsgStream.ReadMessages(0, 1);

    cout << "-= Operator: ";
    for (int i = 0; i < 2; i++) {
        cout << minusAssignPtr[i] << " ";  // Should be Message 1 Message 3
    }
    cout << endl;

    minusMsg3.Reset();
    minusMsg4.Reset();

    return 0;
}