vec4 fetch(in sampler2D channel, in vec2 xy) {
    return texture(channel, xy / iResolution.xy);
}

void mainImage(out vec4 fragColor, in vec2 fragCoord) {
    fragColor = fetch(iChannel0, fragCoord);
    for (int i=-1; i < 2; i++) {
        for (int j=-1; j < 2; j++) {
            if (i == 0 && j == 0) continue;
            vec3 neighbor = fetch(iChannel0, fragCoord + vec2(i, j)).rgb / length(vec2(i, j));
            if (length(neighbor) > length(fragColor.rgb)) fragColor.rgb = neighbor;
        }
    }
}