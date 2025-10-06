// Author: Ayimen H.
// Date: Oct 12, 2024
// Revision: 0

#ifndef MSGSTREAM_H
#define MSGSTREAM_H

using namespace std;

#include <string>
#include <array>
#include <ctime>
#include <stdexcept>

    class MsgStream {
        private:
            static const int OperationLimit = 16;
            static const int MaxCapacity = 64;
            string* messages;
            int messageCount = 0;

            int maxCapacity = 0;

            int operationLimit = 0;
            int operationCount = 0;

            void IsOperationAllowed();

        public:
            MsgStream(int operationLimit = OperationLimit);

            // PostCondition: A message is appended to the stream
            void AppendMessage(const string& message);
            // PreCondition: The stream must not be empty
            string* ReadMessages(int startingMessage, int endingMessage);

            void Reset();
            int QueryMaxCapacity();

            MsgStream(const MsgStream& src);
            MsgStream& operator=(const MsgStream& src);

            MsgStream(MsgStream&& src) noexcept;
            MsgStream& operator=(MsgStream&& src) noexcept;

            int QueryCurrentMessageCount();
    };

#endif //MSGSTREAM_H
