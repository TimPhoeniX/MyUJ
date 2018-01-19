"use strict";
/// <reference path="./gl-matrix.d.ts" />

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

class Hexahedron
{
    constructor(vertices)
    {
        if(vertices.length != 8)
            throw Error("Inalid numbeer of hexahedron vertices");
        let VertexBuffer = new Float32Array(6*4*8);
        let IndexBuffer = new Uint16Array(6*2*3);
        let setFace = function(face, ll, lr, ur, ul)
        {   
            let ofs = face*4;
            IndexBuffer.set([ofs,ofs+1,ofs+2,ofs,ofs+2,ofs+3],face*6);
            ll = vec3.fromValues.apply(null,vertices[ll]);
            lr = vec3.fromValues.apply(null,vertices[lr]);
            ur = vec3.fromValues.apply(null,vertices[ur]);
            ul = vec3.fromValues.apply(null,vertices[ul]);
            let u = vec3.create();
            let v = vec3.create();
            let normal = vec3.create();
            vec3.sub(u,lr,ll);
            vec3.sub(v,ur,ll);
            vec3.cross(normal,u,v);
            vec3.normalize(normal,normal);
            let projection = vec3.create()
            vec3.scale(projection,u,vec3.dot(v,u)/vec3.dot(u,u));
            vec3.sub(v,v,projection);
            vec3.normalize(v,v);
            vec3.normalize(u,u);
            ofs *= 8;
            VertexBuffer.set(ll,ofs);
            VertexBuffer.set(lr,ofs+8);
            VertexBuffer.set(ur,ofs+16);
            VertexBuffer.set(ul,ofs+24);
            ofs+=3;
            VertexBuffer.set(normal,ofs);
            VertexBuffer.set(normal,ofs+8);
            VertexBuffer.set(normal,ofs+16);
            VertexBuffer.set(normal,ofs+24);
        }
        setFace(0,0,3,2,1);
        setFace(1,4,5,6,7);
        setFace(2,0,1,5,4);
        setFace(3,1,2,6,5);
        setFace(4,2,3,7,6);
        setFace(5,3,0,4,7);
        this.VertexBuffer = VertexBuffer;
        this.IndexBuffer = IndexBuffer;
        return this;
    }

    setFaceTex(face, ll, lr, ur, ul)
    {
        let ofs = face*4*8+6;
        this.VertexBuffer.set(ll,ofs);
        this.VertexBuffer.set(lr,ofs+8);
        this.VertexBuffer.set(ur,ofs+16);
        this.VertexBuffer.set(ul,ofs+24);
    }
}