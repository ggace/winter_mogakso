# Double Free Bug
(같은 청크를 두번 해제하여 발생하는 버그)

## 이론
1. 청크가 두번 해제되어 있는다.
2. 해당 청크를 한번 할당하여 data영역에 속한 fd와 bk를 변조한다.
3. 다시한번 할당하여 임의의 주소를 할당, 변조할 수 있게 한다.
- 이걸 방지하기 위해 보호 기법이 적용됨

## 보호기법
```c
typedef struct tcache_entry {
    struct tcache_entry *next;
    /* This field exists to detect double frees.  */
    struct tcache_perthread_struct *key;
} tcache_entry;
```
key가 추가되어 있다. (fd $\rarr$ next, bk $\rarr$ key)

### Tcache Put
```c
tcache_put(mchunkptr chunk, size_t tc_idx) {
    tcache_entry *e = (tcache_entry *)chunk2mem(chunk);
    assert(tc_idx < TCACHE_MAX_BINS);
  
    /* Mark this chunk as "in the tcache" so the test in _int_free will detect a double free.  */
    e->key = tcache;
    e->next = tcache->entries[tc_idx];
    tcache->entries[tc_idx] = e;
    (tcache->counts[tc_idx]);
}
```
key: tcache를 저장함

### Tcache Get
```c
tcache_get (size_t tc_idx)
    assert (tcache->entries[tc_idx] > 0);
    tcache->entries[tc_idx] = e->next;
    --(tcache->counts[tc_idx]);
    e->key = NULL;
    return (void *) e;
}
```
할당시 key에 NULL을 대입함.

### _int_free
```c
_int_free (mstate av, mchunkptr p, int have_lock) {
    #if USE_TCACHE {
        size_t tc_idx = csize2tidx (size);
        if (tcache != NULL && tc_idx < mp_.tcache_bins) {
            /* Check to see if it's already in the tcache.  */
            tcache_entry *e = (tcache_entry *) chunk2mem (p);

            /* This test succeeds on double free.  However, we don't 100% trust it (it also matches random payload data at a 1 in 2^<size_t> chance), so verify it's not an unlikely coincidence before aborting.*/
            if (__glibc_unlikely (e->key == tcache)) {
                tcache_entry *tmp;
                LIBC_PROBE (memory_tcache_double_free, 2, e, tc_idx);
                for (tmp = tcache->entries[tc_idx]; tmp; tmp = tmp->next)
                    if (tmp == e)
                       malloc_printerr ("free(): double free detected in tcache 2");
                    /* If we get here, it was a coincidence.  We've wasted a few cycles, but don't abort.  */
            }

            if (tcache->counts[tc_idx] < mp_.tcache_count) {
                tcache_put (p, tc_idx);
                return;
            }
        }
    }
    #endif
}
```

```c
if (__glibc_unlikely (e->key == tcache))
```
이 부분이 통과하면 double free가 가능하다. 이때, e->key가 한비트만이라도 바뀌면 double free가 가능하다.