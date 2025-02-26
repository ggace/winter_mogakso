# rev-basic-3

- [문제페이지](https://dreamhack.io/wargame/challenges/17)

## 문제해설

실행파일을 실행하면
```
Input : 
```

다음과 같다.

따라서 이를 실행하는 함수를 찾으면

```c
__int64 sub_140001120()
{
  char v1; // [rsp+20h] [rbp-118h]

  memset(&v1, 0, 0x100ui64);
  sub_1400011B0("Input : ");
  sub_140001210("%256s", &v1);
  if ( (unsigned int)sub_140001000(&v1) )
    puts("Correct");
  else
    puts("Wrong");
  return 0i64;
}
```

다음과 같다. sub_140001000를 보면

```c
signed __int64 __fastcall sub_140001000(__int64 a1)
{
  int i; // [rsp+0h] [rbp-18h]

  for ( i = 0; (unsigned __int64)i < 0x18; ++i )
  {
    if ( byte_140003000[i] != (i ^ *(unsigned __int8 *)(a1 + i)) + 2 * i )
      return 0i64;
  }
  return 1i64;
}
```
이다. 이를 그대로 파이썬 코드로 작성하면

```python
a = ["49","60","67","74","63","67","42","66","80","78","69","69","7B","99","6D","88","68","94","9F","8D","4D","A5","9D","45"]
r = []
for i in range(0x18):
	r.append((int(a[i], 16) - 2*i) ^ i)

print("DH{", end="")
for d in r:
	print(chr(d), end="")
print("}")
```
```
DH{I_am_X0_xo_Xor_eXcit1ng}
```
이다.

![alt text](image.png)