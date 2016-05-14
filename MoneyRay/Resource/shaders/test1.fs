#version 150

uniform sampler2D  tex_object; 
in vec2 v_texture_coordinate;  
in vec3 v_vertex_normal; 
//out vec4 FragColor;  
  
void main()  
{  
	gl_FragColor = texture(tex_object, v_texture_coordinate); 
	//FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}  