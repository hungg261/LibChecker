import sys
from decimal import Decimal, getcontext

# very high precision
getcontext().prec = 100

input = sys.stdin.readline

class P:
    def __init__(self,x=0,y=0):
        self.x = Decimal(x)
        self.y = Decimal(y)

    def __add__(self,o):
        return P(self.x+o.x,self.y+o.y)

    def __sub__(self,o):
        return P(self.x-o.x,self.y-o.y)

    def __mul__(self,k):
        k = Decimal(k)
        return P(self.x*k,self.y*k)

    def eq(self,o):
        return self.x == o.x and self.y == o.y


def dot(a,b):
    return a.x*b.x + a.y*b.y

def cross(a,b):
    return a.x*b.y - a.y*b.x

def norm(a):
    return (dot(a,a)).sqrt()

def ccw(a,b,c):
    v = cross(b-a,c-a)
    if v>0: return 1
    if v<0: return -1
    return 0

def onSeg(a,b,p):
    if ccw(a,b,p)!=0:
        return False
    return dot(p-a,p-b) <= 0

def dist(a,b):
    return norm(a-b)

def distSeg(p,a,b):
    ab=b-a
    ap=p-a
    bp=p-b

    if dot(ap,ab)<0:
        return norm(ap)

    if dot(bp,ab)>0:
        return norm(bp)

    return abs(cross(ab,ap))/norm(ab)

def project(p,a,b):
    ab=b-a
    t = dot(p-a,ab)/dot(ab,ab)
    return a + ab*t

def reflect(p,a,b):
    q = project(p,a,b)
    return P(q.x*2-p.x,q.y*2-p.y)


# robust intersection
def intersect(a,b,c,d):

    o1 = ccw(a,b,c)
    o2 = ccw(a,b,d)
    o3 = ccw(c,d,a)
    o4 = ccw(c,d,b)

    # collinear -> infinite intersections -> NO
    if o1==0 and o2==0 and o3==0 and o4==0:
        return False,None

    # no intersection
    if o1*o2>0 or o3*o4>0:
        return False,None

    ab=b-a
    cd=d-c

    den = cross(ab,cd)
    if den==0:
        return False,None

    t = cross(c-a,cd)/den
    p = a + ab*t

    return True,p


n,q = map(int,input().split())

p=[None]*(n+1)

for i in range(1,n+1):
    x,y = input().split()
    p[i]=P(x,y)

for _ in range(q):

    t=input().split()

    if t[0]=="ADD":
        i,j=int(t[1]),int(t[2])
        r=p[i]+p[j]
        print(f"{r.x:.12f} {r.y:.12f}")

    elif t[0]=="SCALE":
        i=int(t[1])
        k=Decimal(t[2])
        r=p[i]*k
        print(f"{r.x:.12f} {r.y:.12f}")

    elif t[0]=="EQUAL":
        i,j=int(t[1]),int(t[2])
        print("YES" if p[i].eq(p[j]) else "NO")

    elif t[0]=="DOT":
        i,j=int(t[1]),int(t[2])
        print(f"{dot(p[i],p[j]):.12f}")

    elif t[0]=="CROSS":
        i,j=int(t[1]),int(t[2])
        print(f"{cross(p[i],p[j]):.12f}")

    elif t[0]=="CCW":
        a,b,c=map(int,t[1:])
        print(ccw(p[a],p[b],p[c]))

    elif t[0]=="DIST":
        i,j=int(t[1]),int(t[2])
        print(f"{dist(p[i],p[j]):.12f}")

    elif t[0]=="ONSEG":
        i,a,b=map(int,t[1:])
        print("YES" if onSeg(p[a],p[b],p[i]) else "NO")

    elif t[0]=="DISTSEG":
        i,a,b=map(int,t[1:])
        print(f"{distSeg(p[i],p[a],p[b]):.12f}")

    elif t[0]=="PROJECT":
        i,a,b=map(int,t[1:])
        r=project(p[i],p[a],p[b])
        print(f"{r.x:.12f} {r.y:.12f}")

    elif t[0]=="REFLECT":
        i,a,b=map(int,t[1:])
        r=reflect(p[i],p[a],p[b])
        print(f"{r.x:.12f} {r.y:.12f}")

    elif t[0]=="INTERSECT":
        a,b,c,d=map(int,t[1:])
        ok,r=intersect(p[a],p[b],p[c],p[d])
        if ok:
            print(f"YES {r.x:.12f} {r.y:.12f}")
        else:
            print("NO")