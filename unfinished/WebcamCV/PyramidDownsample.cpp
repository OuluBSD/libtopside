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
var img_pyr;

function demo_app(videoWidth, videoHeight) {
    canvasWidth  = canvas.width;
    canvasHeight = canvas.height;
    ctx = canvas.getContext('2d');

    ctx.fillStyle = "rgb(0,255,0)";
    ctx.strokeStyle = "rgb(0,255,0)";

    img_pyr = new jsfeat.pyramid_t(4);
    img_pyr.allocate(640, 480, jsfeat.U8_t | jsfeat.C1_t);

    stat.add("grayscale");
    stat.add("pyrdown");
}

function tick() {
    compatibility.requestAnimationFrame(tick);
    stat.new_frame();
    if (video.readyState === video.HAVE_ENOUGH_DATA) {
        ctx.drawImage(video, 0, 0, 640, 480);
        var imageData = ctx.getImageData(0, 0, 640, 480);

        stat.start("grayscale");
        jsfeat.imgproc.grayscale(imageData.data, 640, 480, img_pyr.data[0]);
        stat.stop("grayscale");

        stat.start("pyrdown");
        // you do the same by executing img_pyr.build(img_pyr.data[0], true);
        var i = 2, a = img_pyr.data[0], b = img_pyr.data[1];
        jsfeat.imgproc.pyrdown(a, b);
        for(; i < img_pyr.levels; ++i) {
            a = b;
            b = img_pyr.data[i];
            jsfeat.imgproc.pyrdown(a, b);
        }
        stat.stop("pyrdown");

        // render result back to canvas
        var data_u32 = new Uint32Array(imageData.data.buffer);
        for(i=0; i < img_pyr.levels; ++i){
            render_mono_image(img_pyr.data[i].data, data_u32, img_pyr.data[i].cols, img_pyr.data[i].rows, 640);
        }

        ctx.putImageData(imageData, 0, 0);

        $('#log').html(stat.log());
    }
}

function render_mono_image(src, dst, sw, sh, dw) {
    var alpha = (0xff << 24);
    for(var i = 0; i < sh; ++i) {
        for(var j = 0; j < sw; ++j) {
            var pix = src[i*sw+j];
            dst[i*dw+j] = alpha | (pix << 16) | (pix << 8) | pix;
        }
    }
}

$(window).unload(function() {
    video.pause();
    video.src=null;
});
        

#endif
