"use strict";

/// <reference path="../../mylib.d.ts" />
/// <reference path="../../gl-matrix.d.ts" />
/// <reference path="../../webgl2.d.ts" />

/** @type {WebGL2RenderingContext} */
var gl;

var matrices_ubo = null;
var projection_matrix = null;

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
    gl.clearColor(0.0, 0.0, 0.0, 1.0);
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
    var triangle_color = new Float32Array([1.0, 1.0, 0.0, 0.0,0,1,1]);
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
    gl.bindVertexArray(vao);
    gl.bindBufferBase(gl.UNIFORM_BUFFER, color_ubb, color_ubo);
    gl.bindBufferBase(gl.UNIFORM_BUFFER, matrices_ubb, matrices_ubo);
}

var counter = 0;

function draw()
{
    counter += 0.03;
    let mvp_matrix = mat4.create();
    let view_matrix = mat4.create();
    mat4.lookAt(view_matrix, vec3.fromValues(0., /*Math.sin(counter)*/3, 4), vec3.fromValues(0., 0., 0.), new Float32Array([0., 1., 0.]));
    //mat4.lookAt(view_matrix, new Float32Array([.0, 0 ,2]), new Float32Array([0., 0., 0.]), new Float32Array([0., 1., 0.]));
    mat4.multiply(mvp_matrix, projection_matrix, view_matrix);
    // wyczyszczenie ekranu
    gl.clear(gl.COLOR_BUFFER_BIT);

    let model_matrix = mat4.create();
    mat4.rotateY(model_matrix, model_matrix, counter);
    mat4.translate(model_matrix, model_matrix, vec3.fromValues(1,0,0));
    mat4.rotateY(model_matrix, model_matrix, counter);
    mat4.multiply(mvp_matrix, mvp_matrix, model_matrix);    

    gl.bindBuffer(gl.UNIFORM_BUFFER, matrices_ubo);
    gl.bufferSubData(gl.UNIFORM_BUFFER,0,mvp_matrix,0,0);
    gl.bindBuffer(gl.UNIFORM_BUFFER, null);

    // wyslanie polecania rysowania do GPU (odpalenie shader-ow)
    //gl.drawArrays(gl.TRIANGLES, 0, 3);
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
    in vec2 fuv;
    layout(std140) uniform TriangleColor
    {
        vec3 color1;
        vec3 color2;
    };

    float signum;

    void main()
    {
        signum = sign((fuv.x-0.5)*(fuv.y-0.5));
        frag_color = vec4( color1*(-min(signum,0.)) + color2*max(signum,0.), 1);
    }`;

main();
