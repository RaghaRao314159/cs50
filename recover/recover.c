#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

void edit_filename(char *OG_filename, int i)
{
    //updates the name of the image to be stored (images are stored in increasing order)
    if (i < 10)
    {
        sprintf(OG_filename, "00%i.jpg", i);
        return;
    }
    else if (i < 100)
    {
        sprintf(OG_filename, "0%i.jpg", i);
        return;
    }
    sprintf(OG_filename, "%i.jpg", i);
    return;
}


int main(int argc, char *argv[])
{
    //ensure only one file name is keyed in
    if (argc != 2)
    {
        printf("Usage: ./recover raw_file\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    char filename[8] = "000.jpg";
    int idx = 0;
    FILE *img = NULL;

    //malloc is used for every picture and freed immediately after every image is saved.
    //This is to ensure that stack/heap does not run out of memory

    BYTE *buffer = malloc(512 * sizeof(BYTE));
    if (buffer == NULL)
    {
        fclose(card);
        printf("Could not open buffer.\n");
        return 1;
    }

    while (fread(buffer, sizeof(BYTE), 512, card) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] / 16 == 0x0e)
        {
            //close old file and open new file only when jpg signature is detected.

            if (idx != 0)
            {
                //close old file
                fclose(img);
            }

            //create new file
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Could not open %s.\n", filename);
                return 1;
            }

            //increments filename by 1
            idx += 1;
            edit_filename(filename, idx);
        }

        //ensure a file can only be written into after it is opened. i.e. do not write into NULL pointer
        if (idx != 0)
        {
            fwrite(buffer, sizeof(BYTE), 512, img);

            //free buffer once used to write
            free(buffer);

            //initialise new buffer for new block
            buffer = malloc(512 * sizeof(BYTE));
            if (buffer == NULL)
            {
                fclose(card);
                printf("Could not open buffer.\n");
                return 1;
            }
        }

    }
    free(buffer);
    fclose(img);
    fclose(card);

}