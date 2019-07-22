module EnumOdd where

instance Enum Odd where
	succ (Odd x) = Odd (x + 2)
	pred (Odd x) = Odd (x - 2)
	toEnum x = Odd ((2 * toInteger x) + 1)
	fromEnum (Odd x) = fromInteger (div (x - 1) 2)
	enumFrom x = x : enumFrom (succ x)
	enumFromTo (Odd x) (Odd y) | x > y = []
	               | otherwise = (Odd x) : enumFromTo (succ (Odd x)) (Odd y)
	enumFromThen (Odd x) (Odd y) = (Odd x) : enumFromThen (Odd y) (Odd (x - 2 * (x - y)))
	enumFromThenTo (Odd x) (Odd y) (Odd z) | x < y && x > z = []
	                                       | x > y && x < z = []
	                                       | otherwise = (Odd x) : enumFromThenTo (Odd y) (Odd (x - 2 * (x - y))) (Odd z)
