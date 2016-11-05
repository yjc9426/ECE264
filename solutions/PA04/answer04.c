#include "answer04.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

Image * Image_load(const char * filename)
{
  FILE * fp = NULL;
  int read;
  ImageHeader header;

  size_t num_bytes = 0;
  Image * image = NULL;
  int err = 0;
  
  fp = fopen(filename, "r");
  if(fp==NULL)
   {
      return NULL;
    }
  
  read = fread(&header, sizeof(ImageHeader),1,fp);
  if(!read){
    fclose(fp);
    return NULL;
  }

  if(!header.height|| !header.width)
    {
      fclose(fp);
      return NULL;
    }

  if(header.magic_number != ECE264_IMAGE_MAGIC_NUMBER)
    {
      fclose(fp);
      return NULL;
    }

  if(!header.comment_len)
    {
      fclose(fp);
      return NULL;
    }
  
  char * com = malloc(header.comment_len * sizeof(char));
  if(com == NULL)
    {
      fclose(fp);
      free(com);	
      return NULL;
    }
  
  read = fread(com, 1,header.comment_len, fp);
  if(header.comment_len != read)
    {
      fclose(fp);
      free(com);	
      return NULL;
    }
  
  if(com[header.comment_len - 1] != '\0')
    {
      fclose(fp);
      free(com);	
      return NULL;
    }
  
  num_bytes = sizeof(uint8_t) * header.height * header.width;
  image = malloc(sizeof(Image));
  image->comment = malloc(sizeof(char)*(strlen(com) + 1));
  image->height = header.height;
  image->width = header.width;
  strcpy(image->comment, com);
  image->data = malloc(num_bytes);
  if(image->data == NULL)
    {
      Image_free(image);
      free(com);
      fclose(fp);
      return NULL;
    } 
  
  read = fread(image->data, sizeof(uint8_t), num_bytes, fp);

  if(read != num_bytes)
    {
      Image_free(image);
      free(com);
      fclose(fp);	
      return NULL;
    }

  uint8_t bytes;
  
  read = fread(&bytes, sizeof(uint8_t), 1, fp);

  if(read != 0)
    {
      Image_free(image);
      free(com);
      fclose(fp);	
      return NULL;
    }
   
  free(com);
  fclose(fp);
  return(image);
}

int Image_save(const char *filename, Image * image)
{
  FILE * fp = fopen(filename, "w");
  ImageHeader header;

  header.width = image->width;
  header.height = image->height;
  header.magic_number = ECE264_IMAGE_MAGIC_NUMBER;
  header.comment_len = strlen(image->comment) + 1;

  fwrite(&header, sizeof(ImageHeader), 1, fp);
  fprintf(fp,"%s%c", image->comment, '\0');
  

  int i;
  for(i = 0; i < (image->width * image->height); i++)
    {
      fprintf(fp, "%c", image->data[i]);
    }
  
  fclose(fp);
  return 1;
}

void Image_free(Image * image)
{
  free(image->comment);
  free(image->data);
  free(image);
}

void linearNormalization(int width, int height, uint8_t * intensity)
{
  int i;
  uint8_t max = intensity[0];
  uint8_t min = intensity[0];


  for(i=1; i < height * width; i++)
    {
      if(intensity[i] > max)
	{
	  max = intensity[i];
	}
      if(intensity[i] < min)
	{
	  min = intensity[i];
	}
    }

  for(i = 0; i < height * width; i++)
    {
      intensity[i] = (intensity[i] - min) * 255.0 / (max - min);
    }
}