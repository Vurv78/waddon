# ``waddon``
Example of how to use [wasm2lua](https://github.com/SwadicalRag/wasm2lua) to embed typical programs on Windows.

This embeds:
* [tiny-json](https://github.com/rafagafe/tiny-json)
* [pocketlang](https://github.com/ThakeeNathees/pocketlang)

## Prerequisites
Make sure you have the [wasi-sdk](https://github.com/WebAssembly/wasi-sdk) installed, with the path at ``%WASI_SDK_PATH%``
Get it from the releases (mingw)

## Usage
1. Run ``build.bat``.
2. Edit ``build.bat`` to comment out the line with lua-webidl. (Put 'rem' or '::' before it)
3. Run it again
4. Lua should be generated in ``waddon.lua``
5. See the src-lua folder for example usage from lua.