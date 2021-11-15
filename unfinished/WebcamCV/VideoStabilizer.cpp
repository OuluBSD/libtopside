#include "WebcamCV.h"


NAMESPACE_TOPSIDE_BEGIN


VideoStabilizerBase::VideoStabilizerBase() {
	
}

void VideoStabilizerBase::videOK(int videoWidth, int videoHeight) {

    canvas.width = canvasWidth  = 640;
    canvas.height = canvasHeight = 480;
    ctx = canvas.getContext('2d');

    frameSize.width = canvasWidth;
    frameSize.height = canvasHeight;

    //motion_estimator = new videostab.keypoint_motion_estimator(videostab.MM_AFFINE, frameSize);
    motion_estimator = new videostab.keypoint_motion_estimator(videostab.MM_HOMOGRAPHY, frameSize);

    stabilizer = new videostab.onepass_stabilizer();
    stabilizer.motion_estimator = motion_estimator;

    if(haveWebGL()) {

        // switch off image generation
        stabilizer.doImage = false;

        render_gl = new renderGL(sz.cx, sz.cy, canvas_gl);
        tex0 = render_gl.createAndSetupTexture();
        tex1 = render_gl.createAndSetupTexture();

        processGL();

    } else {

        canvas_gl.style.display = "none";
        video.style.display = canvas.style.display = "inline";
        video.width = canvas.width = canvasWidth = 320;
        video.height = canvas.height = canvasHeight = 240;

        frameSize.width = canvasWidth;
        frameSize.height = canvasHeight;

        motion_estimator = new videostab.keypoint_motion_estimator(videostab.MM_HOMOGRAPHY, frameSize);
        stabilizer.motion_estimator = motion_estimator;

        stabilizer.doImage = true;
        process();
    }
}

void VideoStabilizerBase::processGL() {
    compatibility.requestAnimationFrame( processGL );

    stat.new_frame();

    ctx.drawImage(video, 0, 0, canvasWidth, canvasHeight);
    var imageData = ctx.getImageData(0, 0, canvasWidth, canvasHeight);

    var motion = stabilizer.next_stabilized_frame(imageData);

    render_gl.render();

    var corns = tCorners(motion.data, canvasWidth, canvasHeight);

    render_gl.render_images(tex1, tex0, stabilizer.preProcessedFrame, video, canvasWidth, canvasHeight, corns);

    $('#log').html(stat.log());
}

Vector<Point> VideoStabilizerBase::tCorners(const Vector<float>& M, int w, int h) {
    var pt = [ {'x':0,'y':0}, {'x':w,'y':0}, {'x':w,'y':h}, {'x':0,'y':h} ];
    var z=0.0, i=0, px=0.0, py=0.0;

    for (; i < 4; ++i) {
        px = M[0]*pt[i].x + M[1]*pt[i].y + M[2];
        py = M[3]*pt[i].x + M[4]*pt[i].y + M[5];
        z = M[6]*pt[i].x + M[7]*pt[i].y + M[8];
        pt[i].x = px/z;
        pt[i].y = py/z;
    }

    return pt;
}

void VideoStabilizerBase::Process() {

    compatibility.requestAnimationFrame( process );

    stat.new_frame();

    ctx.drawImage(video, 0, 0, canvasWidth, canvasHeight);
    var imageData = ctx.getImageData(0, 0, canvasWidth, canvasHeight);

    var img = stabilizer.next_stabilized_frame(imageData);

    OutputFromGray(img);
}





#if 0

void VideoStabilizerBase::OglRenderer::renderGL(int w, int h, view) {
    width = w;
    height = h;

    worldMatrix	<< 2.0/width
				<< -2.0/height
				<< -1.0
				<< 1.0;

    gl.viewport(0, 0, width, height);

    initShaders();

    gl.disable(gl.DEPTH_TEST);
    gl.disable(gl.BLEND);
};

void VideoStabilizerBase::OglRenderer::render() {
    gl.clear(gl.COLOR_BUFFER_BIT);
    gl.clearColor(0, 0, 0, 1.0);

    gl.uniform4f(shaderProgram.transformUniform,
                    worldMatrix[0],
                    worldMatrix[1],
                    worldMatrix[2],
                    worldMatrix[3]);
}

void VideoStabilizerBase::OglRenderer::initShaders() {
    var fragmentShader = getShader(gl, "shader-fs");
    var vertexShader = getShader(gl, "shader-vs");
     
    // Create the shader program
       
    var shaderProgram = shaderProgram = gl.createProgram();
    gl.attachShader(shaderProgram, vertexShader);
    gl.attachShader(shaderProgram, fragmentShader);
    gl.linkProgram(shaderProgram);
       
    // If creating the shader program failed, alert
       
    if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
        alert("Unable to initialize the shader program.");
    }
       
    gl.useProgram(shaderProgram);
     
    shaderProgram.vertexPositionAttribute = gl.getAttribLocation(shaderProgram, "aVertexPosition");
    gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);

    shaderProgram.textureCoordAttribute = gl.getAttribLocation(shaderProgram, "aTextureCoord");
    gl.enableVertexAttribArray(shaderProgram.textureCoordAttribute);

    shaderProgram.transformUniform = gl.getUniformLocation(shaderProgram, "transform");
    shaderProgram.samplerUniform = gl.getUniformLocation(shaderProgram, "uSampler");
}

uint32 VideoStabilizerBase::OglRenderer::getShader(gl, id) {
    var shaderScript, theSource, currentChild, shader;
    shaderScript = document.getElementById(id);

    if (!shaderScript) {
        return null;
    }

    theSource = "";
    currentChild = shaderScript.firstChild;

    while(currentChild) {
        if (currentChild.nodeType == currentChild.TEXT_NODE) {
            theSource += currentChild.textContent;
        }
        currentChild = currentChild.nextSibling;
    }

    if (shaderScript.type == "x-shader/x-fragment") {
        shader = gl.createShader(gl.FRAGMENT_SHADER);
    } else if (shaderScript.type == "x-shader/x-vertex") {
        shader = gl.createShader(gl.VERTEX_SHADER);
    } else {
        // Unknown shader type
        return null;
    }
    gl.shaderSource(shader, theSource);

    // Compile the shader program
    gl.compileShader(shader);

    // See if it compiled successfully
    if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
        alert("An error occurred compiling the shaders: " + gl.getShaderInfoLog(shader));
        return null;
    }

    return shader;
}

uint32 VideoStabilizerBase::OglRenderer::createAndSetupTexture() {
    var gl = gl;
    var texture = gl.createTexture();
    gl.bindTexture(gl.TEXTURE_2D, texture);

    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);

    gl.bindTexture(gl.TEXTURE_2D, null);

    return texture;
};

void VideoStabilizerBase::OglRenderer::setRectangle(x, y, width, height) {
    var gl = gl;
    var x2 = x + width;
    var y2 = y + height;
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(
                                        [x, y,
                                         x2, y,
                                         x, y2,
                                         x, y2,
                                         x2, y,
                                         x2, y2
                                        ]), gl.STATIC_DRAW);
}

void VideoStabilizerBase::OglRenderer::setCorners(tlx, tly, trx, _try, brx, bry, blx, bly) {
    var gl = gl;
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(
                                        [tlx, tly,
                                         trx, _try,
                                         blx, bly,
                                         blx, bly,
                                         trx, _try,
                                         brx, bry
                                        ]), gl.STATIC_DRAW);
}

void VideoStabilizerBase::OglRenderer::render_images(tex_id0, tex_id1, image0, image1, w, h, p) {
    var gl = gl;
    var shaderProgram = shaderProgram;

    gl.bindTexture(gl.TEXTURE_2D, tex_id0);
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, image0);

    // draw stabilized first
    var texCoordBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, texCoordBuffer);

    gl.enableVertexAttribArray(shaderProgram.textureCoordAttribute);
    gl.vertexAttribPointer(shaderProgram.textureCoordAttribute, 2, gl.FLOAT, false, 0, 0);

    setRectangle(0, 0, 1, 1);

    var buffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
    gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);
    gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, 2, gl.FLOAT, false, 0, 0);

    setCorners(p[0].x, p[0].y, p[1].x, p[1].y,
                    p[2].x, p[2].y, p[3].x, p[3].y);

    // draw
    gl.drawArrays(gl.TRIANGLES, 0, 6);
    gl.bindTexture(gl.TEXTURE_2D, null);
    //

    // now half of original

    gl.bindTexture(gl.TEXTURE_2D, tex_id1);
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, image1);

    texCoordBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, texCoordBuffer);

    gl.enableVertexAttribArray(shaderProgram.textureCoordAttribute);
    gl.vertexAttribPointer(shaderProgram.textureCoordAttribute, 2, gl.FLOAT, false, 0, 0);

    setRectangle(0, 0, 0.5, 1);

    buffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
    gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);
    gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, 2, gl.FLOAT, false, 0, 0);

    setRectangle(0, 0, w/2, h);

    // draw
    gl.drawArrays(gl.TRIANGLES, 0, 6);

    gl.bindTexture(gl.TEXTURE_2D, null);
}

#endif


NAMESPACE_TOPSIDE_END

