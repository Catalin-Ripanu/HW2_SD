# The Implementation of the Assignment

The assignment was completed in 2 weeks and 4 days.

The implementation ideas came to me successively.

## Week 1
- In the first week, I created the necessary structures, processing functions, and writing functions.
- I used `while(fgets(..))` to obtain the data from the input file.
- Also, in the first week, I solved Problem 1 from the assignment. Of course, there were many errors reported by `valgrind` within the add function.
- I spent 3-4 days to create that algorithm to see/count certain positions using counters.

## Week 2
- In the second week, I performed Problem 2 with the help of the `Prelucrare_Arbore_TF` function. I used a part of the add function.
- This week presented the most obstacles (SIGSEGV->GDB).
- Another 2-3 days of this week were needed for debugging, of course.
- I used `valgrind` and `GDB`. `valgrind` reported the most errors.
- It is interesting that I had to use a triple pointer to properly free the memory (there could have been a simpler way).
- I also used a stack to save the nodes.
- The information stored by a node in the stack is, in fact, the information stored by a node in the tree (the 'data' field is preceded by `GenericTree*`).

The main idea of the program conceived in the first 2 weeks:
```
We start with O in the input file -> X moves.
             X O X
             O X X
             O X O
            ^
           /
      X O X
      O X X
      O X -
      ^
     /
- O X
O X X
O X -
     \
      v
       - O X
       O X X
       O X X
```

I represented the entire game:
```
                        Initial_State
                        /             \
                       v               v
                Stare1_Level1          Stare2_Level1
                                                    \
                                                     v
                                                     Stare1_Level2
```

These states represent nodes, and the game boards were stored using a `char**` field.

The meanings of the following fields:
- `character`: the character that needs to be placed ('X'/'O' or 'T'/'F')
- `edge`: the number of edges.
- `val`: the numeric value stored in the node.
- `Next_Node`: move to another node.
- Example: `Initial_State->Next_Node[1]` represents `Stare2_Level1`.
- To access the game board: `Stare2_Level1->Next_Node[1]->gametable`.
- `Stare1_Level2->Next_Node[1]` is `NULL`.
- As I said, many errors in this part of the program.

## Remaining 4 Days
- I completed the assignment after another 4 days.
- The experience gained in the second week saved me from other errors, of course.
- In these 4 days, I finished Problem 3.
- I searched for more information about the minimax algorithm in Lab 06 of Algorithms Programming.
- The implementation was simple, I found the max/min values at each function call.
- The main part of this solution is in the `main` function.
- I used `strtok` to traverse sequences in the form `'(num1) (num2) [num3]..'` because the numeric values (`num1`, `num2`, `num3`, etc.) were needed.
- I used a variable `Tree_Build` to build the tree.
- The `Tree_Aux` variable has the role of forming the edges if the parenthesis in the sequence is round, and of storing the numeric values in the nodes if the parenthesis is square.
- Again, many problems with `valgrind` in this part.
- I spent 3/4 days here.
- The writing functions were simple, I used `/t` to respect the indentation.
- I also used these `char*` variables (`sir1`, `sir2`, `sir3`), `int` (counters `14`, `17`, `2`, etc.), `Tree_Aux_Free1`/`Tree_Aux_Free2` to free all the memory.

In conclusion, this assignment was not trivial either.