"use strict";

var gl;


function init()
{
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

    gl.clearColor(0.0, 0.0, 0.0, 1.0);
    //gl.enable(gl.CULL_FACE);
    //gl.cullFace(gl.BACK);

    // kompilacja shader-ow
    var vertex_shader = createShader(gl, gl.VERTEX_SHADER, vs_source);
    var fragment_shader = createShader(gl, gl.FRAGMENT_SHADER, fs_source);
    var program = createProgram(gl, vertex_shader, fragment_shader);

    // dane o wierzcholkach
    var vertices = new Float32Array([
        0.0, 0.6, 0.0, 1.0,0.0,0.0,
        -0.3, 0.3, 0.0, 1.0,0.0,0.0,
        0.3, 0.3, 0.0, 1.0,0.0,0.0,
        0.3, 0.3, 0.0, 0.0,1.0,0.0,
        -0.3, -0.3, 0.0, 0.0,0.0,1.0,
        0.3, -0.3, 0.0, 1.0,1.0,1.0,
    ]);

    // tworzenie VBO
    var vbo = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vbo);
    gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);

    var indices = new Uint16Array([0, 1, 2, 1,4,3,4,5,3]);

    // tworzenie bufora indeksow
    var index_buffer = gl.createBuffer();
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, index_buffer);
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, indices, gl.STATIC_DRAW);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, null);

    let gpu_positions_attrib_location = 0;
    let gpu_colors_attrib_location = 1;

    // tworzenie VAO
    var vao = gl.createVertexArray();
    gl.bindVertexArray(vao);
    gl.bindBuffer(gl.ARRAY_BUFFER, vbo);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, index_buffer);
    gl.enableVertexAttribArray(gpu_positions_attrib_location);
    gl.vertexAttribPointer(gpu_positions_attrib_location, 3, gl.FLOAT, gl.FALSE, 6*4, 0);
    gl.enableVertexAttribArray(gpu_colors_attrib_location);
    gl.vertexAttribPointer(gpu_colors_attrib_location, 3, gl.FLOAT, gl.FALSE, 6*4, 3*4);
    gl.bindVertexArray(null);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, null);

    // ustawienia danych dla funkcji draw*
    gl.useProgram(program);
    gl.bindVertexArray(vao);
}

function draw()
{
    // wyczyszczenie ekranu
    gl.clear(gl.COLOR_BUFFER_BIT);

    // wyslanie polecania rysowania (odpalenie shader-ow) do GPU
    gl.drawElements(gl.TRIANGLES, 9, gl.UNSIGNED_SHORT, 0);

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
var vs_source =
    `#version 300 es
    layout(location = 0) in vec3 vertex_position;
    layout(location = 1) in vec3 vertex_color;
    out vec3 color;
    void main()
    {
        gl_Position = vec4(vertex_position, 1);
        color = vertex_color;
    }`;

// fragment shader (GLSL)
var fs_source =
    `#version 300 es
    precision mediump float;
    in vec3 color;
    out vec4 frag_color;
    void main()
    {
        frag_color = vec4(color,1);
    }`;

main();
