Perfect Numbers
---------------

> Q1. Roughly how long did it take your computer to do the search? How many perfect numbers were found and what were they?

A1. 运行时间大约3s；找到了4个，分别为：6、28、496、8128

> Q2. Record the timing results for `findPerfects` that you observed into a table.

A2.  STUDENT_TEST执行时间表格如下：

| Size   | Time(s) |
| ------ | ------- |
| 20000  | 0.867   |
| 40000  | 2.935   |
| 80000  | 11.199  |
| 160000 | 44.087  |

> Q3. Does it take the same amount of work to compute `isPerfect` on the number 10 as it does on the number 1000? Why or why not? Does it take the same amount of work for `findPerfects` to search the range of numbers from 1-1000 as it does to search the numbers from 1000-2000? Why or why not?

A3.
1.`isPerfect`调用了 `divisorSum`，而 `divisorSum`的时间复杂度是$O(n)$，因此对于10和1000，搜索的范围不一样，做的工作不一样多。
2.对于搜索范围为 1-1000 的数，`findPerfect`其工作量是否与 1000-2000 时不一样多，函数的复杂度近为$O(n^2)$，显然$O(\sum_{i=1000}^{2000} i^2)>>O(\sum_{i=1}^{1000} i^2)$

> Q4. Extrapolate from the data you gathered and make a prediction: how long will it take `findPerfects` to reach the fifth perfect number?

A4. 通过之前的数据推测大概是数据翻倍，搜索时间增长四倍，经过粗略计算，大概推断找到第五个数 `findPerfects`大约需要十几天。

> Q5. Do any of the tests still pass even with this broken function? Why or why not?

A5. 其他测试中有些测试依旧可以通过，有些测试不能通过。通过的测试函数有的并没有调用这个函数，不会受到影响；有一个测试用例调用了这个函数但是由于本身样例就是不是完全数，改了函数之后依旧满足不是完全数，因此也通过了测试。

Q6. Describe the testing strategy you used for your test cases to confirm `smarterSum` is working correctly.

A6.测试值为1，6，25；1是边界值，6是完全数，25是平方数。

> Q7. Record your timing results for `findPerfectsSmarter` into a table.

A7. STUDENT_TEST执行时间表格如下：

| Size    | Time(s) |
| ------- | ------- |
| 600000  | 2.974   |
| 1200000 | 7.445   |
| 2400000 | 19.235  |
| 4800000 | 51.764  |

> Q8. Make a prediction: how long will `findPerfectsSmarter` take to reach the fifth perfect number?

A8. 经过粗略计算，大概推断找到第五个数 `findPerfects`大约需要十几分钟。

> Q9. Explain how you chose your specific test cases and why they lead you to be confident `findNthPerfectEuclid` is working correctly.

A9. 我的测试用例是第1，2，3，5个完全数，本地电脑 `long`类型最多测试到第5个完全数，第6个完全数位数为10，`long`类型溢出。

Soundex
-------

> Q10. What is the Soundex code for "Angelou"? What is the code for your own surname?

A10. A524

> Q11. Before writing any code, brainstorm your plan of attack and sketch how you might decompose the work into smaller tasks. Briefly describe your decomposition strategy.

A11.

1. 用 `map`将表中字母对应的值关系存一下
2. 调用 `removeNonLetters` 去除非字母
3. 将字符串变成全大写，并用个变量存一下第一个字母
4. 将字母字符串转变为对应数字的字符串
5. 遍历字符串取出相邻相同字符的第一个和非零字符，注意第一个字符如果是0也要取出
6. 将第一个字符用第3步存的临时变量替换掉
7. 补全或者删除多余字符，使字符串长度为4

> Q12. Think about one or more examples of a class of names that the Soundex system might not work well for. Explain what this class of names is and why the system might incorrectly group them or mis-categorize one of the names.

A12. 无

> Q13. Suppose you are a software engineer working for the U.S. government. You have been tasked with implementing a system that collects names as part of the Census survey and analyzes these names using a phonetic algorithm. Your boss suggests using Soundex and notes that the algorithm is only expected to work for ASCII-encoded strings, since supporting Unicode would require extra work and time. What would your response be and why? What representational harms might result from building a system that exclusively uses Soundex and/or ASCII?

A13. 无
