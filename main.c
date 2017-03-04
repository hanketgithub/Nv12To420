//
//  main.c
//  Nv12To420
//
//  Created by Hank Lee on 5/31/15.
//  Copyright (c) 2015 Hank Lee. All rights reserved.
//

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>

#include "Nv12To420.h"


int main(int argc, char *argv[])
{
    int ifd;
    int ofd;
    
    uint8_t *y;
    uint8_t *uv;
    ssize_t rd_sz;
    
    uint32_t width;
    uint32_t height;
    uint32_t wxh;
    
    char *cp;
    char output[256] = { 0 };


    if (argc < 4)
    {
        printf("useage: %s [input_file] [width] [height]\n", argv[0]);
        
        return -1;
    }

    
    rd_sz   = 0;
    width   = 0;
    height  = 0;
    wxh     = 0;
    cp      = NULL;

    // get input file name from comand line
    ifd = open(argv[1], O_RDONLY);
    if (ifd < 0)
    {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }
    
    // specify output file name
    cp = strrchr(argv[1], '_');
    strncpy(output, argv[1], cp - argv[1]);
    cp = strrchr(argv[1], '.');
    strcat(output, cp);
    ofd = open
            (
             output,
             O_WRONLY | O_CREAT | O_TRUNC,
             S_IRUSR
            );
    
    width   = atoi(argv[2]);
    height  = atoi(argv[3]);
    
    wxh = width * height;

    uint8_t *img = malloc(wxh * 3 / 2);
    uint8_t *u_dst = malloc(wxh / 4);
    uint8_t *v_dst = malloc(wxh / 4);
    
    y  = img;
    uv = y + wxh;
    
    printf("Processing: ");
    
    while (1)
    {
        rd_sz = read(ifd, img, wxh * 3 / 2);
            
        if (rd_sz == wxh * 3 / 2)
        {
            interleave_to_planar
            (
                wxh,
                u_dst,
                v_dst,
                uv
            );
 
            write(ofd, y, wxh);
            write(ofd, u_dst, wxh / 4);
            write(ofd, v_dst, wxh / 4);
        }
        else
        {
            break;
        }
        fputc('.', stdout);
        fflush(stdout);
    }
    
    close(ifd);
    close(ofd);
    
    printf("Done\n");
    printf("Output file: %s\n", output);
    
    return 0;
}
