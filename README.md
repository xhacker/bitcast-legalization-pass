# Bitcast Legalization Pass

```sh
opt -S -load xcode/BitcastLegalization/Debug/libBitcastLegalization.so -bitcastlegalization < tests/i1.ll
```

## Build and Run Using `cmake`, `make`, and `opt`

```sh
mkdir build
cd build
cmake -G "Unix Makefiles" ..
make
cd ..
opt -S -load build/BitcastLegalization/libBitcastLegalization.so -bitcastlegalization < tests/i1.ll
```
