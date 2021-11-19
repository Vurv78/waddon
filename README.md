# ``waddon``
(soon to be example) of a garrysmod addon using [wasm2lua](https://github.com/SwadicalRag/wasm2lua)

Shows how to embed tiny-json.  
I wanted to show off embedding large libraries like quickjs/lua, however they have issues with windows/webassembly at least for me.

## Prerequisites
Make sure you have the [wasi-sdk](https://github.com/WebAssembly/wasi-sdk) installed, with the path at ``%WASI_SDK_PATH%``
Get it from the releases (mingw)

## Usage
1. Run ``build.bat``.
2. Edit ``build.bat`` to comment out the line with lua-webidl. (Put 'rem' or '::' before it)
3. Run it again
4. Lua should be generated in waddon.lua
5. Go into waddon.lua and replace ``__MALLOC__`` and ``__FREE__`` with:

```lua
local __MALLOC__ = function() return 0 end
local __FREE__ = function() end
```
6. See/run test.lua for an example.