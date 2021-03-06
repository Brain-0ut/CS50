// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember resize scale
    char *c = argv[1];
    int n = c[0] - '0';
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    FILE *tmp;
    /*
    if (tmp == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create temp file.\n");
        return 3;
    }
    */
    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);


    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }


    int padding_orig = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biWidth = bi.biWidth * n;
    bi.biHeight = bi.biHeight * n;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding) * abs(bi.biHeight);
    bf.bfSize = (bi.biWidth * sizeof(RGBTRIPLE) + padding) * abs(bi.biHeight) + bf.bfOffBits;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight) / n; i < biHeight; i++)
    {
        tmp = fopen("tmp", "w");
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth / n; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            for (int x = 0; x < n; x++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, tmp);
            }
        }

        // skip over padding, if any
        fseek(inptr, padding_orig, SEEK_CUR);

        // then add it back (to demonstrate how)

        fclose(tmp);
        tmp = fopen("tmp", "r");
        for (int x = 0; x < n; x++)
        {
            for (int j = 0; j < bi.biWidth; j++)
            {
                RGBTRIPLE triple;
                fread(&triple, sizeof(RGBTRIPLE), 1, tmp);
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
            fseek(tmp, 0, SEEK_SET);
        }
        fclose(tmp);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // remove tmp file
    remove("tmp");
    // success
    return 0;
}
