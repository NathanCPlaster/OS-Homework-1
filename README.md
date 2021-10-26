# ReadMe


---

#### Technologies

- Linux Ubuntu
- VsCode

---


#### Prerequisites
- gcc and pthread library
- Compile on Ubuntu/Linux
- C/C++ Extension

## How To Use
After cloning the repository and ensuring you have met the prerequisites
run these commands in order:
```html
    gcc producer.c -pthread -lrt -o producer
    gcc consumer.c -pthread -lrt -o consumer
    ./consumer & ./producer &
```
it is VERY IMPORTANT you run the last command as stated.

## Expected Output
```
[] ####
[] ####
test@test-VB:~/Location/Project$
Producer Ready to create 5 items.
Item produced, there are now 1 item(s) in the table.
Item produced, there are now 2 item(s) in the table.
Item consumed, 1 remaining.
Item consumed, 0 remaining.
Item produced, there are now 1 item(s) in the table.
Item consumed, 0 remaining.
Item produced, there are now 1 item(s) in the table.
Item consumed, 0 remaining.
Item produced, there are now 1 item(s) in the table.
Producer cleaned up!
Item consumed, 0 remaining.
Consumer went home!
```

## References
---
This is a list of online material and provided material I used to analyze and or edit my code with.

- Synchronization Lab  : http://www.cse.cuhk.edu.hk/~ericlo/teaching/os/lab/7-IPC2/index.html

- Linux Manual Pages for SEM Command Descriptions : https://man7.org/linux/man-pages/index.html

- Additional material provided to the class by Professor Guan, Qiang at Kent State University
