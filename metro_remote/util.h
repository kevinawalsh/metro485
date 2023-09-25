#ifndef _UTIL_H_
#define _UTIL_H_

#include <Arduino.h>
#include <Stream.h>

extern bool debug_metro;

extern byte color_map[];

//// // Compute a simple checksum over a string. Returns a 16-bit checksum value.
//// unsigned int compute_checksum(char *s);
//// 
//// // Checks to ensure the given string begins with "#", a hex-formatted number,
//// // and space, where the number matches the checksum of the rest of the string.
//// // If so, this returns a pointer to the rest of the string. If the string format
//// // is incorrect or the checksum value does not match, an error is printed and
//// // nullptr is returned. 
//// char *validate_checksum(char *s);
//// 
//// // Send "#", a hex-formatted number, a space, the given string, and a newline to
//// // the serial port, where the number is a checksum computed over the string.
//// void serial_write_with_checksum(char *line);

// Check whether buf exactly matches cmd, returns true if match.
bool match(const char *buf, const char *cmd);

// Check whether buf starts with prefix, returns true if match.
bool match_prefix(const char **buf, const char *prefix);

// Check whether buf exactly matches cmd, or starts with cmd, then a space, then
// a number. If so, returns true, updates param to the received number (or -1 if
// a number was not given), and updates buf to point to the character after the
// matched portion.
bool match(const char **buf, const char *cmd, int *param);

// LineBuffer gathers data from a given stream, splits it into lines, removes
// the newlines, and returns them one by one. Each line can be at most 255
// characters, not including the newline. Longer lines are discarded.
// Example:
//   ...
//   LineBuffer myInput(&Serial);
//   ...
//   if ((char *line = myInput.nextLine())) {
//     int n = myInput.length(); // same as: n = strlen(line);
//     ... line now contains n characters ...
//   }
//
#define LINE_BUFFER_LEN (256)
class LineBuffer {

  public:

    // Construct LineBuffer that gathers data from the given stream.
    LineBuffer(Stream *base);

    // Discard any previous line, gather more data if needed and if available,
    // chop into lines, and return pointer to start of next line. The returned
    // pointer is to an internal buffer, and should not be freed. Returns
    // nullptr if the next line isn't yet available. 
    char *nextLine();

    // Returns length of current line, the one most recently returned from
    // nextLine(). If there is no current line, i.e. if nextLine() returned
    // nullptr, this returns -1;
    int linelen();

  private:

    Stream *base; // underlying stream from which data is read
    char buf[LINE_BUFFER_LEN]; // buffer
    int len; // amount of data in buffer
    int eol; // length of most recently returned line

};

#endif // _UTIL_H_
