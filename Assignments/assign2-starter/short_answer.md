Warmup
------

> Q1. The display of the Stack in the debugger uses the labels `top` and `bottom` to mark the two ends of the stack. How are the contents labeled when the Stack contains only one element?

A1. 会显示为：`bottom/top`

> Q2. For which type of inputs does the function go into an infinite loop?

A2. 当队列中只含有负数的时候会造成函数无限循环

> Q3. Show your edited code for duplicateNegatives that fixes the problem with the infinite loop

A3. 创建一个辅助队列`result`，把值存储到`result`中过渡一下，最后`q=result`

> Q4. What is the better fix to `sumStack` that corrects the bug?

A4. 如下所示：
```cpp
int total=0;
while (!s.isEmpty()) {
    total += s.pop();
}
```

Maze
----

> 5. In lecture, Cynthia noted the convention is to pass large data structures by reference for reasons of efficiency. Why then do you think `validatePath` passes `path` by value instead of by reference?

A5. TODO

> Q6. After you have written your tests, describe your testing strategy to determine that your `validatePath` works as intended.

A6. TODO

Search Engine
-------------

> Q7. Sketch the contents of the inverted index built from the `res/tiny.txt` database file.

A7. TODO

Beyond Algorithmic Analysis
---------------------------

> Q8. In a short paragraph, describe a real or plausible scenario not previously presented in lecture in which using techniques like Big-O or Asymptotic Analysis to improve the performance of an algorithm might benefit the environment. Include your thoughts on how a software engineer working on this piece of code might identify such potential benefits and take them into consideration when designing the code.

A8. TODO

> Q9. According to the contract that IBM struck with the state of Indiana, the criteria for optimization were improving efficiency of the overall welfare system and reducing fraud. Criteria for reducing wait times and wrongful denials were not included.  However, wrongfully denying benefits has a huge negative  impact on the citizens who rely on the system.  If criteria like minimizing wrongful denials were not included in the contract, should engineers have included them in their optimization algorithm?  Why or why not?

A9. TODO

> Q10. Imagine that after completing CS106B you are hired at IBM as an engineer working on this system. How might you have approached designing and setting the goals of this system?  How might you apply algorithmic analysis tools to build a system that achieved  the desired goals? Could you do so in a way that avoids the severe negative impacts on users of the system that are outlined in the case study?

A10. TODO
