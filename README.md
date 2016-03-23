# Bitcast Legalization Pass

## Build and Run Using `cmake`, `make`, and `opt`

```sh
mkdir build
cd build
cmake -G "Unix Makefiles" ..
make
cd ..
opt -S -load build/BitcastLegalization/libBitcastLegalization.so -bitcastlegalization < tests/i1.ll
```

## Build and Run Using Xcode and `opt`

```sh
mkdir xcode
cd xcode
cmake -G "Xcode" ..
# Open Xcode and build
cd ..
opt -S -load xcode/BitcastLegalization/Debug/libBitcastLegalization.so -bitcastlegalization < tests/i1.ll
```
