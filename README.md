<h1 align="center">
  <br>
  <a href="#"><img src="https://i.ibb.co/6mK5JzX/56a79468-08d4-41eb-b67b-58c38abc4353-200x200.png" alt="AliasAnalysis" width="200"></a>
  <br>
  Alias Analysis
  <br>
</h1>

<h4 align="center">Basic Alias Analysis implementation</h4>


## Table of Contents

- [Getting Started](#getting-started)
  - [Building from source](#build-from-source)
- [Usage](#usage)

## Getting Started

Basic implementation of alias analysis in LLVM.   
[x] Flow-insensitive Intra-procedural variant   
[x] Flow-sensitive Inter-procedural variant   
[x] Context-Sensitive Flow-sensitive Inter-procedural variant   

### Building from source
```sh
$ git clone this_repository.git
$ cd this_repository
$ mkdir build; cd build
$ cmake .. && make
```

## Usage
Use ```AADriver``` to run the analysis on any LLVM IR file.    
Run the flow-insensitive variant by ```AADriver test.ll```    
For now the first argument should be the LLVM IR file     
Use ```-fs``` for the flow-sensitive variant ```AADriver test.ll -fs```  
Use ```-cs``` for the control-sensitive variant ```AADriver test.ll -fs -cs```

