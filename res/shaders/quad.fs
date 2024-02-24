varying vec2 v_uv;
uniform float u_option;
uniform float u_aspect_ratio;
uniform float u_time;
// Resolution might not be used
uniform vec2 u_resolution;
uniform vec2 u_aspect;

//Get the texture as a sampler2D from our application.cpp file
uniform sampler2D u_texture;

const float PI = 3.14159265359;

void main()
{
    // 1.a
    if(u_option == 1.1) {
        vec3 color = mix(vec3(0,0,1), vec3(1,0,0), v_uv.x);
        gl_FragColor = vec4(color,1.0);
    }

    //1.b
    if(u_option == 1.2) {
        vec2 center = vec2(0.5); //from 0 to 1 --> 0.5,0.5 is the center
        float dist_pixel_center = distance(center, v_uv); //Compute distance from the pixel to the center
        gl_FragColor =  vec4(vec3(dist_pixel_center), 1); //Returns as color the distance from 0 to 1.
    }
    
    //1.c TODO: NEED TO FIX
    if(u_option == 1.3) {
        float red_color = step(0.75, sin(v_uv.x * 30.0));
        float blue_color = step(0.75, sin(v_uv.y * 30.0));
        gl_FragColor = vec4(red_color, 0.0, blue_color, 1.0);
        
        //float red_color = step(0.75, sin(v_uv.x * 30.0)); //Sinus varies over time horizontally
        //float blue_color = step(0,75, sin(v_uv.y * 30.0)); //Sinus varies over time vertically
        //gl_FragColor = vec4(red_color, 0.0, blue_color, 1.0); //Set red and blue
    }
    
    //1.d
    if(u_option == 1.4) {
        float rows = 15.0;
        float cols = 15.0;
        
        vec2 uv = v_uv * vec2(rows, cols);
        
        vec2 cell = vec2(floor(uv));
        
        
        vec3 color = mix(mix(vec3(0,0,0), vec3(1,0,0), float(cell.x) / (cols - 1.0)), mix(vec3(0,1,0), vec3(1,1,0), float(cell.x) / (cols -1.0)), float(cell.y) / (rows -1.0));
        
        gl_FragColor = vec4(color, 1.0);
    }
    //1.e //TODO: still have to do it
    if(u_option == 1.5) {
        //dimensions_cell is formed by two floats indicating the position of the row and column
        float num_cells = 20.0;
        vec2 dimensions_cell = floor(v_uv * vec2(num_cells * u_aspect_ratio, 20.0)); //20x20 checkboard
        //We use floor to convert it to the nearest integer value and we also normalize it to our aspect ratio
        //We consider whether we paint black or white the squares
        //The module of the cell coordinates divided by 2.0 will be either 0.0 or 1.0, and hence as it is a vector 3 it will be either black (0.0,0.0,0.0) or white(1.0,1.0,1.0).
        vec3 black_or_white = vec3(mod(dimensions_cell.x + dimensions_cell.y, 2.0) == 0.0 ? 1.0 : 0.0);
        gl_FragColor =  vec4(black_or_white, 1.0);
    }
    //1.f TODO: JUST 1 COSINUS AND NO MOVEMENT
    if(u_option == 1.6) {
        //To compute this we divide it in the up and down section to form both sinusoids
        vec3 up = vec3(0, 1.0 - v_uv.y, 0); //top half
        vec3 down = vec3(0, v_uv.y, 0); //down half
        float up_sin = cos(1.2 * PI * v_uv.x); //Sinus varies over time horizontally and affects top half
        //float down_sin = sin(u_time * PI * (1.0 - v_uv.x)); //Sinus varies over time horizontally and affects down half

        vec3 color = vec3(up * step(0.5 + (up_sin * 0.2), v_uv.y)); //step makes a half to be visible or not
        //color += vec3(down * step(0.5 + (down_sin * 0.2), 1.0 - v_uv.y));
        gl_FragColor = vec4(color, 1.0);
    }
    
    //2.a
    if(u_option == 2.1) {
        vec4 color = texture2D(u_texture, v_uv);
        float grey_scale = (color.x + color.y + color.z) / 3.0; //Average the color
        gl_FragColor = vec4(vec3(grey_scale), 1.0);
    }
    //2.b
    if(u_option == 2.2) {
        vec4 color = texture2D(u_texture, v_uv);
        vec3 inverse_color = vec3(1.0 - color); //We compute the inverse of the color with 1 - color
        gl_FragColor = vec4(inverse_color, 1.0);
    }
    //2.c TODO: NEED TO FIX
    if(u_option == 2.3) {
        vec4 color = texture2D(u_texture, v_uv);
        float color1 = color.x;
        float color2 = color.y;
        float color3 = color.z;
        //Change the values of the color coordinates for channel manipulation
        color.x = 1.0 - color3;
        color.y = color1;
        color.z = color2 / 2.0;
        gl_FragColor = color;
    }
    //2.d TODO: NEED TO FIX
    if(u_option == 2.4) {
        // Using code I used in exercise 2.1 for grey scale
        vec4 color = texture2D(u_texture, v_uv);
        vec3 inverse_color = vec3(1.0 - color); //We compute the inverse of the color with 1 - color
        vec4 grey_scale = vec4(inverse_color, 1.0);
        
        //If the average grey_scale is smaller than 0.5 then returns 0.0 and hence we are working with color black, otherwise returns 1.0 and we are working with white
        vec3 black_and_white = vec3(step(0.5, grey_scale));
        gl_FragColor = vec4(black_and_white, 1.0);
    }
    //2.e
    if(u_option == 2.5) {
        vec4 color = texture2D(u_texture, v_uv);
        vec2 center = vec2(0.5);
      
        float dist_pixel_center = distance(v_uv, center); //from 0 to 1 --> 0.5,0.5 is the center
        float fading = 1.5; //Inner circle
      
        float vignette_effect = 1.0 - dist_pixel_center * fading; //Previously in ex1_b we have seen the distance formula generated an effect with a black circle in the middle fading to white therefore here we apply the inverse
        color = color * vignette_effect; //Apply effect to the image
        gl_FragColor = color;
    }
    
    //2.f
    if(u_option == 2.6) {
        vec4 color = vec4(0.0);
        vec2 pixel_size = vec2(0.001); //Size of each pixel

        //Blur approach: Box blur, each pixel in the resulting image has a value equal to the average value of its neighbours
        for (int i = -5; i <= 5; i++) { //11x11
            for (int j = -5; j <= 5; j++) {
                vec2 offset = vec2(float(i), float(j)) * pixel_size; //offset of neighbour pixel with current pixel
                   color += texture2D(u_texture, v_uv + offset); //add neighbour pixel to color
            }
        }
        color = color / 121.0; //Average the color by the number of pixels used in the for loop (11x11)
        gl_FragColor = color;
    }
    
    
    
    //3.a
    if(u_option == 3.1) {
        vec2 pixel_size = vec2(1.0 / u_aspect.x, 1.0 / u_aspect.y); //Size of each pixel
        float animation = sin(u_time * PI) * 10.0 + 10.0; //Sinus effect using time normalized from [0,20]
        vec2 new_size = animation * pixel_size;  //update size of pixel
        vec2 norm_pos = new_size * floor(v_uv / new_size); //normalize it from [0,1]
        gl_FragColor = texture2D(u_texture, norm_pos); //set the new texture with new coordinates with the effect.
    }
    //2.b
    if(u_option == 3.2) {
        //Compute distance from center of the screen to the pixel
//        float width = (0.5 - v_uv.x) * u_aspect_ratio; //Normalize it to our aspect ratio so shapes are circular and not flat
//        float height = 0.5 - v_uv.y;
//        float distance_center = sqrt(pow(width, 2) + pow(height, 2)); //Pythagoras: Compute distance from center of the screen to the pixel
//        float phase = (distance_center - u_time) * 10.0; //10.0 increases the size of the circle and the speed
//        float slope = cos(phase); //Oscillates [-1,1]
//        vec2 pattern = normalize(vec2(width, height)) * slope * 0.05; //Generate circular pattern varying in time
//        gl_FragColor = texture2D(u_image, v_uv + pattern);
    }

    //gl_FragColor = vec4(mod(v_uv, 0.25), 0.0, 1.0);
}
