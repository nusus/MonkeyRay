#version 150

uniform sampler2D  tex_object; 

in vec2 v_texture_coordinate;  
in vec3 v_vertex_normal; 
out vec4 FragColor;  
  
void main()  
{  
	FragColor = texture(tex_object, v_texture_coordinate); 
}  