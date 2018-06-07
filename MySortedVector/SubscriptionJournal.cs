using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MySortedVector
{
    static class SubscriptionJournal
    {
        public struct SubscriptionNode
        {
            public string objectType;
            public string eventType;
            public DateTime eventDate;

            public SubscriptionNode(string objectType, string eventType)
            {
                this.objectType = objectType;
                this.eventType = eventType;
                this.eventDate = DateTime.Now;
            }
        }
        private static List<SubscriptionNode> journal = new List<SubscriptionNode>();

        public static void AddEntry(SubscriptionNode node)
        {
            SubscriptionNode newNode;
            newNode.objectType = node.objectType;
            newNode.eventType = node.eventType;
            newNode.eventDate = node.eventDate;
            journal.Add(node);
        }

        public static void Print()
        {
            foreach (var node in journal)
            {
                Console.WriteLine("{0}, has {1}, on {2}",
                    node.objectType, node.eventType, node.eventDate);
            }
        }
    }
}
