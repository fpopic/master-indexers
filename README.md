#### Usage:

Used to preprocess input files on single machine because it constructs shared lookup table \
(sync for mutable collection needed on multicore) and maps ids to indices \
(e.g. customerId => customerIndex, itemId => itemIndex) and saves the file with it's lookup table. 

Indices are prefered over ids because linear algebra libraries operate with indices.

Scala time > 45 min (only item-item matrix)\
C++   time < 5 min  (both matrices)

#### Compile:

using g++:

```g++ -static -std=c++11 -O3 indexer.cpp -o indexer```

or with cmake:

```
mkdir cmake-build-debug
cmake --build cmake-build-debug --target indexer -- -j 4
```

#### Run:

``./indexer <item_item_input> <customer_item_input>``

Output files will be in the same folder as input with .indexed and .lookup suffix.

#### Output:
```
Header: itemId1,itemId2,a,b,c,d
Processed lines:1000000
...
Processed lines:71000000
Output file with 71930771 lines saved.
Lookup file with 67052 entries saved.
Time: 166s

Header: customerId,date,itemId,quantity
Processed lines:1000000
...
Processed lines:29000000
Output file with 29154707 lines saved.
Lookup file with 20998 entries saved.
Time: 50s

Process finished with exit code 0
```