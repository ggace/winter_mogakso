# rev-basic-0

-[문제페이지](https://dreamhack.io/wargame/challenges/14)

## 문제 해설

해당 문제는 리버싱 문제로 실행파일만 주어진다. 

이를 좀더 쉽게 분석하기 위해 ida를 사용하겠다. 

파일을 실행시키면
```bash
Input : 
```
다음과 같은 텍스트가 실행되기 때문에 이를 실행하는 부분을 디컴파일을 하면

```c
__int64 sub_140001100()
{
  char v1; // [rsp+20h] [rbp-118h]

  memset(&v1, 0, 0x100ui64);
  sub_140001190("Input : ");
  sub_1400011F0("%256s", &v1);
  if ( (unsigned int)sub_140001000(&v1) )
    puts("Correct");
  else
    puts("Wrong");
  return 0i64;
}
```

다은과 같다. 

sub_140001000에서 참값을 가져오면 될것 같다.

```c
_BOOL8 __fastcall sub_140001000(const char *a1)
{
  return strcmp(a1, "Compar3_the_str1ng") == 0;
}
```
Compar3_the_str1ng를 입력하면 되기 때문에 
정답은 

DH{Compar3_the_str1ng}이다.

![alt text](image.png)