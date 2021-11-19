Mod = dofile("waddon.lua")
Mod.init()

print( Mod.bindings.global.add_one( 500 ) == 501 )
print( Mod.bindings.global.ret_str("Foo") == "Foo" )
print( Mod.bindings.global.json_test( "{ \"name\": \"peter\", \"age\": 32 }" ) == 32 )
print( Mod.bindings.global.json_test( "bad input" ) == 1 )