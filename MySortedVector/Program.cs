using System;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization;


namespace MySortedVector
{
    class Program
    {
        static void Main(string[] args)
        {
            SortedVector<int> vector = new SortedVector<int>();
            BinaryFormatter formatter = new BinaryFormatter();
            vector.Subscribe();
            if (File.Exists("../test.txt"))
            {
                using (FileStream fs = new FileStream("../test.txt", FileMode.Open, FileAccess.Read))
                {
                    vector = (SortedVector<int>)formatter.Deserialize(fs);
                }
                Console.WriteLine();
                Console.WriteLine("Position of 1 is {0}", vector.IndexOf(1));
                Console.WriteLine("Position of 998 is {0}", vector.IndexOf(998));
                Console.WriteLine("Position of 999 is {0}", vector.IndexOf(999));
                vector.Unsubscribe();
                vector.Print();
                SubscriptionJournal.Print();
            }
            vector.Add(1);
            vector.Add(2);
            vector.Add(3);
            vector.Add(-1);
            vector.Add(0);
            vector.Add(166);
            vector.Add(1);
            vector.Add(2);
            vector.Add(10);
            vector.Add(100);
            vector.Add(1000);
            vector.Add(998);
            vector.Add(2);
            vector.Add(2);
            vector.Add(-80);
            for (int index = 0; index < 15; index++)
            {
                Console.Write(vector.GetElement(index) + " ");
            }
            Console.WriteLine();
            for (int index = 0; index < 5; index++)
            {
                vector.Remove(index);
            }
            for (int index = 0; index < 10; index++)
            {
                Console.Write(vector.GetElement(index) + " ");
            }
            Console.WriteLine();
            Console.WriteLine("Position of 1 is {0}", vector.IndexOf(1));
            Console.WriteLine("Position of 998 is {0}", vector.IndexOf(998));
            Console.WriteLine("Position of 999 is {0}", vector.IndexOf(999));
            vector.Unsubscribe();
            vector.Print();
            SubscriptionJournal.Print();
            using (FileStream fs = new FileStream("../test.txt", FileMode.OpenOrCreate, FileAccess.Write))
            {
                formatter.Serialize(fs, vector);
            }
            Console.ReadLine();
        }
    }
}
