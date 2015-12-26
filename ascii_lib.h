#ifndef ASCII_LIB_H
#define ASCII_LIB_H

/* 
0.0 . . . . . . 0.y
1.0              
.
.
.
x.0 x.1 . . . . x.y
*/

//setTransparency char?
//set field size. width and height

//field struct?

//set x/y as -1 to kill object?

struct position{ 
  int x;
  int y;
};


struct ascii_object{
  struct position pos;
  int height;
  int width;
  char *twoDimArray; //design of object
};

void initiate_field(int x, int y, char backg, int num_of_objects);

struct position *add_object(struct ascii_object obj);

void draw_screen();

void delete_field();

#endif
