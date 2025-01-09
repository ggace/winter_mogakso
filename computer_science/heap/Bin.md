# Bin(Linux 기준)
(메모리 해제시 청크 저장을 위한 객체)

## 용어
### unlink
- 청크 추가, 꺼낼때, 연결을 끊는 과정
### consolidation
- 병합이 가능한 bin에서 메모리상 인접한 두 청크의 병합.

## 청크 관리 방법
(크기에 따라 들어가는 BIN의 우선순위가 존재한다.)
### LIFO
- 속도 $\uarr$
- 파편화가 심함.
### address ordered
- 속도 $\darr$
- 파편화가 적음
### FIFO
- LIFO와 address ordered의 사이정도 성능.

## Small Bin (32byte ~ 1023byte)
- 하나의 smallbin에는 같은 크기의 청크만 저장됨.
- 16byte 단위 61개
- 이중 원형 연결 리스트
- FIFO
- 병합 가능

## Fast Bin (32byte ~ 128byte)
- 크기가 작은 청크.
- 16byte 단위 7개
- 단일 연결 리스트
- unlink가 필요하지 않음.
- LIFO
- 병합 불가

## Large Bin (1024byte ~ 1087byte)
- 63개
- 일정범위 내의 크기를 가진 청크를 보관.
- best fit을 통한 재할당
- 크기 내림차순
- 이중 연결 리스트
- unlink 필요
- 병합 가능

## Unsorted Bin
- 분류되지 않은 청크
- 이중 연결 리스트
- 정렬 X
* 탐색 순서
    (탐색과정에서 분류가 이루어짐)
    - fast bin/small bin $\rarr$ unsorted bin
    - large bin $\rarr$ unsorted bin

