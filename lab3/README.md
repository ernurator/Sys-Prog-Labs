## Part 1

### Trap 1

Disassembled `trap1` function:
```
000000000000134f <trap1>:
    134f:       f3 0f 1e fa             endbr64
    1353:       55                      push   %rbp
    1354:       48 89 e5                mov    %rsp,%rbp
    1357:       89 7d ec                mov    %edi,-0x14(%rbp)
    135a:       c7 45 fc 1e 05 00 00    movl   $0x51e,-0x4(%rbp)
    1361:       8b 45 ec                mov    -0x14(%rbp),%eax
    1364:       3b 45 fc                cmp    -0x4(%rbp),%eax
    1367:       0f 9f c0                setg   %al
    136a:       0f b6 c0                movzbl %al,%eax
    136d:       5d                      pop    %rbp
    136e:       c3                      retq
    136f:       90                      nop
```

After examining the disassembled code, I've found out that the trap can be disarmed iff code is larger than `0x51e` (1310 in decimal):
```bash
ernurator@DESKTOP-T1TMEL5:/mnt/c/Users/isenb/projects/sys_prog_labs/Sys-Prog-Labs/lab3/traps$ ./trap1
Enter code to disarm the trap:
1310
💥💥💥💥 The trap blew up. Ouch. 💥💥💥💥
ernurator@DESKTOP-T1TMEL5:/mnt/c/Users/isenb/projects/sys_prog_labs/Sys-Prog-Labs/lab3/traps$ ./trap1
Enter code to disarm the trap:
1311
Trap 1 disarmed! Congratulations! 🎊
```

### Trap 2

Disassembled `trap2` function:
```
00000000000013fc <trap2>:
    13fc:       f3 0f 1e fa             endbr64
    1400:       55                      push   %rbp
    1401:       48 89 e5                mov    %rsp,%rbp
    1404:       89 7d ec                mov    %edi,-0x14(%rbp)
    1407:       89 75 e8                mov    %esi,-0x18(%rbp)
    140a:       c7 45 f8 00 00 00 00    movl   $0x0,-0x8(%rbp)
    1411:       c7 45 fc 00 00 00 00    movl   $0x0,-0x4(%rbp)
    1418:       eb 08                   jmp    1422 <trap2+0x26>
    141a:       83 45 f8 64             addl   $0x64,-0x8(%rbp)
    141e:       83 45 fc 01             addl   $0x1,-0x4(%rbp)
    1422:       83 7d fc 09             cmpl   $0x9,-0x4(%rbp)
    1426:       7e f2                   jle    141a <trap2+0x1e>
    1428:       8b 55 ec                mov    -0x14(%rbp),%edx
    142b:       8b 45 e8                mov    -0x18(%rbp),%eax
    142e:       01 c2                   add    %eax,%edx
    1430:       8b 45 f8                mov    -0x8(%rbp),%eax
    1433:       01 c0                   add    %eax,%eax
    1435:       39 c2                   cmp    %eax,%edx
    1437:       0f 94 c0                sete   %al
    143a:       0f b6 c0                movzbl %al,%eax
    143d:       5d                      pop    %rbp
    143e:       c3                      retq
    143f:       90                      nop
```

After examining the disassembled code, I've found out that the trap can be disarmed iff sum of two arguments is equal to 2000:
```bash
ernurator@DESKTOP-T1TMEL5:/mnt/c/Users/isenb/projects/sys_prog_labs/Sys-Prog-Labs/lab3/traps$ ./trap2
Enter code to disarm the trap:
1999 0
💥💥💥💥 The trap blew up. Ouch. 💥💥💥💥
ernurator@DESKTOP-T1TMEL5:/mnt/c/Users/isenb/projects/sys_prog_labs/Sys-Prog-Labs/lab3/traps$ ./trap2
Enter code to disarm the trap:
1999 1
Trap 2 disarmed! Congratulations! 🎊
ernurator@DESKTOP-T1TMEL5:/mnt/c/Users/isenb/projects/sys_prog_labs/Sys-Prog-Labs/lab3/traps$ ./trap2
Enter code to disarm the trap:
1999 2
💥💥💥💥 The trap blew up. Ouch. 💥💥💥💥
```

## Part 2

### Overflow 1

By giving an input of length 44, the constant value is changing:
```bash
ernurator@DESKTOP-T1TMEL5:/mnt/c/Users/isenb/projects/sys_prog_labs/Sys-Prog-Labs/lab3/buf$ ./buffer
My favorite number is 12 and it will always be 12 and nothing can change that
12345678901234567890123456789012345678901234
My favorite number is 0 and it will always be 0 and nothing can change that
Returned to main safe and sound
```

After changing the `exploit.c` file:
```bash
ernurator@DESKTOP-T1TMEL5:/mnt/c/Users/isenb/projects/sys_prog_labs/Sys-Prog-Labs/lab3/buf$ ./buffer < exploit1.txt
My favorite number is 12 and it will always be 12 and nothing can change that
My favorite number is 131 and it will always be 131 and nothing can change that
Returned to main safe and sound
```

### Overflow 2

I've compiled and run the program using gdb. I put a breakpoint right after `gets`, and looked onto memory values near $rsp register ($rsp is a pointer to the topmost element in the stack, buf in our case):
```
(gdb) x/24wx $rsp
0x7fffffffe490: 0x41414141      0x41414141      0x41414141      0x41414141
0x7fffffffe4a0: 0x41414141      0x41414141      0x41414141      0x41414141
0x7fffffffe4b0: 0xf7fb8f00      0x00007fff      0x004011f0      0x0000000c
0x7fffffffe4c0: 0xffffe4e0      0x00007fff      0x004011d3      0x00000000
0x7fffffffe4d0: 0xffffe5d8      0x00007fff      0x00000000      0x00000001
0x7fffffffe4e0: 0x00000000      0x00000000      0xf7def0b3      0x00007fff
```

Also, I know that address of the $rip is 0x7fffffffe4c8:
```
(gdb) info frame
Stack level 0, frame at 0x7fffffffe4d0:
 rip = 0x4011a0 in foo (buffer.c:25); saved rip = 0x401156
 called by frame at 0x7fffffffe4d8
 source language c.
 Arglist at 0x7fffffffe4c0, args:
 Locals at 0x7fffffffe4c0, Previous frame's sp is 0x7fffffffe4d0
 Saved registers:
  rbp at 0x7fffffffe4c0, rip at 0x7fffffffe4c8
```

Since $rip is located after the buf, we can change its value using buffer overflow. We can change it to the address of first instruction of `hack` function, which is 0x00401156:
```
(gdb) disassemble hack
Dump of assembler code for function hack:
   0x0000000000401156 <+0>:     push   %rbp
   0x0000000000401157 <+1>:     mov    %rsp,%rbp
   0x000000000040115a <+4>:     mov    $0x402008,%edi
   0x000000000040115f <+9>:     callq  0x401030 <puts@plt>
   0x0000000000401164 <+14>:    mov    $0x0,%edi
   0x0000000000401169 <+19>:    callq  0x401060 <exit@plt>
End of assembler dump.
```

So the value of buf in exploit will be: 32 any symbols + copy of register values up to $rip + address of the first instruction of `hack` function. After that we get the following result:
```bash
ernurator@DESKTOP-T1TMEL5:/mnt/c/Users/isenb/projects/sys_prog_labs/Sys-Prog-Labs/lab3/buf$ ./buffer < exploit2.txt
My favorite number is 12 and it will always be 12 and nothing can change that
My favorite number is 12 and it will always be 12 and nothing can change that
you've been hacked!
```

