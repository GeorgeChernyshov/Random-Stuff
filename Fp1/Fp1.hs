head' :: [a] -> a
head' (xs:_) = xs

tail' :: [a] -> [a]
tail' [] = []
tail' (_:xs) = xs

take' :: Int -> [a] -> [a]
take' 0 x = []
take' a (x:xs) = (x:take' (a-1) xs)
                         

drop' :: Int -> [a] -> [a]
drop' 0 x = x
drop' a [] = []
drop' a (x:xs) = (drop' (a-1) xs)

filter' :: (a -> Bool) -> [a] -> [a]
filter' f [] = []
filter' f (x:xs) = if f x == True
                      then (x:filter' f xs)
                      else (filter' f xs)  

foldl' :: (a -> b -> a) -> a -> [b] -> a
foldl' f z [] = z
foldl' f z (x:xs) = foldl' f (f z x) xs

concat' :: [a] -> [a] -> [a]
concat' x [] = x
concat' [] (y:ys) = (y:ys)
concat' (x:xs) y = (x:concat' xs y)

quickSort' :: Ord a => [a] -> [a]
quickSort' [] = []
quickSort' (x:xs) = 
    let sSort = quickSort'(filter' (<=x) xs) 
        rSort = quickSort'(filter' (>x) xs)
    in concat' sSort (x:rSort)
