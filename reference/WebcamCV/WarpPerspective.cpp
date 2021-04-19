#include "WebcamCV.h"

#if 0


// lets do some fun
var video = document.getElementById('webcam');
var canvas = document.getElementById('canvas');
try {
    var attempts = 0;
    var readyListener = function(event) {
        findVideoSize();
    };
    var findVideoSize = function() {
        if(video.videoWidth > 0 && video.videoHeight > 0) {
            video.removeEventListener('loadeddata', readyListener);
            onDimensionsReady(video.videoWidth, video.videoHeight);
        } else {
            if(attempts < 10) {
                attempts++;
                setTimeout(findVideoSize, 200);
            } else {
                onDimensionsReady(640, 480);
            }
        }
    };
    var onDimensionsReady = function(width, height) {
        demo_app(width, height);
        compatibility.requestAnimationFrame(tick);
    };

    video.addEventListener('loadeddata', readyListener);

    compatibility.getUserMedia({video: true}, function(stream) {
        if(video.srcObject !== undefined){
            video.srcObject = stream
        } else {
            try {
                video.src = compatibility.URL.createObjectURL(stream);
            } catch (error) {
                video.src = stream;
            }
        }
        setTimeout(function() {
                video.play();
            }, 500);
    }, function (error) {
        $('#canvas').hide();
        $('#log').hide();
        $('#no_rtc').html('<h4>WebRTC not available.</h4>');
        $('#no_rtc').show();
    });
} catch (error) {
    $('#canvas').hide();
    $('#log').hide();
    $('#no_rtc').html('<h4>Something goes wrong...</h4>');
    $('#no_rtc').show();
}

var stat = new profiler();

var ctx,canvasWidth,canvasHeight;
var img_u8, img_u8_warp, transform;

function demo_app(videoWidth, videoHeight) {
    canvasWidth  = canvas.width;
    canvasHeight = canvas.height;
    ctx = canvas.getContext('2d');

    ctx.fillStyle = "rgb(0,255,0)";
    ctx.strokeStyle = "rgb(0,255,0)";

    img_u8 = new jsfeat.matrix_t(640, 480, jsfeat.U8_t | jsfeat.C1_t);
    img_u8_warp = new jsfeat.matrix_t(640, 480, jsfeat.U8_t | jsfeat.C1_t);
    transform = new jsfeat.matrix_t(3, 3, jsfeat.F32_t | jsfeat.C1_t);

    jsfeat.math.perspective_4point_transform(transform, 0,   0,   50,  50,
                                                        640, 0,   550, 100,
                                                        640, 480, 300, 400,
                                                        0,   480, 100, 400);
    jsfeat.matmath.invert_3x3(transform, transform);

    stat.add("grayscale");
    stat.add("warp perspective");
}

function tick() {
    compatibility.requestAnimationFrame(tick);
    stat.new_frame();
    if (video.readyState === video.HAVE_ENOUGH_DATA) {
        ctx.drawImage(video, 0, 0, 640, 480);
        var imageData = ctx.getImageData(0, 0, 640, 480);

        stat.start("grayscale");
        jsfeat.imgproc.grayscale(imageData.data, 640, 480, img_u8);
        stat.stop("grayscale");

        stat.start("warp perspective");
        jsfeat.imgproc.warp_perspective(img_u8, img_u8_warp, transform, 0);
        stat.stop("warp perspective");

        // render result back to canvas
        var data_u32 = new Uint32Array(imageData.data.buffer);
        var alpha = (0xff << 24);
        var i = img_u8_warp.cols*img_u8_warp.rows, pix = 0;
        while(--i >= 0) {
            pix = img_u8_warp.data[i];
            data_u32[i] = alpha | (pix << 16) | (pix << 8) | pix;
        }

        ctx.putImageData(imageData, 0, 0);

        $('#log').html(stat.log());
    }
}

$(window).unload(function() {
    video.pause();
    video.src=null;
});


#endif
