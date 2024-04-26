#include <limits.h>
#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846
#define RAD_BOT 10

// coordinate struct with float variables "x" & "y"
struct Point {
    float x, y;
};

//move struct with integer variables "angle" & "distance" (initial angle turn and move distance)
struct Move {
    float angle, distance;
};

// placeholder list for given object coordinate list 
const int given_object_point_list[][2] = {{3, 10}, {4, 5}, {5, 6}, {7, 0}, {1, 9}};

int num_pts(int list[]);
void init_obj_list(struct Point objects[]);
float dist_points(struct Point point1, struct Point point2);
double angle_points(struct Point point1, struct Point point2);

int main(void)
{
    
    // graph origin
    struct Point origin = {0, 0};
    
    // number of points robot may travel to, for movelist bc movelist len << point count so movelist[vnum]
    int objnum = num_pts(given_object_point_list);

    // placeholder for requested object designation from controller function
    // consider replacing with numerical designation? 
    char *obj_request = "delta";
    int desired_obj = 3;

    // storage list for the coordinates of all objects, initialized to global const int given_object_point_list[][2] 
    struct Point objects[objnum];
    init_obj_list(objects);

    // placeholder for list of object designations
    char *object_names[] = {"alpha", "beta", "charlie", "delta", "epsilon"};

    // list of avoidance points, values initialized w/ make_avoids()
    struct Point avoids[objnum][4];
    make_avoids(desired_obj, objnum, objects, avoids);

    // array of all points that must be navigated to reach destination
    struct Point *vlist = malloc(sizeof(struct Point) * (objnum * 5));



    // list of moves with angle and distance
    struct Move movelist[objnum];


}

// returns number of points add to
int num_pts(int list[])
{
    return 5;
}

// initializes the struct Point objects[] list with the given list of object coordinates
void init_obj_list(struct Point objects[])
{
    for (int i = 0; i < (sizeof(objects) / sizeof(struct Point)); i++){
        (*(objects + i)).x = *(*(given_object_point_list + i) + 0);
        (*(objects + i)).y = *(*(given_object_point_list + i) + 1);
    }
}

// find distance between two points. two struct Point as argument. return integer distance between them.
float dist_points(struct Point point1, struct Point point2)
{
    return sqrt(pow((point2.x - point1.x), 2) + pow((point2.y - point1.y), 2));
}

// find angle between two points. two struct Point as argument. return radian angle from x-axis from pt1 to pt2.
double angle_points(struct Point point1, struct Point point2)
{
    return atan(abs(point2.y - point1.y) / abs(point2.x - point1.x));
}

// take each object coordinate and create 4 vertices around it
// rows indexed to objects, columns for 4 avoidance points
// ccw generation
void make_avoids(int desired_obj, int objnum, struct Point objects[], struct Point (*avoids)[4])
{
    for (int i = 0; i < objnum; i++){
        if (i = desired_obj) continue;
        (*(avoids + i))[0] = (struct Point){(objects[i].x + RAD_BOT), (objects[i].y)};
        (*(avoids + i))[1] = (struct Point){(objects[i].x), (objects[i].y + RAD_BOT)};
        (*(avoids + i))[2] = (struct Point){(objects[i].x - RAD_BOT), (objects[i].y)};
        (*(avoids + i))[3] = (struct Point){(objects[i].x), (objects[i].y - RAD_BOT)};
    }

    return;
}

int check_path(int objnum, struct Point start, struct Point objects[], struct Point (*avoids)[4], struct Point *vlist, int desired_obj)
{
    // represent angle as line drawn. find lines, set inequality. if an avoidance point is a solution of the
    //inequality, check which object it belongs to, and increase that object's avoidance pt collision count by 
    //one. iterate through all avoidance points. if an object's avoidance point collision count is >= 2, store 
    //its avoidance points in the vertex list

    // find bot rectangle coordinates
    // (btop, bbot, otop, obot)
    struct Point rect_points[4];

    // iterate through avoidance for line A ccw
    for (int i = 0, l = 0; i < 4; i++){
        int hitflag = 0;

        for (int j = 0; j < objnum; j++){
            if (checkloc(rect_points[1], rect_points[3], avoids[i][j]) == 1) hitflag++;
        }

        if (hitflag > 1){
            for (int j = 0; j < 4; j++){
                vlist[l] = avoids[i][j];
                l++;
            } 
        }
    }

    // line b
    for (int i = 0, l = 0; i < 4; i++){
        int hitflag = 0;

        for (int j = 0; j < objnum; j++){
            if (checkloc(rect_points[1], rect_points[3], avoids[i][j]) == 1) hitflag++;
        }

        if (hitflag > 1){
            for (int j = 0; j < 4; j++){
                vlist[l] = avoids[i][j];
                l++;
            } 
        }
    }

    // line c
    for (int i = 0, l = 0; i < 4; i++){
        int hitflag = 0;

        for (int j = 0; j < objnum; j++){
            if (checkloc(rect_points[1], rect_points[3], avoids[i][j]) == 1) hitflag++;
        }

        if (hitflag > 1){
            for (int j = 0; j < 4; j++){
                vlist[l] = avoids[i][j];
                l++;
            } 
        }
    }

    // line d
    for (int i = 0, l = 0; i < 4; i++){
        int hitflag = 0;

        for (int j = 0; j < objnum; j++){
            if (checkloc(rect_points[1], rect_points[3], avoids[i][j]) == 1) hitflag++;
        }

        if (hitflag > 1){
            for (int j = 0; j < 4; j++){
                vlist[l] = avoids[i][j];
                l++;
            } 
        }
    }
}

void find_rect_points(struct Point rect_points[], struct Point start, struct Point object)
{
    double angle_bet = angle_points(start, object);
    double angle_btop, angle_bbot;

    // quadrant 1
    if (object.x >= 0 && object.y > 0){
        angle_btop = ((PI/2) + angle_bet);
        angle_bbot = (((3 * PI)/2) + angle_bet);
    }
    // quadrant 2
    if (object.x < 0 && object.y >= 0){
        angle_btop = (angle_bet - (PI/2));
        angle_bbot = (angle_bet + (PI/2));
    }
    // quadrant 3 
    if (object.x <= 0 && object.y < 0){
        angle_btop = (angle_bet - (PI/2));
        angle_bbot = (angle_bet + (PI/2));
    }
    // quadrant 4 
    if (object.x > 0 && object.y <= 0){
        angle_btop = (angle_bet - ((3* PI)/2));
        angle_bbot = (angle_bet) - (PI/2);
    } 

    // (btop, bbot, otop, obot)
    rect_points[0].x = cos(angle_btop) * (RAD_BOT);
    rect_points[0].y = sin(angle_btop) * (RAD_BOT);
    rect_points[1].x = cos(angle_bbot) * (RAD_BOT);
    rect_points[1].y = sin(angle_bbot) * (RAD_BOT);

    rect_points[2].x = (cos(angle_btop) * (RAD_BOT)) + object.x;
    rect_points[2].y = (sin(angle_btop) * (RAD_BOT)) + object.y;
    rect_points[3].x = (cos(angle_bbot) * (RAD_BOT)) + object.x;
    rect_points[3].y = (sin(angle_bbot) * (RAD_BOT)) + object.y;

}

// returns cross product magnitude of two 2D vectors
float cross_product(struct Point pt1, struct Point pt2)
{
    return (pt1.x * pt2.y) - (pt2.x * pt1.y);
}

// checks if pt3 is above, below, or on line formed by (pt1 & pt2) based on cross product signed magnitude
// 1 above, -1 below, 0 on
int checkloc(struct Point pt1, struct Point pt2, struct Point pt3)
{
    struct Point v = {(pt2.x - pt1.x), pt2.y - pt1.y};
    struct Point u = {(pt3.x - pt1.x), (pt3.y - pt1.y)};
    struct Point w = {(pt3.x - pt2.x), (pt3.y - pt2.y)};

    float p1 = cross_product(u, v);
    float p2 = cross_product(v, w);

    if (p1 > 0 && p2 > 0) return 1; // above line
    else if (p1 < 0 && p2 < 0) return -1; // below line
    else return 0; // on line
}