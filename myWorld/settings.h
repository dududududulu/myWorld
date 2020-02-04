#ifndef _SETTINGS_H
#define _SETTINGS_H

#include <iostream>
using namespace std;

/* Settins of the World */
#define PI               3.14159265
#define Dimension        3
#define TimeElapse       1
#define GLength          256
#define GWidth           256
#define ShotLength       10
#define ShotWidth        10
#define PixelWidth       ShotWidth / GWidth
#define GXCenter         GLength / 2 - 1
#define GYCenter         GWidth / 2 - 1
#define UpView           0
#define DownView         1
#define RightView        2
#define LeftView         3

/* Type Mappings */
#define null_geo         -1
#define line_geo         0

#define shape_geo        100
#define circle_geo       shape_geo
#define square_geo       shape_geo + 1
#define rectangle_geo    shape_geo + 2
#define polygon_geo      shape_geo + 10
#define triangle_geo     polygon_geo + 1
#define rectagon_geo     polygon_geo + 2
#define pendagon_geo     polygon_geo + 3
#define hexagon_geo      polygon_geo + 4
#define curve_geo        shape_geo + 50
#define ring_geo         curve_geo
#define freeshape_geo    shape_geo + 99

#define solid_geo        200
#define globe_geo        solid_geo
#define cylinder_geo     solid_geo + 1
#define prism_geo        solid_geo + 20
#define cube_geo         prism_geo
#define triprism_geo     prism_geo + 1
#define cuboid_geo       prism_geo + 2
#define surface_geo      solid_geo + 50
#define sphere_geo       surface_geo
#define hsphere_geo      surface_geo + 1
#define freesolid_geo    solid_geo + 99


#define point_packing    0
#define frame_packing    1
#define connect_packing  2
#define shape_packing    3


/* Calculation */
#define Numerical_Error  1e-9

/* Alignment */
#define numberSpace      10
#define charSpace        10


/* Accessory Functions */
int minDim(int, int);
bool infinitesimal(double);
double material_density(int);

/* Test Functions */
bool all_test();
bool matrix_test();
bool geometry_test();
bool effect_test();
bool entity_test();

#endif