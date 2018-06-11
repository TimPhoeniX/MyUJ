"use strict";


class Model
{
    constructor(gl, vertices, indices, attributes)
    {
        this.vbo = getVBO(gl,vertices);
        this.indexBuffer = getIndexBuffer(gl, indices);
        this.vao = getVAO(gl,this.vbo,this.indexBuffer, attributes);
        this.ver_count = indices.length;
    }
}

function drawModel(gl, model)
{
    gl.bindVertexArray(model.vao);
    gl.drawElements(gl.TRIANGLES, model.ver_count, gl.UNSIGNED_SHORT, 0);
    gl.bindVertexArray(null);
}

function getVBO(gl, vertices, mode)
{
    let vbo = gl.createBuffer();
    mode = mode | gl.STATIC_DRAW;
    gl.bindBuffer(gl.ARRAY_BUFFER, vbo);
    gl.bufferData(gl.ARRAY_BUFFER, vertices, mode);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);
    return vbo;   
}

function getIndexBuffer(gl, indices, mode)
{
    let index_buffer = gl.createBuffer();
    mode = mode | gl.STATIC_DRAW;
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, index_buffer);
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, indices, gl.STATIC_DRAW);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, null);
    return index_buffer;   
}

class Attribute
{
    constructor(index, size, type, normalized, stride, offset)
    {
        this.index = index;
        this.size = size;
        this.type = type;
        this.normalized = normalized | false;
        this.stride = stride | 4*this.size;
        this.offset = offset | 0; 
    }
}


function getVAO(gl, vbo, index_buffer, attributes)
{
    let setAtrribute = function(attribute)
    {
        gl.enableVertexAttribArray(attribute.index);
        gl.vertexAttribPointer(attribute.index, attribute.size, attribute.type,
            attribute.normalized, attribute.stride, attribute.offset);    
    }   

    let vao = gl.createVertexArray();
    gl.bindVertexArray(vao);
    gl.bindBuffer(gl.ARRAY_BUFFER, vbo);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, index_buffer);
    if(attributes instanceof Array)
    {
        for(let attrib of attributes)
        {
            setAtrribute(attrib);
        }
    }
    else
    {
        setAtrribute(attributes);
    }
    gl.bindVertexArray(null);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, null);
    return vao;
}

var gl;

var frame = 0;

var sun = null;

var house  = null;

var uniforms = {
    color:{
        ubo:null,
        ubi:null,
        ubb:null
    },
    offset:{
        ubo:null,
        ubi:null,
        ubb:null
    }
};

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

    // kompilacja shader-ow
    var vertex_shader = createShader(gl, gl.VERTEX_SHADER, vs_source);
    var fragment_shader = createShader(gl, gl.FRAGMENT_SHADER, fs_source);
    var program = createProgram(gl, vertex_shader, fragment_shader);

    // pobranie ubi
    var color_ubi = gl.getUniformBlockIndex(program, "Color");
    var offset_ubi = gl.getUniformBlockIndex(program, "Offset");
    //var pos_ubi = gl.getUniformBlockIndex(program, "TrianglePosition");
    //console.log("color ubi: " + color_ubi + "\npos ubi: " + pos_ubi);

    // przyporzadkowanie ubi do ubb
    let color_ubb = 0;
    let offset_ubb = 1;
    gl.uniformBlockBinding(program, color_ubi, color_ubb);
    gl.uniformBlockBinding(program, offset_ubi, offset_ubb);

    
    // dane o wierzcholkach
    var vertices = new Float32Array([
        0.0, 0.6, 0.0,// 1.0,0.0,0.0,
        -0.3, 0.3, 0.0,// 1.0,0.0,0.0,
        0.3, 0.3, 0.0,// 1.0,0.0,0.0,
        0.3, 0.3, 0.0,// 0.0,1.0,0.0,
        -0.3, -0.3, 0.0,// 0.0,0.0,1.0,
        0.3, -0.3, 0.0//, 1.0,1.0,1.0,
    ]);

    var indices = new Uint16Array([0, 1, 2, 1,4,3,4,5,3]);

    let gpu_positions_attrib_location = 0; // musi być taka sama jak po stronie GPU!!!
    let pos_attr = new Attribute(gpu_positions_attrib_location,3 , gl.FLOAT);
    
    house = new Model(gl,vertices,indices,pos_attr);
    house.color = new Float32Array([1.0,0.0,.0,.0]),
    house.offset = new Float32Array([0.4,-.3,.0,1])

    vertices = new Float32Array([
        0.0, 0.0, 0.0,// 1.0,0.0,0.0,
        0.1, 0.2, 0.0,// 1.0,0.0,0.0,
        0.2, 0.0, 0.0,// 1.0,0.0,0.0,
        0.1, -0.2, 0.0,// 0.0,1.0,0.0,
        -0.1, -0.2, 0.0,// 0.0,0.0,1.0,
        -0.2, 0, 0.0,// 1.0,1.0,1.0,
        -0.1, 0.2, 0.0//, 1.0,1.0,1.0,
    ]);

    // dane o indeksach
    indices = new Uint16Array([
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5,
        0,5,6,
        0,6,1
    ]);

    sun = new Model(gl,vertices,indices,pos_attr);
    sun.color = new Float32Array([1.0,1.0,.0,.0]),
    sun.offset = new Float32Array([-0.4,-.3,.0,.5])


    // dane o kolorze
    var color = new Float32Array([1.0, 1.0, 0.0, 0.0]);

    // dane o kolorze
    var offset = new Float32Array([0.0, 0.0, 0.0, 0.0]);

    // tworzenie UBO - Uniform Buffer Object
    var color_ubo = gl.createBuffer();
    gl.bindBuffer(gl.UNIFORM_BUFFER, color_ubo);
    gl.bufferData(gl.UNIFORM_BUFFER, color, gl.DYNAMIC_DRAW);
    gl.bindBuffer(gl.UNIFORM_BUFFER, null);

    var offset_ubo = gl.createBuffer();
    gl.bindBuffer(gl.UNIFORM_BUFFER, offset_ubo);
    gl.bufferData(gl.UNIFORM_BUFFER, offset, gl.DYNAMIC_DRAW);
    gl.bindBuffer(gl.UNIFORM_BUFFER, null);

    uniforms.color.ubb = color_ubb;
    uniforms.color.ubi = color_ubi;
    uniforms.color.ubo = color_ubo;

    uniforms.offset.ubb = offset_ubb;
    uniforms.offset.ubi = offset_ubi;
    uniforms.offset.ubo = offset_ubo;

    // ustawienia danych dla funkcji draw*
    gl.useProgram(program);
    gl.bindVertexArray(sun.vao);
    gl.bindBufferBase(gl.UNIFORM_BUFFER, color_ubb, color_ubo);
    gl.bindBufferBase(gl.UNIFORM_BUFFER, offset_ubb, offset_ubo);
    gl.bindVertexArray(house.vao);
    gl.bindBufferBase(gl.UNIFORM_BUFFER, color_ubb, color_ubo);
    gl.bindBufferBase(gl.UNIFORM_BUFFER, offset_ubb, offset_ubo);
}

function draw()
{
    // wyczyszczenie ekranu
    gl.clear(gl.COLOR_BUFFER_BIT);
    // wyslanie polecania rysowania do GPU (odpalenie shader-ow)
    //gl.drawArrays(gl.TRIANGLES, 0, 3);

    frame-=0.01;

    sun.offset  = new Float32Array([
        0.4 + -.8*Math.cos(frame)+.8*Math.sin(frame),
        -.3 + -.8*Math.cos(frame)-.8*Math.sin(frame),
        .0,
        0.1 + Math.abs(Math.cos(frame))
        ]);

    gl.bindBuffer(gl.UNIFORM_BUFFER, uniforms.color.ubo);
    gl.bufferSubData(gl.UNIFORM_BUFFER,0,house.color,0,0);
    gl.bindBuffer(gl.UNIFORM_BUFFER, null);

    gl.bindBuffer(gl.UNIFORM_BUFFER, uniforms.offset.ubo);
    gl.bufferSubData(gl.UNIFORM_BUFFER,0,house.offset,0,0);
    gl.bindBuffer(gl.UNIFORM_BUFFER, null);

    drawModel(gl,house);

    gl.bindBuffer(gl.UNIFORM_BUFFER, uniforms.color.ubo);
    gl.bufferSubData(gl.UNIFORM_BUFFER,0,sun.color,0,0);
    gl.bindBuffer(gl.UNIFORM_BUFFER, null);

    gl.bindBuffer(gl.UNIFORM_BUFFER, uniforms.offset.ubo);
    gl.bufferSubData(gl.UNIFORM_BUFFER,0,sun.offset,0,0);
    gl.bindBuffer(gl.UNIFORM_BUFFER, null);

    drawModel(gl,sun);

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
    //location musi byc takie same jak po stronie CPU!!!
    layout(location = 0) in vec3 vertex_position;
    layout(std140) uniform Offset
    {
        vec3 offset;
        float scale;
    };
    void main()
    {
        gl_Position = vec4(vertex_position*scale + offset, 1);
    }`;

// fragment shader (GLSL)
var fs_source = `#version 300 es
    //fs nie ma domyślnej precyzji dla liczb zmiennoprzecinkowych więc musimy wybrać ją sami
    precision mediump float;
    out vec4 frag_color;
    layout(std140) uniform Color
    {
        vec3 color;
    };
    void main()
    {
        //frag_color = vec4(1, 0, 0, 1);
        frag_color = vec4(color, 1);
    }`;

main();
