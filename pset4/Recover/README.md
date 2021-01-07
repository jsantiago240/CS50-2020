# Recover

//PSEUDOCODE******************************************************************************
// open memory card                             /
// repeat until end of card                     /
//  read 512 bytes into a buffer                /
//  if these bytes are the start of a new jpeg
//    if this is the first jpg
//      write 000.jpg
//    else
//      close the file we just wrote to
//      open new file
//      continue writing
//  else
//    if already found jpg
//      keep writing to it
// EOF
// close files