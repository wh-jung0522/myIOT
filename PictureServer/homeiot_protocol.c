#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "homeiot_protocol.h"

int recv_type_header(int sockfd, IOT_Header* iot_hdr)
{
    char* buf = (char*)calloc(1,sizeof(IOT_Header));
    int tot_recved = 0;
    int temp_recved = 0;
    unsigned short *header_type = (unsigned short *)calloc(1, sizeof(unsigned short));
    while (tot_recved<sizeof(IOT_Header))
    {
        temp_recved = recv(sockfd, buf+tot_recved,sizeof(IOT_Header)-tot_recved,0);
        if(temp_recved == -1) 
        {
            fprintf(stderr,"recv err\n");
            return -1;
        }
        tot_recved +=  temp_recved;
        if(tot_recved > sizeof(IOT_Header))
        {
            fprintf(stderr,"Header Size err\n");
            return -1;
        }
    }
    memcpy((void*)iot_hdr,(void*)buf,sizeof(IOT_Header));
    free(buf);
    printf("Recv Type Header\n");
    return 0;
}
int recv_picture_header(int sockfd, Picture_Header* pic_hdr)
{
    char* buf = (char*)calloc(1,sizeof(Picture_Header));
    int tot_recved = 0;
    int temp_recved = 0;
    while(tot_recved<sizeof(Picture_Header))
    {
        temp_recved = recv(sockfd, buf+tot_recved,sizeof(Picture_Header)-tot_recved,0);
        if(temp_recved == -1) 
        {
            fprintf(stderr,"recv err\n");
            return -1;
        }
        tot_recved +=  temp_recved;
        if(tot_recved > sizeof(Picture_Header))
        {
            fprintf(stderr,"Header Size err\n");
            return -1;
        }
    }
    memcpy((void*)pic_hdr,(void*)buf,sizeof(Picture_Header));
    free(buf);
    printf("Recv Picture Header\n");
    pic_hdr->size = ntohl(pic_hdr->size);
    printf("Recv Picture Size : %d bytes\n", pic_hdr->size);
    return 0;
}

int recv_save_picture_data(int sockfd, Picture_Header* pic_hdr)
{
    char *filepath = (char*)calloc(1,MAX_PATH_LENGTH);
    switch (pic_hdr->user)
    {
    case 0:
        /* Woohyun */
        strcat(filepath,"/home/whjung/Data/WH/");
        break;
    case 1:
        /* Bro */
        strcat(filepath,"/home/whjung/Data/SM/");
        break;
    case 2:
        /* Mom */
        strcat(filepath,"/home/whjung/Data/MOM/");
        break;
    default:
        fprintf(stderr,"User Err\n");
        return -1;
        break;
    }
    char* name = strtok(pic_hdr->picture_name, " ");;
    printf("Picture name : %s\n",name);
    strcat(filepath,name);
    //TODO Copy Resize -> thumbnail
    FILE* pic_fp = fopen(filepath,"w");
    void* buf = (void*)calloc(1,pic_hdr->size);
    int tot_recved = 0;
    int temp_recved = 0;
    while(tot_recved<pic_hdr->size)
    {
        temp_recved = recv(sockfd, buf+tot_recved,pic_hdr->size-tot_recved,0);
        if(temp_recved == -1) 
        {
            fprintf(stderr,"recv err\n");
            return -1;
        }
        tot_recved +=  temp_recved;
        if(tot_recved > pic_hdr->size)
        {
            fprintf(stderr,"Header Size err\n");
            return -1;
        }
    }
    fwrite(buf,pic_hdr->size,1,pic_fp);
    fclose(pic_fp);
    free(buf);
    printf("Recv Picture Data\n");
    return 0;
}