// Author: Ayimen H.
// Date: Nov 11, 2024
// Revision: 0th Revision

#ifndef DURABLESTREAM_H
#define DURABLESTREAM_H
#include "MsgStream.h"

using namespace std;

#include <iostream>
#include <fstream>
#include <string>

class DurableStream : public MsgStream
{
    private:
        unique_ptr<string[]> baseMessages;
        int baseMessageCount;

        unique_ptr<string[]> baseFile;
        int baseFileCount;

        string filePath;
        bool fileClosed = false;

    public:
        DurableStream(int operationLimit, const string& filePath);

        void AppendMessage(const string& message) override;
        void LoadMsgFromFile();

        void WriteMsgToFile();
        void WriteMsgFromFile();

        void  Reset() override;
};

#endif
