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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "Nv12To420.h"

int main(int argc, char *argv[])
{
    int fd_rd;
    int fd_wr;
    
    uint8_t *y;
    uint8_t *uv;
    ssize_t rd_sz;
    
    uint32_t width;
    uint32_t height;
    uint32_t wxh;
    
    char *output_file_name;


    if (argc < 4)
    {
        printf("useage: %s [input_file] [width] [height]\n", argv[0]);
        
        return -1;
    }

    
    rd_sz   = 0;
    width   = 0;
    height  = 0;
    wxh     = 0;
    
    output_file_name = "420sp.yuv";


    // get fd_rd file name from comand line
    fd_rd = open(argv[1], O_RDONLY);
    if (fd_rd < 0)
    {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }
    
    // specify fd_wr file name
    fd_wr = open(output_file_name, O_WRONLY | O_CREAT, S_IRUSR);
    
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
        rd_sz = read(fd_rd, img, wxh * 3 / 2);
            
        if (rd_sz == wxh * 3 / 2)
        {
            interleave_to_planar
            (
                wxh,
                u_dst,
                v_dst,
                uv
            );
 
            write(fd_wr, y, wxh);
            write(fd_wr, u_dst, wxh / 4);
            write(fd_wr, v_dst, wxh / 4);
        }
        else
        {
            break;
        }
        fputc('.', stdout);
        fflush(stdout);
    }
    
    close(fd_rd);
    close(fd_wr);
    
    printf("Done\n");
    printf("Output file: %s\n", output_file_name);
    
    return 0;
}
