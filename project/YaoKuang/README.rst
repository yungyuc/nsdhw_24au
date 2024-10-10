==================================
**Queue for multiprocessing**
==================================

(CPython)Queue for multiprocessing.

**Basic Information**

Queue for multiprocessing, and the ref code is house in its repository: https://github.com/python/cpython/blob/main/Lib/multiprocessing/queues.py

**Problem to Solve**

Exploit the following opportunities to improve code performance:
• Resource sharing between multiple process

**Prospective Users**

It is difficult for developers to reason about the effects of individual coding decisions on the overall performance of a Module implementing queues.

**System Architecture**

Queue is an abstract data type, characterized by first in first out (FIFO, first in first out)
In high-level programming languages, it is easy to implement using arrays and linked lists.

**Schedule**

Week 1 (10/10):

Review the existing unit tests and runs. Start the presentation skeleton. Contents will be added to the presentation along with the code development.

Week 2 (10/17):

Create a universal Python constructor (or factory function) for the different fundamental element types.

Week 3 (10/24):

Make automatic conversion between Queue in Python and the Queue template in Cpython.

Week 4 (10/31): 

Refactoring week (and accommodation of overflown work).

Week 5 (11/7): 

Make a multiprocessing for the Queue.

Week 6 (11/14): 

Refactoring week (and accommodation of overflown work).

Week 7 (11/21): 

Refactoring week (and accommodation of overflown work).

Week 8 (11/28): 

Overflown work.

**References**

•	https://github.com/python/cpython/blob/main/Lib/multiprocessing/queues.py

•	Using Lists as Queues



