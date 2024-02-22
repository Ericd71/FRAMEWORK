varying vec2 v_uv;
uniform float u_option;
uniform float u_aspect_ratio;

void main()
{
    // 1.a
    if(u_option == 1.1) {
        vec3 color = mix(vec3(0,0,1), vec3(1,0,0), v_uv.x);
        gl_FragColor = vec4(color,1.0);
    }

    //1.b Need to fix
    if(u_option == 1.2) {
        vec3 color2 = vec3(distance(vec2(0.5*u_aspect_ratio,0.5*u_aspect_ratio), v_uv));
        gl_FragColor = vec4(color2, 1.0);
    }
    
    //1.c
    if(u_option == 1.3) {
        // Assuming alternating black and white squares:
        if (mod(v_uv.x, 0.5) < 0.5) {
          gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0); // Black
        } else {
          gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0); // White
        }
    }
    
    //1.d
    if(u_option == 1.4) {
        gl_FragColor = vec4(step(0.5, v_uv.x), 1.0, 0.0, 1.0);
    }
    
    //gl_FragColor = vec4(mod(v_uv, 0.25), 0.0, 1.0);
}
