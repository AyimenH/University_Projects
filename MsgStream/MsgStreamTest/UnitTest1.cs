using System;
using P1;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace MsgStreamTest
{
    [TestClass]
    public class MsgStreamTest
    {
        [TestMethod]
        public void CreateMsgStream()
        {
            // Arrange & Act
            MsgStream msgStream = new MsgStream(16);
            
            // Assert
            Assert.IsNotNull(msgStream);
        }

        [TestMethod]
        public void TestReadMessagesInRange()
        {
            // Arrange
            MsgStream msgStream = new MsgStream(16);
            msgStream.AppendMessage("First message");
            msgStream.AppendMessage("Second message");
            
            // Act
            string[] result = msgStream.ReadMessages(0, 1);
            
            // Assert
            Assert.AreEqual(2, result.Length);
            Assert.AreEqual("First message", result[0]);
            Assert.AreEqual("Second message", result[1]);
        }

        [TestMethod]
        public void TestReadMessagesInvalidRange()
        {
            // Arrange
            MsgStream msgStream = new MsgStream(16);
            msgStream.AppendMessage("First message");
            msgStream.AppendMessage("Second message");

            // Assert
            Assert.ThrowsException<ArgumentOutOfRangeException>(() =>
            {
                // Act
                msgStream.ReadMessages(1, 0);
            });
        }

        [TestMethod]
        public void TestAppendMessageExceedMaxCapacity()
        {
            // Arrange
            MsgStream msgStream = new MsgStream(16);
            int maxCapacity = msgStream.QueryMaxCapacity();
            
            // Act
            for (int i = 0; i < maxCapacity; i++)
            {
                msgStream.AppendMessage("This is a message!");
            }

            // Assert
            Assert.ThrowsException<InvalidOperationException>(() =>
            {
                msgStream.AppendMessage("This should not be added!");
            });
        }

        [TestMethod]
        public void TestOperationLimitExceeded()
        {
            // Arrange
            MsgStream msgStream = new MsgStream(1);
            msgStream.AppendMessage("Message 1");
            msgStream.AppendMessage("Message 2");

            // Act
            string[] result = msgStream.ReadMessages(0, 1);

            // Assert
            Assert.AreEqual(2, result.Length);
            Assert.ThrowsException<InvalidOperationException>(() =>
            {
                msgStream.ReadMessages(0, 1);
            });
        }

        [TestMethod]
        public void TestResetThrowsException()
        {
            // Arrange
            MsgStream msgStream = new MsgStream(16);
            msgStream.AppendMessage("First message");
            msgStream.AppendMessage("Second message");
            
            // Act
            msgStream.Reset();
            
            // Assert
            Assert.ThrowsException<ArgumentOutOfRangeException>(() =>
            {
                msgStream.ReadMessages(0, 1);
            });
        }
    }
}
