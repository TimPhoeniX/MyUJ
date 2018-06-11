"use strict";

class Model
{
    constructor(vertices, indices, attributes)
    {
        this.vbo = getVBO(gl,vertices);
        this.indexBuffer = getIndexBuffer(gl, indices);
        this.vao = getVAO(gl,this.vbo,this.indexBuffer, attributes);
        this.ver_count = indices.length;
    }
}

function drawModel(model)
{
    gl.bindVertexArray(model.vao);
    gl.drawElements(gl.TRIANGLES, model.ver_count, gl.UNSIGNED_SHORT, 0);
    gl.bindVertexArray(null);
}

function getVBO(vertices, mode)
{
    let vbo = gl.createBuffer();
    mode = mode | gl.STATIC_DRAW;
    gl.bindBuffer(gl.ARRAY_BUFFER, vbo);
    gl.bufferData(gl.ARRAY_BUFFER, vertices, mode);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);
    return vbo;   
}

function getIndexBuffer(indices, mode)
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

function makeAttrArray(attributes)
{
    let stride = 0;
    for(let attrib of attributes)
    {
        attrib.offset = stride;
        stride += attrib.stride;
    }
    for(let attrib of attributes)
    {
        attrib.stride = stride;
    }
}

function getVAO(vbo, index_buffer, attributes)
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