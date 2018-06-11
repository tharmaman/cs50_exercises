// Resizes a BMP file

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char *temp = argv[1];
    char *infile = argv[2];
    char *outfile = argv[3];

    // convert temp to float
    float f = atof(temp);

    // checking if num is a float between 0.0 to 100.0
    if (f < 0.0 || f > 100.0)
    {
        fprintf(stderr, "N must be a float between 0.0 to 100.0\n");
        return 1;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 1;
    }

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
        return 1;
    }

    // initialize outfile metadata
    BITMAPFILEHEADER bfo = bf;
    BITMAPINFOHEADER bio = bi;

    // declaring integer for triplet
    int triplet = sizeof(RGBTRIPLE);

    // determining the padding for infile
    int paddingi = (4 - (bi.biWidth * triplet) % 4) % 4;

    // adjusting outfile metadata dimensions
    bio.biHeight = (long)(bi.biHeight * f);
    bio.biWidth = (long)(bi.biWidth * f);

    // determining the padding for outfile
    int paddingo =  (4 - (bio.biWidth * triplet) % 4) % 4;

    // determining the remaining metadata
    bio.biSizeImage = abs(bio.biHeight * (bio.biWidth * triplet + paddingo));
    bfo.bfSize = bio.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfo, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bio, sizeof(BITMAPINFOHEADER), 1, outptr);

    // seperate cases for enlargening or reducing

    // reducing case
    if (f < 1.0)
    {
        // inputting outfile's scanlines
        for (int i = 0, bioHeight = abs(bio.biHeight); i < bioHeight; i++)
        {
            // inputting outfile's pixels by row
            for (int j = 0, bioWidth = bio.biWidth; j < bioWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // determining the location of the infile pixel to copy into the outfile space
                long oldPixel = (sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)) + 
                (long)(i * (bi.biWidth * triplet + paddingi) + (j * triplet)) / f;

                //  adjusting copy cursor to the oldPixel's location
                fseek(inptr, oldPixel, SEEK_SET);

                // read RGB triple from infile
                fread(&triple, triplet, 1, inptr);

                // write RGB triple to outfile
                fwrite(&triple, triplet, 1, outptr);

            }
            // adding in padding
            for (int p = 0; p < paddingo; p++)
            {
                fputc(0x00, outptr);
            }
        }
    }
    // enlargening case
    else
    {
    // scanline counter
    int scount = 0;

    // pixel repeater
    int prep = 0;
        // loop over outfile's scanlines
        for (int i = 0, bioHeight = abs(bio.biHeight); i < bioHeight; i++)
        {
            // loop over outfile's pixels
            for (int j = 0, bioWidth = abs(bio.biWidth); j < bioWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, triplet, 1, inptr);

                // write RGB triple to outfile
                fwrite(&triple, triplet, 1, outptr);

                // incrementing pixel repeater
                prep++;

                // check if the pixel has repeated enough
                if (prep < (int)(f))
                {
                    // resets cursor to the beginning of the pixel for repitition
                    fseek(inptr, -triplet, SEEK_CUR);
                }
                else
                {
                    // resets repeater in order to move onto new pixel
                    prep = 0;
                }
            }
            // skip over padding, if any
            fseek(inptr, paddingi, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < paddingo; k++)
            {
                fputc(0x00, outptr);
            }
            // incrementing scount
            scount++;

            // check to see if scanline has been repeated enough (height)
            if (scount < (int)(f))
            {
                // resets cursor to the beginning of the scanline for repetition
                fseek(inptr, -((bi.biWidth * triplet + paddingi)), SEEK_CUR);
            }
            else
            {
                // reset scanline counter to 0
                scount = 0;
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // its lit
    return 0;
}