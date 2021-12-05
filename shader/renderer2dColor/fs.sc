$input v_texcoord0
/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

uniform vec4 u_color;

//SAMPLER2D(u_texture,  0);

void main()
{
	gl_FragColor = u_color/*texture2D(u_texture, v_texcoord0)*/;
}
