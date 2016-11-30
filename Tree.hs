import Prelude hiding (lookup)

data BinaryTree k v = Node k v (BinaryTree k v)(BinaryTree k v) | Nil deriving Show

lookup :: Ord k => k -> BinaryTree k v -> Maybe v
lookup _ Nil = Nothing;
lookup k2 (Node k v lt rt) | k == k2 = Just v 
                           | k2 > k = lookup k2 rt
                           | otherwise = lookup k2 lt


insert :: Ord k => k -> v -> BinaryTree k v -> BinaryTree k v
insert k1 v1 Nil = (Node k1 v1 Nil Nil)
insert k1 v1 (Node k v lt rt) | k1 == k = (Node k v1 lt rt)
                              | k1 > k = (Node k v lt (insert k1 v1 rt))
                              | otherwise = (Node k v (insert k1 v1 lt) rt)

merge :: Ord k => BinaryTree k v -> BinaryTree k v -> BinaryTree k v
merge x Nil = x
merge Nil x = x
merge (Node k v lt rt) bin = (Node k v lt (merge rt bin))

delete :: Ord k => k -> BinaryTree k v -> BinaryTree k v
delete k1 Nil = Nil
delete k1 (Node k v lt rt) | k1 == k = merge lt rt
                           | k1 > k = (Node k v lt (delete k1 rt))
                           | otherwise = (Node k v (delete k1 lt) rt) 
