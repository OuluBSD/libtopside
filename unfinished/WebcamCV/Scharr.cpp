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
var img_u8,img_gxgy;

function demo_app(videoWidth, videoHeight) {
    canvasWidth  = canvas.width;
    canvasHeight = canvas.height;
    ctx = canvas.getContext('2d');

    ctx.fillStyle = "rgb(0,255,0)";
    ctx.strokeStyle = "rgb(0,255,0)";

    img_u8 = new jsfeat.matrix_t(640, 480, jsfeat.U8C1_t);
    img_gxgy = new jsfeat.matrix_t(640, 480, jsfeat.S32C2_t);

    stat.add("grayscale");
    stat.add("scharr");
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

        stat.start("scharr");
        jsfeat.imgproc.scharr_derivatives(img_u8, img_gxgy);
        stat.stop("scharr");

        // render result back to canvas
        var data_u32 = new Uint32Array(imageData.data.buffer);
        var alpha = (0xff << 24);
        var i = img_u8.cols*img_u8.rows, pix=0, gx = 0, gy = 0;
        while(--i >= 0) {
            gx = Math.abs(img_gxgy.data[i<<1]>>2)&0xff;
            gy = Math.abs(img_gxgy.data[(i<<1)+1]>>2)&0xff;
            pix = ((gx + gy)>>2)&0xff;
            data_u32[i] = (pix << 24) | (gx << 16) | (0 << 8) | gy;
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
