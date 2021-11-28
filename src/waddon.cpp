#include "waddon.hpp"
#include <stdio.h>
#include <cstring>
#include <string>

#include "../pocketlang/src/include/pocketlang.h"
#include "../tiny-json/tiny-json.h"

int add_one(int x) {
	return x + 1;
}

char* append_char(char* array) {
    size_t len = strlen(array);

	char* ret = (char*)malloc( (len + 2) * sizeof(char));

	// Need to make wasi op for _Znam for this to work so gonna use malloc instead
    //char* ret = new char[len + 2];

    strcpy(ret, array);
    ret[len] = 'x';
    ret[len+1] = '\0';

    return ret;
}

namespace json {
	enum { MAX_FIELDS = 4 };

	// Should the return the given field as a number
	int get_field_int(char* obj, char* field) {
		json_t pool[ MAX_FIELDS ];

		json_t const* parent = json_create( obj, pool, MAX_FIELDS );
		if ( parent == NULL ) return EXIT_FAILURE;

		json_t const* age = json_getProperty( parent, field );
		if ( age == NULL ) return EXIT_FAILURE;
		if ( json_getType( age ) != JSON_INTEGER ) return EXIT_FAILURE;

		return json_getInteger( age );
	}
}

static void pi(PKVM* vm) {
	pkReturnNumber(vm, 3.14);
}

// Error report callback.
static void reportError(PKVM* vm, PkErrorType type, const char* file, int line, const char* message) {
	fprintf(stderr, "Error: %s\n", message);
}

// print() callback to write stdout.
static void stdoutWrite(PKVM* vm, const char* text) {
	fprintf(stdout, "%s", text);
}

int pklang(char* input) {
	// Pocket VM configuration.
	PkConfiguration config = pkNewConfiguration();
	config.error_fn = reportError;
	config.write_fn = stdoutWrite;
	//config.read_fn = stdinRead;

	// Create a new pocket VM.
	PKVM* vm = pkNewVM(&config);

	// Register your module.
	PkHandle* your_module = pkNewModule(vm, "Waddon");
	pkModuleAddFunction(vm, your_module, "pi", pi, 0);
	pkReleaseHandle(vm, your_module);

	// The path and the source code.
	PkStringPtr source = { input, NULL, NULL, 0, 0 };
	PkStringPtr path = { "./src-lua/example.pk", NULL, NULL, 0, 0 };

	// Run the code.
	PkResult result = pkInterpretSource(vm, source, path, NULL);

	// Free the VM.
	pkFreeVM(vm);

	return (int)result;
}