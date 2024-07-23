// C program for illustration of regcomp()
#include <regex.h>
#include <stdio.h>

// prase ADEXP with regex
// /-([[:word:]]+)?[[:space:]]?([[:alnum:]|[:space:]]+)?/gm
// test string
// -TITLE ABI-ARCID MAH100-ADEP LHBP-ADES EGLL-ATD-RTE ERGOM NIT BNO BIG-WTC M-ATYP B733-EOBD 1807-ETD 1324-RFL 340
// expected output
/*
  const regex = /-([[:word:]]+)?[[:space:]]?([[:alnum:]|[:space:]]+)?/gm;

// Alternative syntax using RegExp constructor
// const regex = new
RegExp('-([[:word:]]+)?[[:space:]]?([[:alnum:]|[:space:]]+)?', 'gm')

const str = `-TITLE ABI-ARCID MAH100-ADEP LHBP-ADES EGLL-ATD-RTE ERGOM NIT BNO
BIG-WTC M-ATYP B733-EOBD 1807-ETD 1324-RFL 340`; let m;

while ((m = regex.exec(str)) !== null) {
    // This is necessary to avoid infinite loops with zero-width matches
    if (m.index === regex.lastIndex) {
        regex.lastIndex++;
    }

    // The result can be accessed through the `m`-variable.
    m.forEach((match, groupIndex) => {
        console.log(`Found match, group ${groupIndex}: ${match}`);
    });
}

 */
// Driver Code
int main(void) {

    const char *rex = "-([[:word:]]+)?[[:space:]]?([[:alnum:]|[:space:]]+)?";
    // Variable to create regex
    regex_t regex;

    // Variable to store the return
    // value after creation of regex
    int value;

    // Function call to create regex
    // value = regcomp(&regex, "[:word:]", 0);
    value = regcomp(&regex, rex, REG_EXTENDED);

    // If compilation is successful
    if (value == 0)
    {
        printf("RegEx compiled successfully.");
	}

	// Else for Compilation error
	else {
		printf("Compilation error.");
	}
	return 0;
}
