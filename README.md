# UserCF
Implement User-based Collaborative Filtering RecSys and a baseline RecSys which recommeds the topk most popular items.

## how to run
download the movielens 100k dataset from 

[http://files.grouplens.org/datasets/movielens/ml-100k.zip](http://files.grouplens.org/datasets/movielens/ml-100k.zip)

and extract it to current folder.

then, compile main.cpp
```shell
g++ main.cpp -std=c++11
```
finally, run

on Linux
```
./a.out
```
on Windows: 
```
a.exe
```

## Result
MostPopular:
```
k=5, f1=6.63%, precision=32.20%, recall=3.69%
k=10, f1=11.35%, precision=30.39%, recall=6.97%
k=20, f1=16.02%, precision=25.46%, recall=11.68%
k=40, f1=20.73%, precision=21.66%, recall=19.88%
k=80, f1=22.72%, precision=17.55%, recall=32.21%
k=160, f1=21.02%, precision=13.37%, recall=49.09%
```
UesrCF:
```
k=5, f1=5.93%, precision=28.80%, recall=3.30%
k=10, f1=10.46%, precision=28.02%, recall=6.43%
k=20, f1=16.13%, precision=25.63%, recall=11.76%
k=40, f1=22.11%, precision=23.10%, recall=21.20%
k=80, f1=25.51%, precision=19.71%, recall=36.18%
k=160, f1=23.35%, precision=14.85%, recall=54.54%
```
UserCF is just a little better then MostPopular when k is large.
