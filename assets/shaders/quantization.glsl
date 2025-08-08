#version 330 core

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D tex;

const float channels = 4.0;

void main()
{
	vec4 color = texture(tex, texCoord);
	color.rgb = floor(color.rgb * channels) / channels;
	
	FragColor = vec4(color.rgb, 1.0);
}