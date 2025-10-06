// Author: Ayimen H.
// Date: Nov 11, 2024
// Revision: 0th Revision

#ifndef MSGSTREAM_H
#define MSGSTREAM_H
#include <string>
#include <stdexcept>
#include <memory>

using namespace std;

class MsgStream
{
protected:
    int OperationLimit = 16;
    int MaxCapacity = 64;
    static int instanceCounter;

    string* messages;
    int messageCount;

    int maxCapacity;
    int operationLimit;
    int operationCount;

    void IsOperationAllowed();

public:
    MsgStream(int operationLimit);
    MsgStream();

    void virtual AppendMessage(const string& message);
    string* ReadMessages(int startingMessage, int endingMessage);

    MsgStream(const MsgStream& src);
    MsgStream& operator=(const MsgStream& src);

    MsgStream(MsgStream&& src) noexcept;
    MsgStream& operator=(MsgStream&& src) noexcept;

    virtual void Reset();

    int QueryMaxCapacity() const;
    int QueryCurrentMessageCount() const;

    MsgStream operator+(const MsgStream& other) const;
    MsgStream& operator+=(const MsgStream& other);

    MsgStream operator-(const MsgStream& other) const;
    MsgStream& operator-=(const MsgStream& other);

    bool operator==(const MsgStream& other) const;
    bool operator!=(const MsgStream& other) const;
};



#endif
