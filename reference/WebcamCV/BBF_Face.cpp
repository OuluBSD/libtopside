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
        try {
            video.src = compatibility.URL.createObjectURL(stream);
        } catch (error) {
            video.src = stream;
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
var img_u8,work_canvas,work_ctx;

var max_work_size = 160;

function demo_app(videoWidth, videoHeight) {
    canvasWidth  = canvas.width;
    canvasHeight = canvas.height;
    ctx = canvas.getContext('2d');

    ctx.fillStyle = "rgb(0,255,0)";
    ctx.strokeStyle = "rgb(0,255,0)";

    var scale = Math.min(max_work_size/videoWidth, max_work_size/videoHeight);
    var w = (videoWidth*scale)|0;
    var h = (videoHeight*scale)|0;

    img_u8 = new jsfeat.matrix_t(w, h, jsfeat.U8_t | jsfeat.C1_t);
    work_canvas = document.createElement('canvas');
    work_canvas.width = w;
    work_canvas.height = h;
    work_ctx = work_canvas.getContext('2d');

    jsfeat.bbf.prepare_cascade(jsfeat.bbf.face_cascade);

    stat.add("bbf detector");
}

function tick() {
    compatibility.requestAnimationFrame(tick);
    stat.new_frame();
    if (video.readyState === video.HAVE_ENOUGH_DATA) {

        ctx.drawImage(video, 0, 0, canvasWidth, canvasHeight);

        work_ctx.drawImage(video, 0, 0, work_canvas.width, work_canvas.height);
        var imageData = work_ctx.getImageData(0, 0, work_canvas.width, work_canvas.height);

        stat.start("bbf detector");

        jsfeat.imgproc.grayscale(imageData.data, work_canvas.width, work_canvas.height, img_u8);

        // possible options
        //jsfeat.imgproc.equalize_histogram(img_u8, img_u8);

        var pyr = jsfeat.bbf.build_pyramid(img_u8, 24*2, 24*2, 4);

        var rects = jsfeat.bbf.detect(pyr, jsfeat.bbf.face_cascade);
        rects = jsfeat.bbf.group_rectangles(rects, 1);

        stat.stop("bbf detector");

        // draw only most confident one
        draw_faces(ctx, rects, canvasWidth/img_u8.cols, 1);

        $('#log').html(stat.log());
    }
}

function draw_faces(ctx, rects, sc, max) {
    var on = rects.length;
    if(on && max) {
        jsfeat.math.qsort(rects, 0, on-1, function(a,b){return (b.confidence<a.confidence);})
    }
    var n = max || on;
    n = Math.min(n, on);
    var r;
    for(var i = 0; i < n; ++i) {
        r = rects[i];
        ctx.strokeRect((r.x*sc)|0,(r.y*sc)|0,(r.width*sc)|0,(r.height*sc)|0);
    }
}

$(window).unload(function() {
    video.pause();
    video.src=null;
});

#endif
