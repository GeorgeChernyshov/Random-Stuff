using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TrieNS
{
    /*  Класс, реализующий бор.
     *  Структура хранит строки.
     *  Функции:
     *  Add - добавление строки, если такой нет
     *  Remove - удаление строки, если таковая имеется
     *  Contains - проверка наличия строки в боре
     *  StartsWithPrefix - количество строк, начинающихся с префикса
     */
    public class Trie
    {
        private Node head = new Node();


        /*  Функция, проверяющая наличие строки
         *  @params str строка, наличие которой проверяется
         *  @returns true если она есть, иначе false
         */
        public bool Contains(string str)
        {
            Node node = head;
            foreach(char ch in str)
            {
                if (node.Children.ContainsKey(ch))
                {
                    node = node.Children[ch];
                }
                else
                {
                    return false;
                }
            }
            return node.isLast;
        }

        /*  Функция, добавляющая в бор строку, если такой нет
         *  @params str строка, которую нужно добавить
         *  @returns true, если строка была добавлена
         *  false если строка уже была в боре
         */
        public bool Add(string str)
        {
            if (Contains(str))
                return false;

            Node node = head;
            foreach (char ch in str)
            {
                node.ChildrenCount++;
                if (node.Children.ContainsKey(ch))
                {
                    node = node.Children[ch];
                }
                else
                {
                    Node newNode = new Node();
                    node.Children.Add(ch, newNode);
                    node = newNode;
                }
            }
            node.isLast = true;
            return true;
        }

        /*  Функция удаления строки из бора, если таковая имеется
         *  @params str строка, которую необходимо удалить
         *  @returns true если строка была удалена
         *  false если строка не содержалась в боре
         */
        public bool Remove(string str)
        {
            if (!Contains(str))
                return false;

            Node node = head;
            foreach (char ch in str)
            {
                node.ChildrenCount--;
                if (node.Children.ContainsKey(ch))
                {
                    node = node.Children[ch];
                }
            }
            if(node.ChildrenCount > 0)
            {
                node.isLast = false;
            }
            else
            {
                node = head;
                foreach (char ch in str)
                {
                    if (node.ChildrenCount == 0 && !node.isLast)
                    { 
                        node.Children.Remove(ch);
                        break;
                    } else
                    {
                        node = node.Children[ch];
                    }
                }
            }
            return true;
        }

        //Функция, возвращающая размер бора
        public int Size() => head.ChildrenCount;

        /*  Функция, возвращающая количество строк, начинающихся
         *  с заданного префикса
         *  @params prefix заданный префикс
         *  @returns int количество строк
         */
        public int StartsWithPrefix(string prefix)
        {
            Node node = head;
            foreach (char ch in prefix)
            {
                if (node.Children.ContainsKey(ch))
                {
                    node = node.Children[ch];
                }
                else
                {
                    return 0;
                }
            }
            return node.ChildrenCount + (node.isLast ? 1 : 0);
        }

        public void Serialize(BinaryWriter writer)
        {
            head.Serialize(writer);
        }

        public void Deserialize(BinaryReader reader)
        {
            head.Deserialize(reader);
        }

        private class Node
        {
            public int ChildrenCount = 0;
            public bool isLast = false;
            public Dictionary<char, Node> Children = new Dictionary<char, Node>();

            public void Serialize(BinaryWriter writer)
            {
                writer.Write(isLast);
                writer.Write(ChildrenCount);
                writer.Write(Children.Count);
                foreach(char ch in Children.Keys)
                {
                    Children[ch].Serialize(writer);
                }
            }

            public void Deserialize(BinaryReader reader)
            {
                try 
                {
                    isLast = reader.ReadBoolean();
                    ChildrenCount = reader.ReadInt32();
                    int ChildrenSize = reader.ReadInt32();
                    for(int i = 0; i < ChildrenSize; ++i)
                    {
                        Node node = new Node();
                        node.Deserialize(reader);
                    }
                }
                catch(EndOfStreamException)
                {
                    Console.WriteLine("Incorrect input file, deserialization is impossible");
                }
            }
        }
    }
}
