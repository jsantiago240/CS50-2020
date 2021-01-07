/* Javius Santiago
   Recover.c
   6/18/2020
   Program recovers JPEGs from a forensic image.
   See README.txt for pseudocode
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// The size of each block is 512 Bytes
const int BLOCK_SIZE = 512;
/* The length of the jpg filenames will be 8, 3 chars for the digits,
   1 for "." and 3 for "jpg" plus the null terminating character
*/
const int FILE_NAME_LENGTH = 8;

// Prototype for function used to determine if a block signifies the start of a jpg
bool isJPG(unsigned char myBuffer[BLOCK_SIZE]);

int main(int argc, char *argv[])
{
    // 512 Byte buffer to be analyzed
    unsigned char buffer[BLOCK_SIZE];
    char filename[FILE_NAME_LENGTH];
    int jpgCount = 0;
    bool jpgFound = false;
    // File pointer we will write data to
    FILE *outfile = NULL;

    // Ensures proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover FILENAME.raw\n");
        return 1;
    }

    // Forensic image we will analyze
    FILE *infile = fopen(argv[1], "r");

    // Ensures file is properly read
    if (infile == NULL)
    {
        printf("Error reading file\n");
        return 1;
    }

    // Loops through until end of file, when 512 Bytes can't be read
    while (fread(&buffer, BLOCK_SIZE, 1, infile) == 1)
    {
        // Is the current block the start of a jpg
        if (isJPG(buffer))
        {
            // Is this the first jpg found
            if (jpgFound == false)
            {
                jpgFound = true;
            }
            // If this is a new jpg, but not the first one to be found
            else
            {
                // Close file currently being written to
                fclose(outfile);
                // Update jpgCount (for filename)
                jpgCount++;
            }
            // Update filename and open new file, then write / continue writing
            sprintf(filename, "%03i.jpg", jpgCount);
            outfile = fopen(filename, "a");
            fwrite(&buffer, BLOCK_SIZE, 1, outfile);
        }
        // If this block is not the start of a jpg file
        else
        {
            // Has a jpg already been found
            if (jpgFound == true)
            {
                // Keep writing to the current file
                fwrite(&buffer, BLOCK_SIZE, 1, outfile);
            }
        }
    }

// Close any file that may be open
    fclose(infile);
    fclose(outfile);

    return 0;
}

// Determines if a given block signifies the start of a jpg
bool isJPG(unsigned char myBuffer[BLOCK_SIZE])
{
    if (myBuffer[0] == 0xff && myBuffer[1] == 0xd8 && myBuffer[2] == 0xff && (myBuffer[3] & 0xf0) == 0xe0)
    {
        return true;
    }
    return false;
}
