// Author: Ayimen H.
// Date: Nov 11, 2024
// Revision: 0th Revision

// Class Invariant:
// baseMessageCount and messageCount must always be <= maxCapacity
// File I/O operations only occur in chunks (every 4th message) or upon reset=
// subclass of MsgStream

#include "DurableStream.h"

using namespace std;


DurableStream::DurableStream(int operationLimit, const string& filePath) : MsgStream(operationLimit)
{
    if (filePath.empty())
    {
        throw invalid_argument("filePath is invalid");
    }

    baseMessages = make_unique<string[]>(MaxCapacity);

    for (int i = 0; i < messageCount; i++)
    {
        baseMessages[i] = messages[i];
    }

    baseMessageCount = messageCount;
    baseFile = make_unique<string[]>(MaxCapacity);

    this->filePath = filePath;
    ifstream file(filePath);

    if (file.is_open())
    {
        LoadMsgFromFile();
        file.close();
    }

    else
    {
        ofstream createFile(filePath);
        if (!createFile)
        {
            throw runtime_error("Failed to create file: " + filePath);
        }

        LoadMsgFromFile();
        createFile.close();
    }
}

void DurableStream::AppendMessage(const string& message)
{
    MsgStream::AppendMessage(message);

    if (messageCount % 4 == 0 || messageCount == 0)
    {
        WriteMsgToFile();
    }
}

void DurableStream::LoadMsgFromFile() {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error opening file for reading: " << filePath << endl;
        return;
    }

    string line;
    while (getline(file, line) && messageCount < maxCapacity) {
        if(!line.empty())
        {
            messages[messageCount] = line;
            baseFile[messageCount] = line;
            messageCount++;
        }
    }
    baseFileCount = messageCount;
    file.close();
}

void DurableStream::WriteMsgToFile() {
    ofstream file(filePath, ios::app);
    if (!file.is_open()) {
        cerr << "Error opening file for appending: " << filePath << endl;
        return;
    }

    for (int i = 0; i < messageCount; i++) {
        file << messages[i] << endl;
    }

    file.close();
}

void DurableStream::WriteMsgFromFile() {
    ofstream file(filePath, ios::app);
    if (!file.is_open()) {
        cerr << "Error opening file for appending: " << filePath << endl;
        return;
    }

    for (int i = 0; i < baseFileCount; i++) {
        file << baseFile[i] << endl;
    }

    file.close();
}

void DurableStream::Reset()
{
    for (int i = 0; i < maxCapacity; ++i)
    {
        messages[i].clear();
    }

    for (int i = 0; i < baseMessageCount; i++)
    {
        messages[i] = baseMessages[i];
    }

    messageCount = baseMessageCount;

    ofstream file(filePath, ios::trunc);
    if (file.is_open())
    {
        file.close();
    }

    WriteMsgFromFile();
}

// Implementation Invariant:
// - Append operations need not immediately trigger a write, except every 4th message).
// Copy and Move Semantics Suppressed
// ^^ due to using unique ptrs, memory management not needed
// ^ also why no destructor