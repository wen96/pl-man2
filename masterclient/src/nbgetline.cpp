//////////////////////////////////////////////////////////////////
/// \brief Non-blocking Getline: gets a line of chars from a input
/// stream, waiting until it gets to a delimiter or a timeout.
/// It returns a string without the delimiter at the end.
/// \param in       Input stream where to get the characters from. Assumed to be non-blocking.
/// \param str      String where received characters will be written to. It will be erased.
/// \param delim    Delimiter character. '\n' by default.
/// \param timeout  Milliseconds to wait for a new character whenever EOF is found (3 by default)
//////////////////////////////////////////////////////////////////
void nb_getline(boost::fdistream &in, std::string &str,
                char delim, unsigned timeout) const
{
  std::stringstream ss;
  char c = 0;

  // Timeout needs to be incremented +1, 'cause 0 does not count
  if (timeout + 1 != 0) timeout++;

  // Read characters while we do not found delimiter or we run out of time
  do {
    // Get next character (instream should be non-blocking!)
    in.clear();
    in.get(c);

    // Next character found, put it in provisional stream
    if (!in.eof()) {
      if (c != delim) ss << c;

    // Found eof, and we are in the middle of the line
    } else if (ss.str().length() > 0) {
      while (in.eof() && ss.str().length() > 0 && timeout > 0) {
        // Sleep 1 millisecond and try again
        usleep(1000);
        in.clear();
        timeout--;
      }

    // Nothing waiting to be read, let's exit
    } else break;
  } while ( timeout > 0 && c != delim );

  // Return the string overwritting the parameter str
  str = ss.str();
}
