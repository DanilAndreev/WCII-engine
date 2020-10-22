#pragma once

typedef int Exitcode;

// Parser exitcodes
const Exitcode GM_NO_ERROR = 0; // No errors
const Exitcode GM_ERROR_ALLOCATING_MEMORY = 1; // Error allocating memory
const Exitcode GM_ERROR_ARGUMENTS_COUNT = 2; // Error, too low arguments
const Exitcode GM_ERROR_NOT_VALID_TYPE = 3; // Error, not valid type of target input
const Exitcode GM_ERROR_NOT_VALID_STRUCTURE = 4; // Error, not valid structure of encoding
const Exitcode GM_ERROR_NULL_POINTER = 5; // Error, not valid structure of encoding
