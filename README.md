# holbertonschool-printf
Creating a function that behaves similar to printf. but less well handled depending on who's asking.

Design Notes :
All output goes through write() — no string.h functions are used anywhere, per the project's constraints.
handle_string writes its entire string in one write() call, passing the string's own memory directly as the buffer, rather than looping character-by-character or building a separate copy.
handle_char and handle_percent both go through the shared putchar_out helper for their single-character writes, avoiding duplicated write()/error-checking logic.
%c requires pulling the argument as int, not char, because C automatically promotes char arguments to int when passed through a variadic ... parameter.
A NULL argument to %s is handled explicitly and prints (null), matching real printf's behavior instead of crashing.
Return values are checked, not ignored: write()'s result is compared against the exact number of bytes requested (not just checked for < 0), since a partial write is a distinct possibility from an outright error.


File Names and Function :

main.h - Contains all function prototypes
A prototype is a one-line declaration that tells the compiler "this function exists, here's its name, and here's exactly what it takes in and what it gives back" — without actually containing the function's code.

_printf.c - printf is the entry point that walks the format string by individual character and routes any % conversion directly to matching handler.

putchar_out.c - writes a single character output using write(). used by handle_char and handle_percent. ssize_t result; -- declared to hold whatever write() reports back. the s infront of size stands for "signed". its a a byte count that's allowed to be negative, because negative means error. Any time you're capturing what write() or read() directly hands back, ssize_t. in this case failure or error is -1

handle_char.c - Handles %c which pulls the argument as an int and casts it back to char, which then writes it via putchar_out. 
c = (char)va_arg(args, int); -- two things happen on this line. First, va_arg(args, int) reaches into the argument list and pulls out the next value, treating it as an int -- this is required because char arguments get automatically promoted to int when passed through a variadic '...' parameter, so that's the type that's actually sitting there. Second, (char) casts that int back down to a char, since that's what it always represented.

handle_string.c - Handles %s, it pulls a char * which falls back to "(null)". If the pointer is NULL it measures its length and writes the whole string in a single write()call
1. function signature
int handle_string(va_list args)  takes the variadic argument list positioned at the %s argument, returns an int (the character count, or -1 on failure).
2. declare variables
char *str; and int len;  str will hold the pointer to the string, len will hold its length once measured.
3. pull the string pointer
str = va_arg(args, char *); -- pulls the argument as a char * (a pointer), which is the correct type for %s 
4 guard against NULL
if (str == NULL) str = "(null)"; -- guards against a crash. If the caller passed no real string, this swaps in the literal "(null)" so the rest of the function can proceed normally
5. measure the length
len = 0; while (str[len]) len++; -- walks the string counting characters until it hits the null terminator ('\0'). This is a written replacement for strlen(), since string.h isn't allowed.
6. write it all in one call
if (write(1, str, len) != len) return (-1); -- writes the entire string in one system call. 1 is stdout, str is the buffer (the string's own memory, no copy needed), len is how many bytes to write. Comparing the result to len (not just checking for -1).
7. return the count
return (len); -- if the write succeeded, hands back the character count for the caller's running total.


handle_percent - Handles %%. It writes a literal '%' via putchar_out. 
int handle_percent(void) -- takes no arguments at all, since %% doesn't consume anything from the caller's argument list. Returns an int reporting success or failure.







