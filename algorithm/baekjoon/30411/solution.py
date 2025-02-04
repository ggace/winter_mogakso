n, k = map(int, input().split())

possible = n-1
for i in range(1, n):
    possible += (n-1-i)//2
    if(possible >= k):
        print("YES")
        break

if(possible < k):
    print("NO")
    exit()
        

for i in range(1, n):
    print(f"{i} {i+1}")
    k -= 1
    if(k == 0):
        break;

for i in range(1, n):
    if(k == 0) :
        break;
    for j in range(i+3, n+1, 2):
        print(f"{i} {j}")
        k -= 1
        if(k == 0):
            break;
