n, m, q = map(int, input().split())
a = [[0]*(m+1) for _ in range(n+1)]

for i in range(1, n+1):
    row = list(map(int, input().split()))
    for j in range(1, m+1):
        a[i][j] = row[j-1]

for _ in range(q):
    query = list(map(int, input().split()))
    if query[0] == 1:
        _, x, y, k = query
        a[x][y] += k
    else:
        _, x1, y1, x2, y2 = query
        s = 0
        for i in range(x1, x2+1):
            for j in range(y1, y2+1):
                s += a[i][j]
        print(s)
