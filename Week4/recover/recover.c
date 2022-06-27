#include <stdio.h>
#include <stdlib.h>

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    char out_filename[8];
    unsigned char buffer[BLOCK_SIZE]; //initialize the buffer of 512 byte
    int file_idx = 0;
    FILE *outptr;

    while (fread(buffer, BLOCK_SIZE, 1, inptr))
    {
        //checking if this block is start of .jpg file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //if this .jpg file wasn't first, closes the previous file
            if (file_idx)
            {
                fclose(outptr);
            }
            sprintf(out_filename, "%03i.jpg", file_idx);
            file_idx++;
            outptr = fopen(out_filename, "w");
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", out_filename);
                return 3;
            }
        }
        //if output file is opened, then write current block into the file
        if (outptr != NULL)
        {
            fwrite(buffer, BLOCK_SIZE, 1, outptr);
        }
    }
    //closes all opened files
    fclose(outptr);
    fclose(inptr);
    return 0;
}
