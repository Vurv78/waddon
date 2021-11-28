Mod = dofile("../waddon.lua")
Mod.init()
Mod.setImports( {
	env = _G,
	wasi_snapshot_preview1 = dofile("wasilib.lua")(Mod.memory)
} )

--print( Mod.exports._start() )

print( "500 + 1: ", Mod.bindings.global.add_one( 500 ) )
print( "Foo + x: ", Mod.bindings.global.append_char("Foo") )
print( "x.age:", Mod.bindings.json.get_field_int( "{ \"name\": \"peter\", \"age\": 32 }", "age" ) )
print( "malformed.invalid: ", Mod.bindings.json.get_field_int( "bad input", "invalid" ) == 1 ) -- 1 is Json Failure

local example_handle, errmsg = io.open("example.pk", "rb")
if errmsg then error(errmsg) end
print("\nRunning pocketlang code:")
local code = example_handle:read("*a")
local status = Mod.bindings.global.pklang( code )
example_handle:close()

print("Ok? ", status == 0)