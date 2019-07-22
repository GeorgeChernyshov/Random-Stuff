module Perms where

perms :: [a] -> [[a]]
perms [] = [[]]
perms (x : xs) = concatMap (\y -> putFirst (head y) y) (takeOut 0 (x:xs)) where
	putFirst :: [a] -> [[a]] -> [[a]]
	putFirst x xs = map (x ++) (tail xs)

	takeOut :: Int -> [a] -> [[[a]]]
	takeOut i xs | (i + 1) == length xs =  [[xs !! i] : perms (take i xs)]
	             | otherwise = ([xs !! i] : perms (take i xs ++ drop (i + 1) xs)) : takeOut (i + 1) xs
