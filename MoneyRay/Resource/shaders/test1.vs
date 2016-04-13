#version 150
 
uniform mat4 uni_model_view_matrix;
uniform mat4 uni_projection_matrix;

in vec3 in_vertex_position; 
in vec2 in_texture_coordinate;
in vec3 in_vertex_normal;  
  
out vec2 v_texture_coordinate;  
out vec3 v_vertex_normal;
  
void main()  
{  
    v_texture_coordinate =  in_texture_coordinate;
	v_vertex_normal = in_vertex_normal;
    vec4 pos_vs = uni_model_view_matrix * vec4(in_vertex_position,1.0);
	gl_Position =   uni_projection_matrix * pos_vs;
}  