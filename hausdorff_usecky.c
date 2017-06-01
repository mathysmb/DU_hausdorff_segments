#include <stdio.h>
#include <math.h>

#define SIMILAR 1
#define FAIL 0

typedef struct{
    float x;
    float y;
}POINT;

typedef struct{
    POINT beg;
    POINT end;
}SEGMENT;

void make_vector(POINT *A,POINT *B,POINT *V){
	V->x = B->x - A->x;
	V->y = B->y - A->y;
}

float vector_lenght(POINT *v){
    return sqrt(v->x*v->x + v->y*v->y);
}

float vector_angle(POINT *v,POINT *u){
	float angle;

	angle = acos(( v->x*u->x + v->y*u->y ) / ( vector_lenght(v) * vector_lenght(u) ));

	return angle;
}


float dist_segment_point(SEGMENT *s,POINT *X){
    POINT u, v,w;
    float angle1,angle2;

    make_vector(&(s->beg),X,&u);
    make_vector(&(s->beg),&(s->end),&v);
    make_vector(X,&(s->end),&w);

    angle1 = vector_angle(&u,&v);
    angle2 = vector_angle(&v,&w);
	
	
    if (angle1 >= M_PI/2 || angle2 >= M_PI/2){
        if (vector_lenght(&u) > vector_lenght(&w)) 
			return vector_lenght(&w);
        else 
			return vector_lenght(&u);
    } else{
        return vector_lenght(&u)*sin(angle1);
    }


}

int comp_points(POINT *p1,POINT *p2){
	if ((p1->x == p2->x) && (p1->y == p2->y)) 
		return SIMILAR;
	else 
		return FAIL;
}

float dist_haus_line_line(SEGMENT *s1, SEGMENT *s2){
    float dist[4],max;
    int i;
    
	if (comp_points(&(s1->beg),&(s2->beg)) != 1 && comp_points(&(s1->beg),&(s2->end)) != 1) 
		dist[0] = dist_segment_point(s2,&(s1->beg));
	else 
		dist[0] = 0;
		
	if (comp_points(&(s1->end),&(s2->beg)) != 1 && comp_points(&(s1->end),&(s2->end)) != 1) 
		dist[1] = dist_segment_point(s2,&(s1->end));
	else 
		dist[1] = 0;
		
	if (comp_points(&(s2->beg),&(s1->beg)) != 1 && comp_points(&(s2->beg),&(s1->end)) != 1) 
		dist[2] = dist_segment_point(s1,&(s2->beg));
	else 
		dist[2] = 0;
		
	if (comp_points(&(s2->end),&(s1->beg)) != 1 && comp_points(&(s2->end),&(s1->end)) != 1) 
		dist[3] = dist_segment_point(s1,&(s2->end));
	else 
		dist[3] = 0;
	
	max = dist[0];
	for(i=0; i<4; i++){
    	if (dist[i] > max) max = dist[i];
	}

	return max;	
    
}

void main(){
    SEGMENT s1,s2;

	printf("Zadaj zaciatok a koniec prvej usecky:\n");
	scanf("%f%f%f%f",&(s1.beg.x),&(s1.beg.y),&(s1.end.x),&(s1.end.y));
	
	printf("Zadaj zaciatok a koniec druhej usecky:\n");
	scanf("%f%f%f%f",&(s2.beg.x),&(s2.beg.y),&(s2.end.x),&(s2.end.y));
	
	printf("%f",dist_haus_line_line(&s1,&s2));

}
