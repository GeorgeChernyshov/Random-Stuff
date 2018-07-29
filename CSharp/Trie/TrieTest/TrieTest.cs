using System;
using System.Collections.Generic;
using System.IO;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using TrieNS;

namespace TrieTest
{
    [TestClass]
    public class TrieTest
    {
        private List<string> sample = new List<string> { "A", "to", "tea", "ted", "ten", "i", "in", "inn" };

        [TestMethod]
        public void ExceptionTest1()
        {
            string fileName = "exception.test";
            using (BinaryWriter writer = new BinaryWriter(File.Open(fileName, FileMode.Create)))
            {
                writer.Write("1111111");
            }
            Trie trie = new Trie();
            using (BinaryReader reader = new BinaryReader(File.Open(fileName, FileMode.Open)))
                trie.Deserialize(reader);
        }

        [TestMethod]
        public void AddTest()
        {
            Trie trie = new Trie();
            trie.Add("Hello");
        }

        [TestMethod]
        public void AddContainsTest()
        {
            Trie trie = new Trie();
            trie.Add("Hello");
            Assert.IsTrue(trie.Contains("Hello"));
            trie.Add("Goodbye");
            Assert.IsTrue(trie.Contains("Goodbye"));
        }

        [TestMethod]
        public void ContainsEmptyTest()
        {
            Trie trie = new Trie();
            Assert.IsFalse(trie.Contains("Anything"));
        }

        [TestMethod]
        public void ContainsEmptyStringTest()
        {
            Trie trie = new Trie();
            Assert.IsFalse(trie.Contains(""));
        }

        [TestMethod]
        public void AddNotContainsTest()
        {
            Trie trie = new Trie();
            trie.Add("Hello");
            Assert.IsFalse(trie.Contains("Goodbye"));
        }

        [TestMethod]
        public void RemoveContainsTest()
        {
            Trie trie = new Trie();
            trie.Add("Hello");
            trie.Add("Goodbye");
            trie.Remove("Hello");
            Assert.IsTrue(trie.Contains("Goodbye"));
        }

        [TestMethod]
        public void RemoveNotContainsTest()
        {
            Trie trie = new Trie();
            trie.Add("Hello");
            trie.Add("Goodbye");
            trie.Remove("Goodbye");
            Assert.IsFalse(trie.Contains("Goodbye"));
        }

        [TestMethod]
        public void RemoveFromEmptyTest()
        {
            Trie trie = new Trie();
            Assert.IsFalse(trie.Remove("Hello"));
            Assert.AreEqual(0, trie.Size());
        }

        [TestMethod]
        public void RemoveEmptyStringFromEmptyTest()
        {
            Trie trie = new Trie();
            Assert.IsFalse(trie.Remove(""));
            Assert.AreEqual(0, trie.Size());
        }

        [TestMethod]
        public void AddNotRemoveTest()
        {
            Trie trie = new Trie();
            trie.Add("Goodbye");
            Assert.IsFalse(trie.Remove("Hello"));
            Assert.AreEqual(1, trie.Size());
        }

        [TestMethod]
        public void AddOneTwoTimesTest()
        {
            Trie trie = new Trie();
            Assert.IsTrue(trie.Add("Hello"));
            Assert.IsFalse(trie.Add("Hello"));
            Assert.AreEqual(1, trie.Size());
        }

        [TestMethod]
        public void SampleTest()
        {
            Trie trie = new Trie();
            foreach(string str in sample)
            {
                trie.Add(str);
            }
            foreach(string str in sample)
            {
                Assert.IsTrue(trie.Contains(str));
            }
            Assert.AreEqual(8, trie.Size());
        }

        [TestMethod]
        public void StartsWithPrefixEmptyTest()
        {
            Trie trie = new Trie();
            Assert.AreEqual(0, trie.StartsWithPrefix("Hello"));
        }

        [TestMethod]
        public void StartsWithPrefixEmptyStringTest()
        {
            Trie trie = new Trie();
            foreach (string str in sample)
            {
                trie.Add(str);
            }
            Assert.AreEqual(trie.Size(), trie.StartsWithPrefix(""));
        }

        [TestMethod]
        public void StartsWithPrefixOneTest()
        {
            Trie trie = new Trie();
            trie.Add("Hell");
            Assert.AreEqual(1, trie.StartsWithPrefix("H"));
            Assert.AreEqual(1, trie.StartsWithPrefix("He"));
            Assert.AreEqual(1, trie.StartsWithPrefix("Hel"));
            Assert.AreEqual(1, trie.StartsWithPrefix("Hell"));
            Assert.AreEqual(0, trie.StartsWithPrefix("Hello"));
        }

        [TestMethod]
        public void StartsWithPrefixSampleTest()
        {
            Trie trie = new Trie();
            foreach (string str in sample)
            {
                trie.Add(str);
            }
            Assert.AreEqual(1, trie.StartsWithPrefix("A"));
            Assert.AreEqual(4, trie.StartsWithPrefix("t"));
            Assert.AreEqual(1, trie.StartsWithPrefix("to"));
            Assert.AreEqual(3, trie.StartsWithPrefix("te"));
            Assert.AreEqual(3, trie.StartsWithPrefix("i"));
            Assert.AreEqual(2, trie.StartsWithPrefix("in"));
            Assert.AreEqual(1, trie.StartsWithPrefix("inn"));
        }

        [TestMethod]
        public void SerializationEmptyTest()
        {
            string fileName = "serializationempty.test";
            Trie trie = new Trie();
            using (BinaryWriter writer = new BinaryWriter(File.Open(fileName, FileMode.Create)))
                trie.Serialize(writer);
            Trie deserialized = new Trie();
            using (BinaryReader reader = new BinaryReader(File.Open(fileName, FileMode.Open)))
                deserialized.Deserialize(reader);
            Assert.AreEqual(0, deserialized.Size());
        }
        [TestMethod]
        public void SerializationSampleTest()
        {
            string fileName = "serializationsample.test";
            Trie trie = new Trie();
            foreach(string str in sample)
            {
                trie.Add(str);
            }
            using (BinaryWriter writer = new BinaryWriter(File.Open(fileName, FileMode.Create)))
                trie.Serialize(writer);
            Trie deserialized = new Trie();
            using (BinaryReader reader = new BinaryReader(File.Open(fileName, FileMode.Open)))
                deserialized.Deserialize(reader);
            Assert.AreEqual(trie.Size(), deserialized.Size());
            foreach (string str in sample)
            {
                Assert.IsTrue(trie.Contains(str));
            }
        }
    }
}
