#version 410 core
precision highp float;
#define pi = 3.1415926535897932385;
#define FLT_MAX 3.402823466e+38
#define FLT_MIN 1.175494351e-38

//#include "ray.glsl"
//#include "sphere.glsl"
//#include "hitrect.glsl"


in vec2 texCoord;
out vec4 color;

/*RAYO*/
struct Ray{
    vec3 origin;
    vec3 dir;
};

/*SPHERE*/
struct Sphere{
    vec3 center;
    float radius;
};
/*HIT RECORD*/
struct HitRecord{
    vec3 p;
    vec3 normal;
    float t;
    bool front_face;
};

void set_face_normal(Ray r,  vec3 outward_normal, inout HitRecord hit) {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.

        hit.front_face = dot(r.dir, outward_normal) < 0.0;
        hit.normal = hit.front_face ? outward_normal : -outward_normal;
    }


vec3 at(Ray r, float t)
{
    return r.origin + t * r.dir;
}

bool hit_sphere(Sphere s, Ray r, float ray_tmin, float ray_tmax, inout HitRecord rec) {
    vec3 oc = s.center - r.origin;
    float a =  dot(r.dir, r.dir);
    float h =  dot(r.dir, oc);//b = -2.0 * dot(r.dir, oc);
    float c =  dot(oc, oc) - s.radius*s.radius;
    float discriminant = h*h - a *c; //b*b - 4*a*c;
    
    if(discriminant < 0.0)
        return false;
    //return ((-b - sqrt(discriminant)) / (2.0 * a) );
    float sqrtd = sqrt(discriminant);
    float root =  (h - sqrtd) / a;  
     if (root <= ray_tmin || ray_tmax <= root) {
            root = (h + sqrtd) / a;
            if (root <= ray_tmin || ray_tmax <= root)
                return false;
            
        }

    rec.t = root;
    rec.p = at(r,rec.t);
    vec3 outward_normal = (rec.p - s.center) / s.radius;
    set_face_normal(r, outward_normal,rec);

    return true;



}

vec3 ray_color(Ray r, Sphere s, float ray_tmin, float ray_tmax, inout HitRecord rec){

    bool hit_t = hit_sphere(s,r, ray_tmin, ray_tmax, rec);

    if (hit_t) {
        //rec3 N = normalize(at(r,hit_t) - vec3(s.center));
        return 0.5 * (rec.normal + vec3(1.0));
    }

    vec3 unit_direction = normalize(r.dir);
    float a = 0.5*(unit_direction.y + 1.0);
    return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a*vec3(0.5, 0.7, 1.0);
}


void main()
{
    
    /*Pantalla*/
    float aspectRatio = 16.0 / 9.0;
    int image_width = 400;
    int image_height = int(image_width / aspectRatio);

    if(image_height < 1)
        image_height = 1;

    vec3 camera_center = vec3(0.0);
    vec3 up = vec3(0.0,1.0,0.0);
    vec3 right = vec3(1.0,0.0,0.0);

    float focal_length = 1.0;
    float viewport_height = 2.0;
    float viewport_width = viewport_height * (float(image_width)/image_height);

     // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    vec3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    vec3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    vec3 pixel_center = pixel00_loc + (texCoord.x * image_width  * pixel_delta_u) + (texCoord.y * image_height  * pixel_delta_v);
    vec3 ray_direction = pixel_center - camera_center;
    
    /***/
    Ray rayo;
    rayo.origin = camera_center;
    rayo.dir = ray_direction;

    Sphere esfera;
    esfera.center = vec3(0.0,0.0,-1.0);
    esfera.radius = 0.5;

    Sphere esfera2;
    esfera2.center = vec3(0.0,-100.5,-1.0);
    esfera2.radius = 100.0;
    
    HitRecord rec;

    vec3 pixel_color = ray_color(rayo,esfera,FLT_MIN, FLT_MAX, rec);
    vec3 pixel_color2 = ray_color(rayo,esfera2,FLT_MIN, FLT_MAX, rec);

    color = vec4(pixel_color2, 1.0);
}