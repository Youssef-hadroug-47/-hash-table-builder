## Building My Own HashMap in C From Scratch 

- Here is my own associative array implemented as a hash map
- The Hash Function I used is the following :    
> [!NOTE]
> \sum{(p^i*(len(b)-(i+1) ))*byteCode(b\index{i})} % size
> p is a prime number 
> byteCode is the ASCII code of corresponding character 
> size if the struct capacity

- I used Double Hashing Algorithm for collision handling 
- The final Hash formula :
> [!NOTE]
> ( hash_a + (hash_b\*attemplt+1) ) % size

**Compile**
```
    make -s compile
```
**Run**
```
    make -s build
```

> [!NOTE]
> This algorithm is not the best so far. It actually abuses memory heavily. 
> Infinite loops also occur very often.  
