# BinarySearchTreeExercises

While studying Data Structures I decided to attack Binary Trees first as I felt least adept at them.  
I made 3 unbalanced trees of unique keys. One with raw pointers, one with unique pointers and one using  
indices in a vector. I also made one balanced tree of unique key/value pairs as a red black tree using raw  
pointers. The methods in common between all versions are `custom destructors`(except for the vector version),  
`insert()`(the red black tree map also has an `operator[]()` concerning insertion) and `displayTree()`  
which is currently only set up for int keys.

The red black tree version being the most involved also contains other methods not listed in the below table. The  
table lists the current state of the project concerning some common qualities that I chose to either include or not  
as of yet amongst them. The `main.cpp` files are just arbitrary bits of code I would play around with and modify to  
test the structures out. As time permits I will continue to update/improve this project.

| version | special members | contains() | erase() | empty() | size() | clear() | balanced | key | key, value | iterator | template |
| ------- | :-------------: | :--------: | :-----: | :-----: | :----: | :-----: | :------: | :-: | :--------: | :------: | :------: |
| Raw     |        x        |     x      |    x    |    x    |   x    |    x    |          |  x  |
| Smart   |        x        |     x      |         |         |   x    |         |          |  x  |
| Vec     |                 |     x      |    x    |    x    |   x    |    x    |          |  x  |            |          |    x     |
| RBT     |        x        |     x      |    x    |    x    |   x    |    x    |    x     |     |     x      |    x     |    x     |
