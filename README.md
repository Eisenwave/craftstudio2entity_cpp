# craftstudio2entity
Converts CraftStudio .csjsmodel files into Minecraft Bedrock Edition entity geometry files.

## Installation
This software has been developed using C++11.

To compile it from source, you require [CMake](https://cmake.org/).
Simply enter the repository folder and run `cmake .`.
This will generate the necessary `Makefile` or the equivalent on Windows or MacOS.
On Linux systems, run `make` and the binary will be found in the `bin/` directory.

## Usage

```bash
./craftstudio2entity <csjsmodel path> <entity path> [flags]
```

* `csjsmodel path` - (input) the CraftStudio JSON input file
* `entity path` - (output) the Minecraft Bedrock Edition entity model
* `flags` - `r` for "replace" (only flag right now)


## Conversion Specifics

The name of the model in CraftStudio becomes the name of the geometry in the output entity.

All hierarchies of blocks in CraftStudio as well as rotations, pivots and positionts are preserved 100%.
Every block becomes exactly one bone in an entity.
However, child blocks that have no rotations are simply become additional cubes of their parent bone.

#### CraftStudio Input
![CraftStudio](https://i.imgur.com/nFhRCA8.png)

#### Entity Output (visualized using [Blockbench](https://www.blockbench.net))
![Blockbench](https://i.imgur.com/nmA6CxB.png)
NOTE: to open an entity file in Blockbench, the name of the geometry must begin with `geometry.`.

UV is only preserved for "Full" UV in BlockBench but all textures are assumed to have a constant 128x128 size.
Automatic adjustment of texture dimensions may be added in the future.
