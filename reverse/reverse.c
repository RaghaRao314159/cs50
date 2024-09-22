#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./volume input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // Read header
    WAVHEADER *header = malloc(sizeof(WAVHEADER));
    if (header == NULL)
    {
        printf("could not open header,\n");
        return 1;
    }


    fread(header, sizeof(WAVHEADER), 1, infile);

    // Use check_format to ensure WAV format
    if (check_format(*header) == 0)
    {
        printf("not wav format");
        return 1;
    }

    // Open output file for writing
    FILE *outfile = fopen(argv[2], "w");
    if (outfile == NULL)
    {
        printf("Could not open %s.\n", argv[2]);
        return 1;
    }


    // Write header to file
    fwrite(header, sizeof(WAVHEADER), 1, outfile);

    // Use get_block_size to calculate size of block
    BYTE block_size = get_block_size(*header);
    free(header);

    fseek(infile, -block_size, SEEK_END);
    int block[block_size];
    // Write reversed audio to file
    while (ftell(infile) > 43)
    {
        fread(block, sizeof(BYTE), block_size, infile);
        fwrite(block, sizeof(BYTE), block_size, outfile);
        fseek(infile, -2 * block_size, SEEK_CUR);
    }

    fclose(infile);
    fclose(outfile);
}

int check_format(WAVHEADER header)
{
    char wave[] = {'W', 'A', 'V', 'E'};
    for (int i = 0; i < 4; i++)
    {
        if (header.format[i] != wave[i])
        {
            return 0;
        }
    }
    return 1;
}

int get_block_size(WAVHEADER header)
{
    return (BYTE)(header.numChannels * header.bitsPerSample / 8);
}