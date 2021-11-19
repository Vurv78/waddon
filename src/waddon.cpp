#include "waddon.hpp"
#include <stdio.h>
#include <cstring>

#include "../tiny-json/tiny-json.h"

int add_one(int x) {
	return x + 1;
}

// Returns the char* with 'x' appended to it.
char* ret_str(char* x) {
	return x;
}

enum { MAX_FIELDS = 4 };

// Should the return the 'age' field of the given json object (hardcoded)
int json_test(char* obj) {
	json_t pool[ MAX_FIELDS ];

	json_t const* parent = json_create( obj, pool, MAX_FIELDS );
	if ( parent == NULL ) return EXIT_FAILURE;

	json_t const* age = json_getProperty( parent, "age" );
	if ( age == NULL ) return EXIT_FAILURE;
	if ( json_getType( age ) != JSON_INTEGER ) return EXIT_FAILURE;

	return json_getInteger( age );
}