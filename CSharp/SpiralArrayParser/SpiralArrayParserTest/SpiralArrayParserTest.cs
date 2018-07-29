using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using SpiralArrayParser;

namespace SpiralArrayParserTest
{
    [TestClass]
    public class SpiralArrayParserTest
    {
        [TestMethod]
        public void printSpirally3By3()
        {
            int[][] array = {
                new int[]{0,1,2},
                new int[]{3,4,5},
                new int[]{6,7,8}
            };
            int[] expected = { 4, 1, 0, 3, 6, 7, 8, 5, 2 };
            int[] actual = Parser.PrintSpirally(array);
            CollectionAssert.AreEqual(expected, actual);
        }
        [TestMethod]
        public void printSpirally4By4()
        {
            int[][] array = {
                new int[]{0, 1, 2, 3},
                new int[]{4, 5, 6, 7},
                new int[]{8, 9, 10,11},
                new int[]{12,13,14,15}
            };
            int[] expected = { 10, 6, 5, 9, 13, 14, 15, 11, 7, 3, 2, 1, 0, 4, 8, 12 };
            int[] actual = Parser.PrintSpirally(array);
            CollectionAssert.AreEqual(expected, actual);
        }
        [TestMethod]
        public void ColumnSort1()
        {
            int[][] array = {
                new int[]{3, 1, 2},
                new int[]{0, 0, 0},
            };
            int[][] expected = {
                new int[]{1, 2, 3},
                new int[]{0, 0, 0},
            };
            int[][] actual = Parser.SortColumns(array);
            for(int i = 0; i < actual.Length; ++i)
                CollectionAssert.AreEqual(expected[i], actual[i]);
        }
        [TestMethod]
        public void ColumnSort2()
        {
            int[][] array = {
                new int[]{3, 1, 2},
                new int[]{1, 2, 3},
                new int[]{4, 5, 6},
                new int[]{7, 8, 9}
            };
            int[][] expected = {
                new int[]{1, 2, 3},
                new int[]{2, 3, 1},
                new int[]{5, 6, 4},
                new int[]{8, 9, 7}
            };
            int[][] actual = Parser.SortColumns(array);
            for (int i = 0; i < actual.Length; ++i)
                CollectionAssert.AreEqual(expected[i], actual[i]);
        }
    }
}
