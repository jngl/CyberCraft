$input a_position, a_texcoord0
$output v_texcoord0

/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

void main()
{
    v_texcoord0 = a_texcoord0;
	gl_Position = mul(u_modelViewProj, vec4(a_position, 0.0, 1.0) );
}
