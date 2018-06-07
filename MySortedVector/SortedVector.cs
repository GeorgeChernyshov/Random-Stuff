using System;
using System.Collections.Generic;
using System.Text;

namespace MySortedVector
{
    public interface ISortedVector<T>
    {
        void Add(IComparable<T> item);
        void Remove(int index);
        T GetElement(int index);
        int IndexOf(IComparable<T> item);
    }

    [Serializable()]
    class SortedVector<T> : ISortedVector<T>
    {

        private int _size = 0;
        private int _capacity = 10;
        private T[] _array;

        private event EventHandler<SortedVectorEventArgs<T>> AddDeleteEvent;
        public event EventHandler<SortedVectorEventArgs<T>> SortedVectorEvent
        {
            add
            {
                AddDeleteEvent += value;
                SubscriptionJournal.SubscriptionNode node = new SubscriptionJournal.SubscriptionNode("Sorted Vector", "subscribed");
                SubscriptionJournal.AddEntry(node);
            }
            remove
            {
                AddDeleteEvent -= value;
                SubscriptionJournal.SubscriptionNode node = new SubscriptionJournal.SubscriptionNode("Sorted Vector", "unsubscribed");
                SubscriptionJournal.AddEntry(node);
            }
        }

        public AddDeleteJournal<T> addDeleteJournal = new AddDeleteJournal<T>();

        private void HandleAddition(object sender, SortedVectorEventArgs<T> e) => addDeleteJournal.AddEntry(e);

        public SortedVector()
        {
            _array = new T[_capacity];
        }

        public SortedVector(int size)
        {
            _size = size;
            _capacity = (2 * size) + 1;
            _array = new T[_capacity];
        }

        public void Add(IComparable<T> item)
        {
            EventHandler<SortedVectorEventArgs<T>> handler = AddDeleteEvent;
            SortedVectorEventArgs<T> e = new SortedVectorEventArgs<T>("Add", (T)item);
            handler?.Invoke(this, e);

            for (int index = 0; index < _size; index++)
            {
                if (item.CompareTo(_array[index]) < 0)
                {
                    T temp = _array[index];
                    _array[index] = (T)item;
                    item = (IComparable<T>)temp;
                }
            }
            _array[_size++] = (T)item;
            if (_size == _capacity)
                Resize();
        }


        private void Resize()
        {
            _capacity *= 2;
            T[] newArray = new T[_capacity];
            for (int index = 0; index < _size; index++)
            {
                newArray[index] = _array[index];
            }
            _array = newArray;
        }


        public void Remove(int index)
        {
            if (index < 0 || index >= _size)
            {
                Console.WriteLine("Incorrect index");
                return;
            }

            T item = _array[index];
            EventHandler<SortedVectorEventArgs<T>> handler = AddDeleteEvent;
            SortedVectorEventArgs<T> e = new SortedVectorEventArgs<T>("Remove", (T)item);
            handler?.Invoke(this, e);

            for (int i = index; i < _size - 1; i++)
            {
                _array[i] = _array[i + 1];
            }
            _size--;
        }


        public T GetElement(int index)
        {
            if (index < 0 || index >= _size)
            {
                Console.WriteLine("Incorrect index");
                return default(T);
            }
            return _array[index];
        }


        public int IndexOf(IComparable<T> item)
        {
            int index = 0;
            while (index < _size)
            {
                if (item.CompareTo(_array[index]) == 0)
                {
                    return index;
                }
                if (item.CompareTo(_array[index]) == -1)
                {
                    return -1;
                }
                index++;
            }
            return -1;
        }

        public void Subscribe() => SortedVectorEvent += HandleAddition;

        public void Unsubscribe() => SortedVectorEvent -= HandleAddition;

        public void Print() => addDeleteJournal.Print();     
    }
}
