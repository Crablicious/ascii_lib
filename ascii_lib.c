#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ascii_lib.h"


struct fieldData{
  struct position size;
  struct ascii_object **objs;
  int num_of_objects;
  char backg;
};


struct fieldData *field;
char *temp_field;

void initiate_field(int x, int y, char backg, int num_of_objects){
  field = malloc(sizeof(struct fieldData));
  field->size.x = x;
  field->size.y = y;
  field->backg = backg;
  field->objs = malloc(sizeof(void *)*num_of_objects);
  field->num_of_objects = num_of_objects;

  temp_field = malloc(sizeof(char)*field->size.y*field->size.x);
}

void insert_obj(struct ascii_object *obj){
  for(int i = 0; i < field->num_of_objects; i++){
    if(field->objs[i] == NULL){
      field->objs[i] = obj;
      return;
    }
  }
  printf("OBJECT ARRAY FULL, INCREASE NUM_OF_OBJECTS!\n");
}

struct position *add_object(struct ascii_object obj){
  struct ascii_object *tmp = malloc(sizeof(struct ascii_object));
  tmp->pos = obj.pos;
  tmp->height = obj.height;
  tmp->width = obj.width;
  
  tmp->twoDimArray = malloc(sizeof(char)*obj.width*obj.height);
  memcpy(tmp->twoDimArray, obj.twoDimArray, obj.height*obj.width);
  insert_obj(tmp);

  return (struct position *)&(tmp->pos);
}

void fill_background(char *temp_field){
  memset(temp_field, field->backg, field->size.x*field->size.y);
}

void draw_objects(char *temp_field){
  for(int i = 0; field->objs[i] != NULL; i++){
    struct ascii_object curr = *(field->objs[i]);
    
    for(int j = curr.pos.y; j < (curr.height+curr.pos.y); j++){ 
      if(j >= 0 && j < field->size.y){
        int height_offset = j*(field->size.x); 
        int width_offset = curr.pos.x;
        int offscreen_offset = 0; //don't draw out of screen.
        int width_to_draw = curr.width;
        if(curr.pos.x + curr.width > field->size.x){
          offscreen_offset = curr.pos.x + curr.width - field->size.x;
        }
        width_to_draw -= offscreen_offset;
        if(width_to_draw < 0){
          width_to_draw = 0;
        }
        memcpy(temp_field+height_offset+width_offset, curr.twoDimArray+(j-curr.pos.y)*curr.height, width_to_draw);
      }
    }
  }
}

void print_field(char *temp_field){
  for(int i = 0; i < field->size.y; i++){
    
    printf("%.*s\n", field->size.x, temp_field+i*field->size.x);
  }
}

void print_lines(){
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}


void draw_screen(){
  print_lines();
  
  fill_background(temp_field);
  draw_objects(temp_field);
  
  print_field(temp_field);
}

void delete_field(){
  free(temp_field);
  for(int i = 0; field->objs[i] != NULL; i++){
    free(field->objs[i]->twoDimArray);
    free(field->objs[i]);
  }
  free(field->objs);
  free(field);
}
