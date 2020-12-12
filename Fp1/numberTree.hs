numberTree :: Tree () -> Tree Integer
numberTree tree =
  let nTree :: State Integer (Tree ()) -> State Integer (Tree Integer)
      nTree m = do
        s <- get
        case evalState m s of
          (Leaf _) -> do
            n <- get
            modify (+1)
            return (Leaf n)
          (Fork l _ r) -> do
            l1 <- nTree (return l)
            n <- get
            modify (+1)
            r1 <- nTree (return r)
            return (Fork l1 n r1)
  in evalState (nTree (return tree)) 1
