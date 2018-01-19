"use strict";

var gl;
let timing = 0;

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
    gl.clearColor(1.0, 0.0, 0.0, 1.0);
}

function draw()
{
    if(timing!=60)
    {
        gl.clearColor(0.0, 1.0, 0.0, 1.0)
        ++timing;
    }
    else
    {
        gl.clearColor(1.0, 0.0, 0.0, 1.0);
        timing = 0;
    }

    gl.clear(gl.COLOR_BUFFER_BIT);
    window.requestAnimationFrame(draw);
}

function main()
{
    
    init();
    draw();
};

main();
