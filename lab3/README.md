## Part 1

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

