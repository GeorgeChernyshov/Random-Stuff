using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MySortedVector
{
    public class SortedVectorEventArgs<T> : EventArgs
    {
        public string _collectionName = "SortedVector";
        public string _actionType;
        public T _changedObject;

        public SortedVectorEventArgs(string actionType, T added)
        { 
            _actionType = actionType;
            _changedObject = added;
        }
    }
}
