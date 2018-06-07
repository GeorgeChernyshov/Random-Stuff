using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MySortedVector
{
    [Serializable]
    class AddDeleteJournal<T>
    {
        [Serializable]
        public struct AddDeleteNode<T>
        {
            public string collectionName;
            public string actionType;
            public T changedObject;
        }

        private List<AddDeleteNode<T>> journal = new List<AddDeleteNode<T>>();

        public void AddEntry(SortedVectorEventArgs<T> e)
        {
            AddDeleteNode<T> node;
            node.collectionName = e._collectionName;
            node.actionType = e._actionType;
            node.changedObject = e._changedObject;
            journal.Add(node);
        }

        public void Print()
        {
            int id = 0;
            foreach(var node in journal)
            {
                Console.WriteLine("ID: {0}, Collection name: {1}, Action type: {2}, Changed Object: {3}",
                    id++, node.collectionName, node.actionType, node.changedObject);
            }
        }
    }
}
