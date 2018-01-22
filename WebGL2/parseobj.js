"use strict";

//<iframe id="<name>" src="<path>" style="display:none;"></iframe>
// query = "#<name"      

function getObjectsFromFrame(query){
    let data = document.querySelector(query).contentDocument.getElementsByTagName("pre")[0].innerHTML;
    return parseObjects(data);
}

function getMaterialsFromFrame(query){
    let data = document.querySelector(query).contentDocument.getElementsByTagName("pre")[0].innerHTML;
    return parseMaterials(data);
}

function parseObjects(obj)
{
    let Objects = [];
    let vertices = [];
    let texcoords = [];
    let normals = [];
    let faces = [];
    let usemtl = null;
    function parseLine(line)
    {
        let newObject = line.indexOf("object");
        if(newObject != -1)
        {
            line = line.trim();
            line = line.split(/\s+/);
            return line[2];
        }

        let comment = line.indexOf("#");
        if(comment != -1) {
            line = line.substring(0, comment);
        }
        line = line.trim();

        line = line.split(/\s+/);

        if(line[0] === 'v')
        {
            vertices.push([Number(line[1]), Number(line[2]), Number(line[3])]);
        }
        else if(line[0] === 'vt')
        {
            texcoords.push([Number(line[1]), Number(line[2])]);
        }
        else if(line[0] === 'vn')
        {
            normals.push([Number(line[1]), Number(line[2]), Number(line[3])]);
        }
        else if(line[0] === 'f')
        {
            let face = []
            for(let i = 1; i < line.length; ++i)
            {
                let verts = line[i].split(/\W+/);
                face.push({v:verts[0]-1,uv:verts[1]-1,n:verts[2]-1});
            }
            if(face.length === 3)
            {
                faces.push(...face);
            }
            else
            {
                faces.push(face[0],face[1],face[2],face[0],face[2],face[3])
            }
        }
        else if(line[0] === 'usemtl')
        {
            usemtl = line[1];
        }
    }

    function makeData(name)
    {
        let indices = [];
        let data = [];
        let unique = {};
        let index = 0;
        for (let i = 0; i < faces.length; i++) {
            let face = faces[i];
            let id = face.v+"/"+face.uv+"/"+face.n;
            if(unique[id])
            {
                indices.push(unique[id]);
            }
            else
            {
                let vertex = vertices[face.v].concat(normals[face.n],texcoords[face.uv]);
                data.push(...vertex);
                indices.push(index);
                unique[id]=index++;
            }
        }
        return { name:name, data:data, indices:indices, material:usemtl };
    }

    obj = obj.split('\n');
    let object = undefined;
    let nextObject = undefined;
    for(let i = 0; i < obj.length; ++i)
    {
        nextObject = parseLine(obj[i]);
        if(!object && nextObject)
        {
            object = nextObject;
        }
        else if(nextObject && (object != nextObject))
        {
            Objects.push(makeData(object))
            object = nextObject;
            faces = [];
        }
    }
    Objects.push(makeData(object))
    return Objects;
};

function parseMaterials(mats)
{
    let currentMat = {};
    let materials = [];
    function parseLine(line)
    {
        var comment = line.indexOf("#");
        if(comment != -1)
        {
            line = line.substring(0, comment);
        }

        line = line.trim();
        line = line.split(/\s+/);

        if(line[0] === "newmtl")
        {
            if(currentMat.name)
            {
                materials.push(currentMat);
                currentMat = {};
            }
            currentMat.name = line[1];
        }
        else if(line[0] === "Ka")
        {
            currentMat.ambient = [...line.slice(1,4)];
        }
        else if(line[0] === "Kd")
        {
            currentMat.diffuse = [...line.slice(1,4)];
        }
        else if(line[0] === "Ks")
        {
            currentMat.specular = [...line.slice(1,4)];
        }
        else if(line[0] === "Ns")
        {
            currentMat.specularExponent = line[1];
        }
        else if(line[0] === "d" || line[0] === "Tr")
        {
            currentMat.transparent = line[1];
        }
        else if(line[0] === "illum")
        {
            currentMat.illumMode = line[1];
        }
        else if(line[0] === "map_Ka")
        {
            currentMat.ambientMap = line[1];
        }
        else if(line[0] === "map_Kd")
        {
            currentMat.diffuseMap = line[1];
        }
        else if(line[0] === "map_Ks")
        {
            currentMat.specularMap = line[1];
        }
        else if(line[0] === "map_d")
        {
            currentMat.alphaMat = line[1];
        }
        else if(line[0] === "map_bump" || line[0] === "bump") {
            currentMat.bumpMap = line[1];
        }
        else if(line[0] === "disp")
        {
            currentMat.displacementMap = line[1];
        }
        return currentMat;
    }
    mats = mats.split('\n');
    let material = undefined;
    let nextmat = undefined;
    for(let i = 0; i < mats.length; ++i)
    {
        nextmat = parseLine(mats[i]);
    }
    return materials;
}