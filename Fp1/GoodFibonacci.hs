fibonacci :: Integer -> Integer
fibonacci n | n >= 0 = helper 1 1 n
            | n < 0 = helper 1 (-1) n

helper :: Integer -> Integer -> Integer -> Integer
helper prev1 prev2 total | total == 0 = 0
                         | (total == 1 || total == -1) = prev1
                         | (total == 2 || total == -2) = prev2
                         | total > 0 = helper prev2 (prev1 + prev2) (total - 1)
                         | otherwise = helper prev2 (prev1 - prev2) (total + 1)
