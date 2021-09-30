#ifndef HOMEIOT_PROTOCOL_H
#define HOMEIOT_PROTOCOL_H

#ifndef MAX_HERADER_TYPE
#define MAX_HERADER_TYPE 65535
#endif

#ifndef MAX_PICTURE_LENGTH
#define MAX_PICTURE_LENGTH 128
#endif

#ifndef MAX_PATH_LENGTH
#define MAX_PATH_LENGTH 256
#endif


typedef struct _iot_hdr
{
    unsigned char type;
} __attribute__((__packed__)) IOT_Header;
// __attribute__((__packed__)) : without padding 


typedef struct _picture_hdr
{
    unsigned char user; /*User : 0~255*/
    int size;
    unsigned char picture_name[MAX_PICTURE_LENGTH];
} __attribute__((__packed__)) Picture_Header;

int recv_type_header(int sockfd, IOT_Header* iot_hdr);
int recv_picture_header(int sockfd, Picture_Header* pic_hdr);
int recv_save_picture_data(int sockfd, Picture_Header* pic_hdr);

#endif /* HOMEIOT_PROTOCOL_H */