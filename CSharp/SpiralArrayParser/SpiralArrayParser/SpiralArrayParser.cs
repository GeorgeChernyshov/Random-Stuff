using System;
using System.Collections;
using System.Collections.Generic;


/*  Класс, реализующий две функции:
 *  PrintSpirally - функция, печатающая двумерный массив 
 *  SortColumns - функция, сортирующая столбцы двумерного 
 *  массива по первому элементу
 */
namespace SpiralArrayParser
{
    delegate void RefAction(ref int x, ref int y);
    public class Parser
    {
        private static int[] spiralArray;
        private static int spiralArrayIndex = 0;

        private static Dictionary<string, RefAction> takeStep =
            new Dictionary<string, RefAction>
            {
                { "Up",    (ref int x, ref int y) => --y},
                { "Down",  (ref int x, ref int y) => ++y},
                { "Left",  (ref int x, ref int y) => --x},
                { "Right", (ref int x, ref int y) => ++x}
            };

        private class Coordinates
        {
            public Coordinates(int x, int y)
            {
                _x = x;
                _y = y;
            }
            public int _x;
            public int _y;
        }

        private static Coordinates coordinates;

        private static void Traverse(int[][] array, int length, String direction)
        {
            for (int i = 0; i < length; i++)
            {
                spiralArray[spiralArrayIndex++] = array[coordinates._y][coordinates._x];
                takeStep[direction](ref coordinates._x, ref coordinates._y);
            }
        }

        /*  Функция, траспонирующая матрицу
         *  @params array - массив, который будет транспонирован
         *  @returns int[][] - транспонированный массив
         */
        private static int[][] Transpose(int[][] array)
        {
            int[][] transposedArray = new int[array[0].Length][];
            for (int i = 0; i < array[0].Length; ++i)
            {
                transposedArray[i] = new int[array.Length];
                for (int j = 0; j < array.Length; ++j)
                {
                    transposedArray[i][j] = array[j][i];
                }
            }
            return transposedArray;
        }

        private class ArrayComparator : IComparer<int[]>
        {
            int IComparer<int[]>.Compare(int[] A, int[] B)
            {
                if (A.Length * B.Length == 0)
                    return 0;
                return A[0] - B[0];
            }
        }


        /*  Функция, печатающая двумерный массив по спирали
         *  @params int[][] array массив, который необходимо напечатать
         *  @returns int[] "развернутый" массив
         */
        public static int[] PrintSpirally(int[][] array)
        {
            spiralArrayIndex = 0;
            spiralArray = new int[array.Length * array.Length];
            coordinates = new Coordinates(array.Length / 2, array.Length / 2);
            int x = array.Length / 2;
            int y = array.Length / 2;
            for (int length = 1; length < array.Length; ++length)
            {
                if ((length & 1) == 1)
                {
                    Traverse(array, length, "Up");
                    Traverse(array, length, "Left");
                }
                else
                {
                    Traverse(array, length, "Down");
                    Traverse(array, length, "Right");
                }
            }
            String str = ((array.Length & 1) == 1) ? "Up" : "Down";
            Traverse(array, array.Length, str);
            for (int index = 0; index < spiralArray.Length; ++index)
            {
                Console.Write(spiralArray[index] + " ");
            }
            Console.WriteLine();
            return spiralArray;
        }


        /*  Функция, сортирующая столбцы двумерного массива по 
         *  первому элементу.
         *  @param array - массив, который необходимо отсортировать
         *  @returns сортированный массив
         */
        public static int[][] SortColumns(int[][] array)
        {
            int[][] transposedArray = Transpose(array);
            List<int[]> toSort = new List<int[]>(transposedArray);
            toSort.Sort(new ArrayComparator());
            int index = 0;
            foreach (int[] Row in toSort)
            {
                transposedArray[index++] = Row;
            }
            return Transpose(transposedArray);
        }
    }
}
