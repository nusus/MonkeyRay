#version 150
 
uniform mat4 uni_mvpw_matrix;

in vec3 in_vertex_position; 
in vec2 in_texture_coordinate;
in vec3 in_vertex_normal;  
  
out vec2 v_texture_coordinate;  
out vec3 v_vertex_normal;
  
void main()  
{  
    v_texture_coordinate =  in_texture_coordinate;
	v_vertex_normal = in_vertex_normal;
    gl_Position = uni_mvpw_matrix * vec4(in_vertex_position,1.0);
}  