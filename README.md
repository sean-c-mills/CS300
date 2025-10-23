# CS300

1. What was the problem you were solving in the projects for this course?

   In the projects, I was solving the problem of organizing and retrieving course information efficiently for the academic advising team at ABC University.
   The program needed to load course data from a file, store it within a data structure, and then allow the users to display the full course list or
   search for specific courses. The challenge I had to overcome was to determine which data structure between a vector, hash table, or binary search tree
   to use and see which one offered the best balance between speed, memory usage, and scalability.

2. How did you approach the problem? Consider why data structures are important to understand.

   I approached the problem by first analyzing the different data structures and their performances. I wrote pseudocode and created a runtime analysis chart
   of all the different data structures for comparison. After testing and evaluating their advantages and disadvantages, I made the decision that the
   binary search tree was the best one for the project because it maintains data in sorted order while allowing efficient lookups and insertions.
   Understanding data structures was important because they affect how efficiently a program processes and accesses data, especially as input sizes grow.

3. How did you overcome any roadblocks you encountered while going through the activities or project?

   One of the biggest roadblocks I encountered was during the hash table activity. Implementing chaining correctly was difficult because I initially tried to access
   and modify nodes directly without using pointers, which caused issues when linking new nodes in the chain. The program either failed to insert the bids properly
   or gave incomplete output when it printed all the bids. By using error documentation, I was able to track each step of the debugging process, such as what was causing
   the issue, what I tried, and how I eventually fixed it, which helped me tremendously when overcoming the issue.

4. How has your work on this project expanded your approach to designing software and developing programs?

   Working on this project taught me how important it is to plan before you write code. By creating pseudocode and analyzing how the different data structures worked,
   I learned to think through the logic of the program before creating it. I also now see how choosing the right data structure early on can make a program run quicker
   and use less memory. This has helped me to understand that good software design means breaking the bigger problems into smaller and more manageable parts.

5. How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

   By working on this project I better understand the value of clean, organized code. I made sure to use consistent indentation, use better variable names that are more
   descriptive, and have modular functions for readability. I also learned to write code that is easily adapted. A good example of this is how I designed functions
   that could later support new features such as the prerequisite validation or expanded course data. 
