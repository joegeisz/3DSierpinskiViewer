#ifndef STRUCTS_H
#define STRUCTS_H

//
//  color, point, and affine transfomrations represented as structs
//

struct color{ double r; double g; double b;};
struct point{ double x; double y; double z; color cube; color past; };
struct affine{ double mat[3][3]; double vec[3];};

#endif // STRUCTS_H
