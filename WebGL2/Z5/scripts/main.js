"use strict";

/// <reference path="../../mylib.d.ts" />
/// <reference path="../../gl-matrix.d.ts" />
/// <reference path="../../webgl2.d.ts" />

/** @type {WebGL2RenderingContext} */
var gl;

var matrices_ubo = null;
var projection_matrix = null;

var texture1 = null;
var texture2 = null;
var texture3 = null;

function init()
{
    var m = mat4.create();
    // inicjalizacja webg2
    try {
        let canvas = document.querySelector("#glcanvas");
        gl = canvas.getContext("webgl2");
    }
    catch(e) {
    }

    if (!gl)
    {
        alert("Unable to initialize WebGL.");
        return;
    }
    gl.viewport(0, 0, gl.drawingBufferWidth, gl.drawingBufferHeight);
    gl.enable(gl.DEPTH_TEST);
    gl.clearColor(0.7, 0.7, 0.7, 1.0);
    gl.enable(gl.CULL_FACE);
    gl.cullFace(gl.BACK);    
    
    // kompilacja shader-ow
    var vertex_shader = createShader(gl, gl.VERTEX_SHADER, vs_source);
    var fragment_shader = createShader(gl, gl.FRAGMENT_SHADER, fs_source);
    var program = createProgram(gl, vertex_shader, fragment_shader);

    // pobranie ubi
    var color_ubi = gl.getUniformBlockIndex(program, "TriangleColor");
    var matrices_ubi = gl.getUniformBlockIndex(program, "Matrices");

    // przyporzadkowanie ubi do ubb
    let color_ubb = 0;
    gl.uniformBlockBinding(program, color_ubi, color_ubb);
    let matrices_ubb = 1;
    gl.uniformBlockBinding(program, matrices_ubi, matrices_ubb);

    var linear_sampler = gl.createSampler();
    gl.samplerParameteri(linear_sampler, gl.TEXTURE_WRAP_S, gl.REPEAT);
    gl.samplerParameteri(linear_sampler, gl.TEXTURE_WRAP_T, gl.REPEAT);
    gl.samplerParameteri(linear_sampler, gl.TEXTURE_WRAP_R, gl.REPEAT);
    gl.samplerParameteri(linear_sampler, gl.TEXTURE_MIN_FILTER, gl.LINEAR_MIPMAP_LINEAR);
    gl.samplerParameteri(linear_sampler, gl.TEXTURE_MAG_FILTER, gl.LINEAR);

    texture1 = gl.createTexture();
    gl.bindTexture(gl.TEXTURE_2D, texture1);
    // wypelnianie tekstury jednym pikselem
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, 1, 1, 0, gl.RGBA, gl.UNSIGNED_BYTE, new Uint8Array(255, 255, 255, 255));
    gl.bindTexture(gl.TEXTURE_2D, null);
    
    texture2 = gl.createTexture();
    gl.bindTexture(gl.TEXTURE_2D, texture2);
    // wypelnianie tekstury jednym pikselem
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, 1, 1, 0, gl.RGBA, gl.UNSIGNED_BYTE, new Uint8Array(255, 255, 255, 255));
    gl.bindTexture(gl.TEXTURE_2D, null);

    texture3 = gl.createTexture();
    gl.bindTexture(gl.TEXTURE_2D, texture3);
    // wypelnianie tekstury jednym pikselem
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, 1, 1, 0, gl.RGBA, gl.UNSIGNED_BYTE, new Uint8Array(255, 255, 255, 255));
    gl.bindTexture(gl.TEXTURE_2D, null);
    // ładowanie obrazka (asynchronicznie)
    var image1 = new Image();
    image1.src = "images/Modern_diffuse.png";
    image1.addEventListener('load', function(){
        gl.bindTexture(gl.TEXTURE_2D, texture1);
        // ladowanie danych z obrazka do tekstury
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, image1);
        // tworzenie mipmap
        gl.generateMipmap(gl.TEXTURE_2D);
        gl.bindTexture(gl.TEXTURE_2D, null);
    });
    var image2 = new Image();
    image2.src = "images/glass.png";
    image2.addEventListener('load', function(){
        gl.bindTexture(gl.TEXTURE_2D, texture2);
        // ladowanie danych z obrazka do tekstury
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, image2);
        // tworzenie mipmap
        gl.generateMipmap(gl.TEXTURE_2D);
        gl.bindTexture(gl.TEXTURE_2D, null);
    });
    var image3 = new Image();
    image3.src = "images/red_bricks.png";
    image3.addEventListener('load', function(){
        gl.bindTexture(gl.TEXTURE_2D, texture3);
        // ladowanie danych z obrazka do tekstury
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, image3);
        // tworzenie mipmap
        gl.generateMipmap(gl.TEXTURE_2D);
        gl.bindTexture(gl.TEXTURE_2D, null);
    });

    // dane o wierzcholkach
    var vertices = new Float32Array([
                    -0.4, -0.2, 0.4, 1,    0, 0, //0
                    0.4, -0.2, 0.4, 1,     0, 1, //1
                    0.4, -0.2, -0.4, 1,    1, 1, //2
                    -0.4, -0.2, -0.4, 1,   1, 0, //3
                    -0.2, +0.2, 0.2, 0.1,  0, 0, //4
                    0.2, +0.2, 0.2, 0.1,   0, 1, //5
                    0.2, +0.2, -0.2, 0.1,  1, 1, //6
                    -0.2, +0.2, -0.2, 0.1, 1, 0, //7
                    -0.4, -0.2, 0.4, 0.4,  0, 0, //8
                    0.4, -0.2, 0.4, 0.4,   0, 1, //9
                    -0.2, +0.2, 0.2, 0.4,  1, 0.25, //10
                    0.2, +0.2, 0.2, 0.4,   1, 0.75, //11
                    0.4, -0.2, 0.4, 0.6,   0, 0, //12
                    0.4, -0.2, -0.4, 0.6,  0, 1, //13
                    0.2, +0.2, 0.2, 0.6,   1, 0.25, //14
                    0.2, +0.2, -0.2, 0.6,  1, 0.75, //15
                    0.4, -0.2, -0.4, 0.8,  0, 0, //2 16
                    -0.4, -0.2, -0.4, 0.8, 0, 1, //3 17
                    0.2, +0.2, -0.2, 0.8,  1, 0.25, //6 18
                    -0.2, +0.2, -0.2, 0.8, 1, 0.75, //7 19
                    -0.4, -0.2, 0.4, 0.2,  0, 1, //0 20
                    -0.4, -0.2, -0.4, 0.2, 0, 0, //3 21
                    -0.2, +0.2, 0.2, 0.2,  1, 0.75, //4 22
                    -0.2, +0.2, -0.2, 0.2, 1, 0.25  //7 23
                    
                ]);

    //var vbo = getVBO(gl,vertices);
    var vbo = getVBO(vertices);
    // dane o indeksach
    var indices = new Uint16Array([
        2,1,0,
        0,3,2,
        4,5,6,
        4,6,7,
        8,9,11,
        8,11,10,
        12,13,15,
        12,15,14,
        16,17,19,
        16,19,18,
        21,20,22,
        21,22,23
    ]);

    // var vao = getIndexBuffer(gl,index_buffer);
    var index_buffer = gl.createBuffer();
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, index_buffer);
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, indices, gl.STATIC_DRAW);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, null);

    let gpu_positions_attrib_location = 0;
    let gpu_brightness_attrib_location = 1; // musi być taka sama jak po stronie GPU!!!
    let gpu_uv_attrib_location = 2;

    var vao = gl.createVertexArray();
    gl.bindVertexArray(vao);
    gl.bindBuffer(gl.ARRAY_BUFFER, vbo);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, index_buffer);
    gl.enableVertexAttribArray(gpu_positions_attrib_location);
    gl.vertexAttribPointer(gpu_positions_attrib_location, 3, gl.FLOAT, gl.FALSE, 6*4, 0);
    gl.enableVertexAttribArray(gpu_brightness_attrib_location);
    gl.vertexAttribPointer(gpu_brightness_attrib_location, 1, gl.FLOAT, gl.FALSE, 6*4, 3*4);
    gl.enableVertexAttribArray(gpu_uv_attrib_location);
    gl.vertexAttribPointer(gpu_uv_attrib_location, 2, gl.FLOAT, gl.FALSE, 6*4, 4*4);
    gl.bindVertexArray(null);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, null);

    // dane o kolorze
    var triangle_color = new Float32Array([
        1.0, 1.0, 1.0,
        0.0,
        0.5, 0.5, 0.5
    ]);
    // dane o macierzy
    var mvp_matrix = mat4.create();
    var model_matrix = mat4.create();
    mat4.rotateY(model_matrix, model_matrix, Math.PI/4);
    var view_matrix = mat4.create();
    mat4.lookAt(view_matrix, new Float32Array([0., 0., 2.]), new Float32Array([0., 0., 0.]), new Float32Array([0., 1., 0.]));
    projection_matrix = mat4.create();
    mat4.perspective(projection_matrix, Math.PI/4., gl.drawingBufferWidth/gl.drawingBufferHeight, 0.01, 10);
    mat4.multiply(mvp_matrix, projection_matrix, view_matrix);
    mat4.mul(mvp_matrix, mvp_matrix, model_matrix);

    // tworzenie UBO
    var color_ubo = gl.createBuffer();
    gl.bindBuffer(gl.UNIFORM_BUFFER, color_ubo);
    gl.bufferData(gl.UNIFORM_BUFFER, triangle_color, gl.DYNAMIC_DRAW);
    gl.bindBuffer(gl.UNIFORM_BUFFER, null);
    matrices_ubo = gl.createBuffer();
    gl.bindBuffer(gl.UNIFORM_BUFFER, matrices_ubo);
    gl.bufferData(gl.UNIFORM_BUFFER, mvp_matrix, gl.DYNAMIC_DRAW);
    gl.bindBuffer(gl.UNIFORM_BUFFER, null);

    // ustawienia danych dla funkcji draw*
    gl.useProgram(program);
    gl.bindSampler(0, linear_sampler);
    gl.activeTexture(gl.TEXTURE0 +  0);
    gl.bindVertexArray(vao);
    gl.bindBufferBase(gl.UNIFORM_BUFFER, color_ubb, color_ubo);
    gl.bindBufferBase(gl.UNIFORM_BUFFER, matrices_ubb, matrices_ubo);
}

var counter = 0;

var Key = {
    _pressed: {},
  
    W:87,
    S:83,
    A:65,
    D:68,
    LEFT: 37,
    UP: 38,
    RIGHT: 39,
    DOWN: 40,

    isDown: function(keyCode) {
      return this._pressed[keyCode];
    },
    
    onKeydown: function(event) {
      this._pressed[event.keyCode] = true;
    },
    
    onKeyup: function(event) {
      delete this._pressed[event.keyCode];
    }
};
window.addEventListener('keyup', function(event) { Key.onKeyup(event); }, false);
window.addEventListener('keydown', function(event) { Key.onKeydown(event); }, false);

var rotX = 0;
var rotY = 0;
var movX = 0;
var movY = 0;
const delta_rot = 0.1;
const delta_mov = 0.05;

function camTransform(cam_matrix){
  if (Key.isDown(Key.UP)) rotX+=delta_rot;
  if (Key.isDown(Key.DOWN)) rotX-=delta_rot;
  if (Key.isDown(Key.LEFT)) rotY+=delta_rot;
  if (Key.isDown(Key.RIGHT)) rotY-=delta_rot;
  if (Key.isDown(Key.W)) movY-=delta_mov;
  if (Key.isDown(Key.S)) movY+=delta_mov;
  if (Key.isDown(Key.A)) movX+=delta_mov;
  if (Key.isDown(Key.D)) movX-=delta_mov; 
  mat4.translate(cam_matrix,cam_matrix,[movX,movY,0])
  mat4.rotateY(cam_matrix,cam_matrix,rotY);
  mat4.rotateX(cam_matrix,cam_matrix,rotX);
  //mat4.translate(cam_matrix,cam_matrix,[movX,movY,0])
}

function draw()
{
    counter += Math.PI/200;
    let mvp_matrix = mat4.create();
    let vp_matrix = mat4.create();
    let view_matrix = mat4.create();
    mat4.lookAt(view_matrix, vec3.fromValues(0., /*Math.sin(counter)*/0, 5), vec3.fromValues(0., 0., 0.), new Float32Array([0., 1., 0.]));
    //mat4.lookAt(view_matrix, new Float32Array([.0, 0 ,2]), new Float32Array([0., 0., 0.]), new Float32Array([0., 1., 0.]));
    camTransform(view_matrix)
    mat4.multiply(vp_matrix, projection_matrix, view_matrix);
    // wyczyszczenie ekranu
    gl.clear(gl.COLOR_BUFFER_BIT);

    let model_matrix = mat4.create();
    mat4.rotateY(model_matrix, model_matrix, counter);

    mat4.multiply(mvp_matrix, vp_matrix, model_matrix);        
    gl.bindBuffer(gl.UNIFORM_BUFFER, matrices_ubo);
    gl.bufferSubData(gl.UNIFORM_BUFFER,0,mvp_matrix,0,0);
    gl.bindBuffer(gl.UNIFORM_BUFFER, null);

    gl.bindTexture(gl.TEXTURE_2D, texture1);
    gl.drawElements(gl.TRIANGLES, 3*2*6, gl.UNSIGNED_SHORT, 0);
    
    mat4.translate(model_matrix, model_matrix, vec3.fromValues(2,0,0));
    mat4.rotateY(model_matrix, model_matrix, counter);

    mat4.multiply(mvp_matrix, vp_matrix, model_matrix);        
    gl.bindBuffer(gl.UNIFORM_BUFFER, matrices_ubo);
    gl.bufferSubData(gl.UNIFORM_BUFFER,0,mvp_matrix,0,0);
    gl.bindBuffer(gl.UNIFORM_BUFFER, null);
    
    gl.bindTexture(gl.TEXTURE_2D, texture2);
    gl.drawElements(gl.TRIANGLES, 3*2*6, gl.UNSIGNED_SHORT, 0);

    let moon = mat4.create();
    mat4.scale(moon, moon, vec3.fromValues(0.5,0.5,0.5));    
    mat4.rotateY(moon, moon, counter);
    mat4.translate(moon, moon, vec3.fromValues(1.5,0,0));
    mat4.rotateY(moon, moon, counter);

    mat4.multiply(model_matrix, model_matrix, moon);        
    mat4.multiply(mvp_matrix, vp_matrix, model_matrix);        
    gl.bindBuffer(gl.UNIFORM_BUFFER, matrices_ubo);
    gl.bufferSubData(gl.UNIFORM_BUFFER,0,mvp_matrix,0,0);
    gl.bindBuffer(gl.UNIFORM_BUFFER, null);

    gl.bindTexture(gl.TEXTURE_2D, texture3);
    gl.drawElements(gl.TRIANGLES, 3*2*6, gl.UNSIGNED_SHORT, 0);

    window.requestAnimationFrame(draw);
}

function main()
{
    init();
    draw();
};

function createShader(gl, type, source)
{
    var shader = gl.createShader(type);
    gl.shaderSource(shader, source);
    gl.compileShader(shader);
    var success = gl.getShaderParameter(shader, gl.COMPILE_STATUS);
    if(success)
    {
        return shader;
    }

    console.log(gl.getShaderInfoLog(shader));
    gl.deleteShader(shader);
}

function createProgram(gl, vertex_shader, fragment_shader)
{
    var program = gl.createProgram();
    gl.attachShader(program, vertex_shader);
    gl.attachShader(program, fragment_shader);
    gl.linkProgram(program);
    var success = gl.getProgramParameter(program, gl.LINK_STATUS);
    if(success)
    {
        return program;
    }

    console.log(gl.getProgramInfoLog(program));
    gl.deleteProgram(program);
}

// vertex shader (GLSL)
var vs_source = `#version 300 es
    // "location" musi byc takie same jak po stronie CPU!!!
    layout(location = 0) in vec3 vertex_position;
    layout(location = 1) in float brightness;
    layout(location = 2) in vec2 uv;
    out float fbrightness;
    out vec2 fuv;

    layout(std140) uniform Matrices
    {
        mat4 mvp_matrix;
    };
    void main()
    {
        gl_Position = mvp_matrix*vec4(vertex_position, 1);
        fbrightness = (1.1-brightness);
        fuv=uv;
    }`;

// fragment shader (GLSL)
var fs_source = `#version 300 es
    // fs nie ma domyślnej precyzji dla liczb zmiennoprzecinkowych więc musimy wybrać ją sami
    precision mediump float;
    in float fbrightness;
    out vec4 frag_color;
    uniform sampler2D color_texture;
    in vec2 fuv;
    layout(std140) uniform TriangleColor
    {
        vec3 color1;
        vec3 color2;
    };

    float signum;

    void main()
    {
        //signum = sign((fuv.x-0.5)*(fuv.y-0.5));
        signum = -sign( (fuv.x-0.5)*(fuv.x-0.5)+(fuv.y-0.5)*(fuv.y-0.5)-(0.25*0.25) );
        vec3 result = texture(color_texture, fuv).rgb;
        vec3 chess = color1*(-min(signum,0.)) + color2*max(signum,0.);
        frag_color = vec4( chess*result, 1);
        //frag_color = vec4( result, 1);
    }`;

main();
